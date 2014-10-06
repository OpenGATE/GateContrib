/*----------------------
   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See GATE/LICENSE.txt for further details
----------------------*/


#ifndef GateCoincidenceTimeDiffSelectorMessenger_h
#define GateCoincidenceTimeDiffSelectorMessenger_h 1

#include "GatePulseProcessorMessenger.hh"

class G4UIdirectory;
class G4UIcmdWithoutParameter;
class G4UIcmdWithAString;
class G4UIcmdWithABool;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADouble;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWith3Vector;
class G4UIcmdWith3VectorAndUnit;

class GateCoincidenceTimeDiffSelector;

class GateCoincidenceTimeDiffSelectorMessenger: public GateClockDependentMessenger
{
public:
  GateCoincidenceTimeDiffSelectorMessenger(GateCoincidenceTimeDiffSelector* itsTimeDiffSelector);
  virtual ~GateCoincidenceTimeDiffSelectorMessenger();

  inline void SetNewValue(G4UIcommand* aCommand, G4String aString);

  inline GateCoincidenceTimeDiffSelector* GetTimeDiffSelector(){ return (GateCoincidenceTimeDiffSelector*) GetClockDependent(); }

private:
  G4UIcmdWithADoubleAndUnit *minTimeCmd; //!< set the min time window
  G4UIcmdWithADoubleAndUnit *maxTimeCmd; //!< set the max time window
};

#endif