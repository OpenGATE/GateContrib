/** ----------------------
  Copyright (C): OpenGATE Collaboration
  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See LICENSE.md for further details
  ----------------------*/
#include "Selector.h"
#include <cassert>

Selector::Selector() {}

Selector::~Selector()
{
 fHistos->draw( fCanvas );
}

void Selector::setEnablePrompt( bool enable ) { fEnablePrompt = enable; }

void Selector::setBinsTime( int bins ) { fBinsTime = bins; }

void Selector::setMinTime( double tmin ) { fMinTime = tmin; }

void Selector::setMaxTime( double tmax ) { fMaxTime = tmax; }

void Selector::setBinsPosition( int bins ) { fBinsPos = bins; }

void Selector::setMinPosition( double xymin ) { fMinPos = xymin; }

void Selector::setMaxPosition( double xymax ) { fMaxPos = xymax; }

void Selector::setModel( std::string model ) { fModel = model; }

void Selector::setFileName( std::string file_name ) { fFileName = file_name; }

void Selector::setLifetime( double lifetime ) { fLifetime = lifetime; }

void Selector::showParameters() const
{
 std::cout << "[INFO] Model                               : " << fModel << std::endl;
 std::cout << "[INFO] Prompt gamma                        : " << ( fEnablePrompt ? "ENABLE" : "DISABLE") << std::endl;
 std::cout << "[INFO] Time histogram - bins               : " << fBinsTime << std::endl;
 std::cout << "[INFO] Time histogram - min value          : " << fMinTime << " ns " << std::endl;
 std::cout << "[INFO] Time histogram - max value          : " << fMaxTime << " ns " << std::endl;
 std::cout << "[INFO] Lifetime                            : " << ( fLifetime > 0.0 ? std::to_string( fLifetime ) + " ns" : "DISABLE" ) << std::endl;
 std::cout << "[INFO] Position histogram - bins           : " << fBinsPos << std::endl;
 std::cout << "[INFO] Position histogram - min value (xy) : " << fMinPos << " cm" <<std::endl;
 std::cout << "[INFO] Position histogram - max value (xy) : " << fMaxPos << " cm" << std::endl;
}

void Selector::doJob()
{
 showParameters();

 if ( fModel == kParaPositroniumModel ) { fHistos.reset( new ParaPositroniumHistograms() ); } 
 else if ( fModel == kOrthoPositroniumModel ) { fHistos.reset( new OrthoPositroniumHistograms() ); } 
 else if ( fModel == kPositroniumModel ) 
 { 
  fHistos.reset( new PositroniumHistograms() ); 
  fHistos->setAnnihilationGammasNumber( 3 );//by default we assume that maximal number of annihilation gammas is 3
 }
 else { assert( false ); }

 fHistos->setLifeTimeHistogramParams( fBinsTime, fMinTime, fMaxTime  );
 fHistos->setPositionHistogramParams( fBinsPos, fMinPos, fMaxPos  );

 if ( fLifetime > 0.0 ) { fHistos->setLifetime( fLifetime ); }

 fHistos->init( fEnablePrompt );

 fReader.start( fFileName );
 std::cout << "[INFO] Reading file ... - start" << std::endl;
 while ( fReader.readNextEntry() )
 {
  if ( fReader.getPDGCode() != kGammaPDGCode  || fReader.getProcessName() != kComptonProcessName ) { continue; }

  if ( fEvent.getID() != fReader.getEventID() ) 
  { 
   addEvent(); 
  }
  addTrack();
  addHit();
 }
 std::cout << "[INFO] Reading file ... - finished" << std::endl;
}

void Selector::addEvent()
{
 if ( fEvent.getID() != Event::NotDefined  ) { processEvent(); }
 fEvent = Event( fReader.getEventID() );
}

void Selector::addTrack()
{

 int track_id = fReader.getTrackID();
 int parent_id = fReader.getParentID();
 TVector3 source_position = fReader.getSourcePosition();
 if ( fEvent.getTracksNumber() == 0 || fEvent.getLastTrack()->getID() != track_id ) { fEvent.addTrack( Track( track_id, parent_id, source_position ) ); }

}

void Selector::addHit()
{
 double energy_deposition = fReader.getEnergyDeposition();
 double time = fReader.getTime();
 int n_compt_cristal = fReader.getNCristalCompton();
 TVector3 position = fReader.getPosition();
 TVector3 momentum = fReader.getMomentumDirection();
 

 fEvent.getLastTrack()->addHit( Hit( energy_deposition, time, n_compt_cristal, position, momentum ) );
}

void Selector::processEvent()
{
 fHistos->fill( fEvent );
}
