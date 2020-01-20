/** ----------------------
  Copyright (C): OpenGATE Collaboration
  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See LICENSE.md for further details
  ----------------------*/
#include "ParaPositroniumHistograms.h"
#include "Hit.h"
#include <string>

void ParaPositroniumHistograms::init( bool prompt_simulated )
{
 setPromptGammaEnable( prompt_simulated );
 setAnnihilationGammasNumber( 2 );
 initHistograms( "_pPs" );
}

void ParaPositroniumHistograms::fill( const Event& event )
{
 PositroniumHistograms::fill( event );
}

void ParaPositroniumHistograms::draw( const TCanvas& c )
{
 PositroniumHistograms::draw( c );
}

