/** ----------------------
  Copyright (C): OpenGATE Collaboration
  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See LICENSE.md for further details
  ----------------------*/
#ifndef ParaPositroniumHistograms_h
#define ParaPositroniumHistograms_h

#include "Event.h"
#include "TCanvas.h"
#include "PositroniumHistograms.h"

/** Author: Mateusz Bała
 *  Email: bala.mateusz@gmail.com
 *  Organization: J-PET (http://koza.if.uj.edu.pl/pet/)
 *  About class: For received event fills histograms for parapositronium
 **/
class ParaPositroniumHistograms : public PositroniumHistograms
{
 public:
  ParaPositroniumHistograms() {}
  virtual ~ParaPositroniumHistograms() {}
  virtual void init( bool prompt_simulated );
  virtual void fill( const Event& event );
  virtual void draw( const TCanvas& c );
};

#endif
