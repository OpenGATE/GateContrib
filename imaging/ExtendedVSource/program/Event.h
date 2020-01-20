/** ----------------------
  Copyright (C): OpenGATE Collaboration
  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See LICENSE.md for further details
  ----------------------*/
#ifndef Event_h
#define Event_h

#include "Track.h"
#include <vector>

/** Author: Mateusz Bała
 *  Email: bala.mateusz@gmail.com
 *  Organization: J-PET (http://koza.if.uj.edu.pl/pet/)
 *  About class: Simple representation of event
 **/
class Event
{
 public:
  Event () {}
  Event( const int& event_id );
  void addTrack( const Track& track );
  std::vector<Track> getTracks() const;
  unsigned int getTracksNumber() const; 
  int getID() const; 
  Track* getLastTrack();
  Track* getTrack( const int& track_id );
  
  static const int NotDefined = -1;

 private:
  int fID = NotDefined;
  std::vector<Track> fTracks = {};
};

#endif
