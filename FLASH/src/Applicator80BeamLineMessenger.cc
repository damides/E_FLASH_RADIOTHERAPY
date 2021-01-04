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

#include "Applicator80BeamLineMessenger.hh"//note:you have to add the option for all applicator and junctions
#include "Applicator80BeamLine.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"


    Applicator80BeamLineMessenger::Applicator80BeamLineMessenger(Applicator80BeamLine* beamLine)
:applicator80(beamLine)

{
    
    beamLineDir = new G4UIdirectory("/beamLine/");
    beamLineDir -> SetGuidance("set specification of range shifter");  

    FinalApplicatorFLASHDir = new G4UIdirectory("/beamLine/FinalApplicatorFLASH/");
    FinalApplicatorFLASHDir -> SetGuidance("set specification of final applicator");  

        
    innerRadiusFinalApplicatorFLASHCmd = new G4UIcmdWithADoubleAndUnit("/beamLine/FinalApplicatorFLASH/halfInnerRad",this);
    innerRadiusFinalApplicatorFLASHCmd -> SetGuidance("Set size of inner radius ( max 21.5 mm)");
    innerRadiusFinalApplicatorFLASHCmd -> SetParameterName("Size",false);
    innerRadiusFinalApplicatorFLASHCmd -> SetDefaultUnit("mm");  
    innerRadiusFinalApplicatorFLASHCmd -> SetUnitCandidates("mm cm m");  
    innerRadiusFinalApplicatorFLASHCmd -> AvailableForStates(G4State_Idle);

    OuterRadiusFinalApplicatorFLASHCmd = new G4UIcmdWithADoubleAndUnit("/beamLine/FinalApplicatorFLASH/halfOuterRad",this);
    OuterRadiusFinalApplicatorFLASHCmd -> SetGuidance("Set size of outer radius ( max 21.5 mm)");
    OuterRadiusFinalApplicatorFLASHCmd -> SetParameterName("Size",false);
    OuterRadiusFinalApplicatorFLASHCmd -> SetDefaultUnit("mm");  
    OuterRadiusFinalApplicatorFLASHCmd -> SetUnitCandidates("mm cm m");  
    OuterRadiusFinalApplicatorFLASHCmd -> AvailableForStates(G4State_Idle);

}

Applicator80BeamLineMessenger::~Applicator80BeamLineMessenger()
{ 

    delete OuterRadiusFinalApplicatorFLASHCmd; 
    delete innerRadiusFinalApplicatorFLASHCmd; 
    delete FinalApplicatorFLASHDir;  
    delete beamLineDir; 
     
 
}




void Applicator80BeamLineMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 

 
    if( command == innerRadiusFinalApplicatorFLASHCmd )
    { applicator80 -> SetInnerRadiusFinalApplicatorFLASH
	(innerRadiusFinalApplicatorFLASHCmd -> GetNewDoubleValue(newValue));}

    else if( command == OuterRadiusFinalApplicatorFLASHCmd )
    { applicator80 -> SetOuterRadiusFinalApplicatorFLASH
	(OuterRadiusFinalApplicatorFLASHCmd -> GetNewDoubleValue(newValue));}

}

