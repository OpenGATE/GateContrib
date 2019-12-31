/** ----------------------
  Copyright (C): OpenGATE Collaboration
  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See LICENSE.md for further details
  ----------------------*/
#include "OrthoPositroniumHistograms.h"
#include "Hit.h"
#include <string>
#include<iostream>

void OrthoPositroniumHistograms::init( bool prompt_simulated )
{
 setPromptGammaEnable( prompt_simulated );
 setAnnihilationGammasNumber( 3 );

 std::string title = "_oPs";
 initHistograms( title );
 hAngleDistribution.reset( get2DHistogram( "AngleDistribution" + title,  180, -0.5, 180.5, "#theta_{12} [deg]", "#theta_{23} [deg]" ) );
 hAngleDistributionScattered.reset( get2DHistogram( "AngleDistributionScattered" + title,  180, -0.5, 180.5, "#theta_{12} [deg]", "#theta_{23} [deg]" ) );
}

void OrthoPositroniumHistograms::fillScatteringAnglesPlot( std::map<int, PositroniumHistograms::MiniHit> hits )
{
 int gamma_index = fDataWithPrompt ? kPromptGammaTrackID : 0;
 std::map<int, PositroniumHistograms::MiniHit>::iterator h1 = hits.find( ++gamma_index );
 std::map<int, PositroniumHistograms::MiniHit>::iterator h2 = hits.find( ++gamma_index ); 
 std::map<int, PositroniumHistograms::MiniHit>::iterator h3 = hits.find( ++gamma_index ); 

 if ( h1 == hits.end() || h2 == hits.end() || h3 == hits.end() ) { return; }

 TVector3 p1 = h1->second.fPosition;
 TVector3 p2 = h2->second.fPosition;
 TVector3 p3 = h3->second.fPosition;

 std::vector<double> thetas =  std::vector<double>(3,0.0);
 thetas[0] = p1.Angle( p2 ) * TMath::RadToDeg();
 thetas[1] = p1.Angle( p3 ) * TMath::RadToDeg();
 thetas[2] = p2.Angle( p3 ) * TMath::RadToDeg(); 

 std::sort( thetas.begin(), thetas.end() );
 hAngleDistribution->Fill( thetas[0], thetas[1] );

 TVector3 md1 = h1->second.fMomentumDirection;
 TVector3 md2 = h2->second.fMomentumDirection;
 TVector3 md3 = h3->second.fMomentumDirection;

 thetas[0] = md1.Angle( md2 ) * TMath::RadToDeg();
 thetas[1] = md1.Angle( md3 ) * TMath::RadToDeg();
 thetas[2] = md2.Angle( md3 ) * TMath::RadToDeg(); 

 std::sort( thetas.begin(), thetas.end() );  
 hAngleDistributionScattered->Fill( thetas[0], thetas[1] ); 
}

void OrthoPositroniumHistograms::fill( const Event& event )
{
 std::map<int, PositroniumHistograms::MiniHit> hits = getFirstHits( event );
 tryFillLifeTimePlot( hits );
 fillEnergyDepositionPlots( hits );
 fillSourcePositionPlot( hits ); 
 fillScatteringAnglesPlot( hits );
}

void OrthoPositroniumHistograms::draw( const TCanvas& c )
{
 PositroniumHistograms::draw( c );

 hAngleDistribution->Draw("colz");
 c.Print( getImgName( hAngleDistribution.get() ).c_str() );

 hAngleDistributionScattered->Draw("colz");
 c.Print( getImgName( hAngleDistributionScattered.get() ).c_str() );
}
