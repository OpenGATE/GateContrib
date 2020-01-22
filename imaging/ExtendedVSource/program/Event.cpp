/** ----------------------
  Copyright (C): OpenGATE Collaboration
  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See LICENSE.md for further details
  ----------------------*/
#include "Event.h"

Event::Event( const int& event_id ) { fID = event_id; }
  
void Event::addTrack( const Track& track ) { fTracks.push_back( track ); }
  
std::vector<Track> Event::getTracks() const { return fTracks; }
  
unsigned int Event::getTracksNumber() const { return fTracks.size(); }

int Event::getID() const { return fID; }

Track* Event::getLastTrack() { return &fTracks[ fTracks.size() - 1 ]; }

Track* Event::getTrack( const int& track_id )
{
 unsigned int N = fTracks.size();
 for ( unsigned int track_index = 0; track_index < N; ++track_index )
 {
  if ( fTracks[track_index].getID() == track_id ) { return &fTracks[track_index]; }
 }
 return nullptr;
}
