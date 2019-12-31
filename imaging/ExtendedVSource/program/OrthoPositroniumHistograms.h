/** ----------------------
  Copyright (C): OpenGATE Collaboration
  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See LICENSE.md for further details
  ----------------------*/
#ifndef OrthoPositroniumHistograms_h
#define OrthoPositroniumHistograms_h

#include "Event.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TH2D.h"
#include "PositroniumHistograms.h"

/** Author: Mateusz Bała
 *  Email: bala.mateusz@gmail.com
 *  Organization: J-PET (http://koza.if.uj.edu.pl/pet/)
 *  About class: For received event fills histograms for orthopositronium
 **/
class OrthoPositroniumHistograms : public PositroniumHistograms
{
 public:
  OrthoPositroniumHistograms() {}
  virtual ~OrthoPositroniumHistograms() {}
  virtual void init( bool prompt_simulated );
  virtual void fill( const Event& event );
  virtual void draw( const TCanvas& c );
  void fillScatteringAnglesPlot( std::map<int, PositroniumHistograms::MiniHit> hits );
 private:
  std::unique_ptr<TH2D> hAngleDistribution;
  std::unique_ptr<TH2D> hAngleDistributionScattered;
};

#endif
