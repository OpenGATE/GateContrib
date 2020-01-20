/** ----------------------
  Copyright (C): OpenGATE Collaboration
  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See LICENSE.md for further details
  ----------------------*/
#ifndef Selector_h
#define Selector_h

#include "Event.h"
#include "Reader.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "ParaPositroniumHistograms.h"
#include "OrthoPositroniumHistograms.h"
#include <memory>

/** Author: Mateusz Bała
 *  Email: bala.mateusz@gmail.com
 *  Organization: J-PET (http://koza.if.uj.edu.pl/pet/)
 *  About class: Interprets and filters data received from reader and creates events ( with tracks and hits ) for further analysis.
 **/
class Selector
{
 public:
  Selector();
  ~Selector();
  void doJob();

  void setEnablePrompt( bool enable );
  void setBinsTime( int bins );
  void setMinTime( double tmin );
  void setMaxTime( double tmax );
  void setBinsPosition( int bins );
  void setMinPosition( double xymin );
  void setMaxPosition( double xymax );

  void setModel( std::string model );
  void setFileName( std::string file_name );
  void setLifetime( double lifetime );

 private:
  void addEvent();
  void processEvent();
  void addTrack();
  void addHit();
  void showParameters() const;  

 private:
  Reader fReader;
  Event fEvent;
  const int kGammaPDGCode = 22;
  const std::string kComptonProcessName = "compt";
  const std::string kParaPositroniumModel = "pPs";
  const std::string kOrthoPositroniumModel = "oPs";
  const std::string kPositroniumModel = "Ps";
  std::string fModel = "";

  double fMinTime = 0.0;
  double fMaxTime = 0.0;
  unsigned int fBinsTime = 0;
  double fLifetime = 0.0;
  
  double fMinPos = 0.0;
  double fMaxPos = 0.0;
  unsigned int fBinsPos = 0.0;

  bool fEnablePrompt = false;

  std::string fFileName = "";

  TCanvas fCanvas;
  std::unique_ptr<PositroniumHistograms> fHistos;
};

#endif
