/** ----------------------
  Copyright (C): OpenGATE Collaboration
  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See LICENSE.md for further details
  ----------------------*/
#include "PositroniumHistograms.h"
#include <iostream>
#include "TF1.h"

PositroniumHistograms::PositroniumHistograms() {}

PositroniumHistograms::~PositroniumHistograms() {}

void PositroniumHistograms::setPromptGammaEnable( const bool& enable ) { fDataWithPrompt = enable; }

void PositroniumHistograms::setAnnihilationGammasNumber( const int& n ) { fAnnihilationGammasNumber = n; }

void PositroniumHistograms::setLifeTimeHistogramParams( const unsigned int& bins, const double& minx, const double& maxx )
{
 fMinTime = minx;
 fMaxTime = maxx;
 fBinsTime = bins; 
}

void PositroniumHistograms::setLifetime( const double& lifetime ) { fLifetime = lifetime; }

void PositroniumHistograms::setPositionHistogramParams( const unsigned int& bins, const double& minx, const double& maxx )
{
 fMinPos = minx;
 fMaxPos = maxx;
 fBinsPos = bins;
}

void PositroniumHistograms::init( bool prompt_simulated )
{
 fDataWithPrompt = prompt_simulated;
 initHistograms( "_Ps" );
}

void PositroniumHistograms::MiniHit::fill( const Hit& hit, const TVector3& source_position )
{
 fTime = hit.getTime();
 fPosition = hit.getPosition();
 fMomentumDirection = hit.getMomentumDirection();
 fEnergyDeposition = hit.getEnergyDeposition();
 fSourcePosition = source_position;
}

TH1D* PositroniumHistograms::get1DHistogram( std::string name, unsigned int bins, double minx, double maxx, std::string axis_x_name, std::string axis_y_name )
{
 TH1D* h = new TH1D( name.c_str(), "", bins, minx, maxx );
 h->GetXaxis()->SetTitle( axis_x_name.c_str() );
 h->GetYaxis()->SetTitle( axis_y_name.c_str() );
 return h;
}

TH2D* PositroniumHistograms::get2DHistogram( std::string name, unsigned int bins, double minxx, double maxxy, std::string axis_x_name, std::string axis_y_name )
{
 TH2D* h = new TH2D( name.c_str(), "", bins, minxx, maxxy, bins, minxx, maxxy );
 h->GetXaxis()->SetTitle( axis_x_name.c_str() );
 h->GetYaxis()->SetTitle( axis_y_name.c_str() );
 return h;
}

void PositroniumHistograms::initHistograms( std::string title )
{
 fTitle = title;
 std::cout << "[?] " << fBinsTime << " " << fMinTime << " " << fMaxTime << std::endl;
 hLifetime.reset( get1DHistogram( "Lifetime" + title, fBinsTime, fMinTime, fMaxTime, " T_{life} [ns]", "Counts" ) );
 hEnergyDeposition.reset( get1DHistogram( "EnergyDeposition" + title, 1000, -0.5, 2000.5, "#Delta E [keV]", "Counts" ) );
 hEnergyDepositionPrompt.reset( get1DHistogram( "EnergyDepositionPrompt" + title, 1000, -0.5, 2000.5, "#Delta E [keV]", "Counts" ) );
 hEnergyDepositionAnnihilation.reset( get1DHistogram( "EnergyDepositionAnnihilation" + title, 1000, -0.5, 2000.5, "#Delta E [keV]", "Counts" ) );
 hSourcePosition.reset( get2DHistogram( "SourcePosition" + title, fBinsPos, fMinPos, fMaxPos, "x [cm]", "y [cm]" ) );
}

std::map<int, PositroniumHistograms::MiniHit> PositroniumHistograms::getFirstHits( const Event& event )
{
 std::vector<Track> tracks = event.getTracks();
 std::map<int, PositroniumHistograms::MiniHit> first_hits;

 for ( std::vector<Track>::iterator itrack = tracks.begin(); itrack != tracks.end(); ++itrack )
 {
  int trackID = itrack->getID();
  PositroniumHistograms::MiniHit mh;
  mh.fill( (itrack->getHits())[0], itrack->getSourcePosition() );
  first_hits.emplace( trackID, mh );
 }
 return first_hits;
}

void PositroniumHistograms::tryFillLifeTimePlot( std::map<int, MiniHit> hits )
{
 if ( !fDataWithPrompt ) { return; }

 //at least prompt gamma and one annihilation gamma
 if ( hits.size() < 2 ) { return; }

 std::map<int, MiniHit>::iterator found_prompt_hit =  hits.find( kPromptGammaTrackID );
 
 if ( found_prompt_hit == hits.end() ) { return; }

 std::map<int, MiniHit>::iterator found_annihilation_hit;
 for ( int track_id = kPromptGammaTrackID + 1; track_id < kPromptGammaTrackID + fAnnihilationGammasNumber; ++track_id )
 {
  found_annihilation_hit = hits.find( track_id );
  if (  found_annihilation_hit != hits.end() ) { break; }
 }

 if ( found_annihilation_hit == hits.end() ) { return; }

 double t_prompt = found_prompt_hit->second.fTime;
 double t_event_init = t_prompt - getTOF( found_prompt_hit->second.fPosition, found_prompt_hit->second.fSourcePosition );
 double t_ann = found_annihilation_hit->second.fTime;
 double t_lifetime = t_ann - getTOF( found_annihilation_hit->second.fPosition, found_annihilation_hit->second.fSourcePosition ) - t_event_init;

 hLifetime->Fill( t_lifetime ); 
}

double PositroniumHistograms::getTOF( const TVector3& hit_position, const TVector3& source_position )
{
 return TMath::Abs( (hit_position-source_position).Mag() / kLightVelocityVacuum );
}

void PositroniumHistograms::fillEnergyDepositionPlots( std::map<int, MiniHit> hits )
{
 for ( std::map<int, MiniHit>::iterator imh = hits.begin(); imh != hits.end(); ++imh )
 {
  double energy_deposition = imh->second.fEnergyDeposition;

  if ( fDataWithPrompt && imh->first == kPromptGammaTrackID ) { hEnergyDepositionPrompt->Fill( energy_deposition ); }
  else { hEnergyDepositionAnnihilation->Fill( energy_deposition ); }

  hEnergyDeposition->Fill( energy_deposition );
 }
}

void PositroniumHistograms::fillSourcePositionPlot( std::map<int, MiniHit> hits )
{
 if ( hits.size() == 0 ) { return; }
 TVector3 sp = hits.begin()->second.fSourcePosition;
 hSourcePosition->Fill( sp.x(), sp.y() );
}

std::string PositroniumHistograms::getImgName( TObject* h )
{
 std::string name = std::string( h->GetName() ) + ".png";
 return name;
}

void PositroniumHistograms::fill( const Event& event )
{
 std::map<int, PositroniumHistograms::MiniHit> hits = getFirstHits( event );
 tryFillLifeTimePlot( hits );
 fillEnergyDepositionPlots( hits );
 fillSourcePositionPlot( hits );
}

void PositroniumHistograms::draw( const TCanvas& c )
{
 hLifetime->Draw( "hist" );
 if ( fLifetime > 0.0 )
 {
  //Let's evaluate theoretical lifetime exponent and draw it
  double A = hLifetime->GetBinContent( hLifetime->FindBin( 0.0 ) );
  double B = hLifetime->GetBinContent( hLifetime->FindBin( fMaxTime ) ) - A * TMath::Exp( (-1.0) * fMaxTime / fLifetime );
  TF1 f( "lifetime_fun", [&](Double_t * t, Double_t *) { return A * TMath::Exp( (-1.0) * t[0] / fLifetime ) + B; }, fMinTime, fMaxTime, 0 );
  f.SetLineColor(2);
  f.Draw("same L");
  c.Print( getImgName( hLifetime.get() ).c_str() );
 } else { c.Print( getImgName( hLifetime.get() ).c_str() ); }

 hEnergyDeposition->Draw( "hist" );
 c.Print( getImgName( hEnergyDeposition.get() ).c_str() );

 hEnergyDepositionPrompt->Draw( "hist" );
 c.Print( getImgName( hEnergyDepositionPrompt.get() ).c_str() );

 hEnergyDepositionAnnihilation->Draw( "hist" );
 c.Print( getImgName( hEnergyDepositionAnnihilation.get() ).c_str() ); 

 hSourcePosition->Draw( "colz" );
 c.Print( getImgName( hSourcePosition.get() ).c_str() );

 hEnergyDeposition->Draw( "hist" );
 hEnergyDepositionPrompt->Draw( "hist same" );
 hEnergyDepositionPrompt->SetLineColor( 2 );
 hEnergyDepositionAnnihilation->Draw( "hist same" );
 hEnergyDepositionAnnihilation->SetLineColor( 3 );

 std::string img_name = "energy_deposition_spectra" + fTitle + ".png";
 c.Print( img_name.c_str() ); 
}

