/** ----------------------
  Copyright (C): OpenGATE Collaboration
  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See LICENSE.md for further details
  ----------------------*/
#ifndef PositroniumHistograms_h
#define PositroniumHistograms_h

#include "TH1D.h"
#include "TH2D.h"
#include "TVector3.h"
#include "TCanvas.h"
#include "Hit.h"
#include "Event.h"
#include <memory>
#include <map>
#include <string>

/** Author: Mateusz Bała
 *  Email: bala.mateusz@gmail.com
 *  Organization: J-PET (http://koza.if.uj.edu.pl/pet/)
 *  About class: For received event fills histograms for positronium
 **/
class PositroniumHistograms
{
 public:

  struct MiniHit
  {
   double fTime = 0.0;
   TVector3 fPosition = TVector3( 0.0, 0.0, 0.0 );
   TVector3 fMomentumDirection = TVector3( 0.0, 0.0, 0.0 );
   double fEnergyDeposition = 0.0;
   TVector3 fSourcePosition = TVector3( 0.0, 0.0, 0.0 );

   void fill( const Hit& hit, const TVector3& source_position  );
  };

  PositroniumHistograms();
  virtual ~PositroniumHistograms();

  void setPromptGammaEnable( const bool& enable );
  void setAnnihilationGammasNumber( const int& n );

  void setLifeTimeHistogramParams( const unsigned int& bins, const double& minx, const double& maxx );
  void setPositionHistogramParams( const unsigned int& bins, const double& minx, const double& maxx );

  void setLifetime( const double& lifetime );

  void initHistograms( std::string title = "" );

  std::map<int, MiniHit> getFirstHits( const Event& event );
  void tryFillLifeTimePlot( std::map<int, MiniHit> hits );
  void fillEnergyDepositionPlots( std::map<int, MiniHit> hits );
  void fillSourcePositionPlot( std::map<int, MiniHit> hits );
  
  double getTOF( const TVector3& hit_position, const TVector3& source_position );

  std::string getImgName( TObject* h );
  virtual void draw( const TCanvas& c );

  TH1D* get1DHistogram( std::string name, unsigned int bins, double minx, double maxx, std::string axis_x_name, std::string axis_y_name );
  TH2D* get2DHistogram( std::string name, unsigned int bins, double minxy, double maxxy, std::string axis_x_name, std::string axis_y_name );

  virtual void fill( const Event& event );
  virtual void init( bool prompt_simulated );

 protected:
  bool fDataWithPrompt = false;
  const int kPromptGammaTrackID = 1;
  int fAnnihilationGammasNumber = 1;
  const double kLightVelocityVacuum = 29.9792458; //cm/ns

  std::string fTitle = "_Ps";
 //Histograms
  std::unique_ptr<TH1D> hLifetime;
  std::unique_ptr<TH1D> hEnergyDeposition;
  std::unique_ptr<TH1D> hEnergyDepositionPrompt;
  std::unique_ptr<TH1D> hEnergyDepositionAnnihilation;
  std::unique_ptr<TH2D> hSourcePosition;

  double fMinTime = 0.0;
  double fMaxTime = 0.0;
  unsigned int fBinsTime = 0;
  double fLifetime = 0.0;
  
  double fMinPos = 0.0;
  double fMaxPos = 0.0;
  unsigned int fBinsPos = 0.0;
};

#endif
