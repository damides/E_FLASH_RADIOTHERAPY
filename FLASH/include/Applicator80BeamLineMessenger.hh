//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// This is the first version of FLASH, a Geant4-based application
//
// 
//////////////////////////////////////////////////////////////////////////////////////////////

#ifndef Applicator80BeamLineMessenger_h
#define Applicator80BeamLineMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class Applicator80BeamLine;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;

class Applicator80BeamLineMessenger: public G4UImessenger
{
  public:
  Applicator80BeamLineMessenger(Applicator80BeamLine*);
  ~Applicator80BeamLineMessenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
private:

  // Pointer to the detector component
  Applicator80BeamLine* applicator80;

 
   G4UIdirectory* beamLineDir;  // Control of the beam line

   G4UIdirectory* FinalApplicatorFLASHDir;  // Control of the final applicator
   G4UIdirectory* FirstApplicatorFLASHDir;  // Control of the first applicator

  // G4UIcmdWithAString*   FinalApplicatorFLASHMatCmd;
  // UI command to set the material of the final applicator component of 
  // the beam line 
 
    G4UIcmdWithADoubleAndUnit* innerRadiusFinalApplicatorFLASHCmd;
    G4UIcmdWithADoubleAndUnit* innerRadiusFirstApplicatorFLASHCmd;
  // UI command to set the inner radius of the final applicator component of 
  // the beam line 

    G4UIcmdWithADoubleAndUnit* OuterRadiusFinalApplicatorFLASHCmd;
    G4UIcmdWithADoubleAndUnit* OuterRadiusFirstApplicatorFLASHCmd;

  // UI command to set the outer radius of the final applicator component of 
  // the beam line 
 
   
};
#endif

