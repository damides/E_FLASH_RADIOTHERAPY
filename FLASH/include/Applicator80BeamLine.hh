//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Appaboration.  It is provided  under  the terms  and *
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

#ifndef Applicator80BeamLine_H
#define Applicator80BeamLine_H 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"

#include "G4Cons.hh"  
#include "G4SubtractionSolid.hh"  

class G4VPhysicalVolume;
class FLASHDetectorConstruction;
class Applicator80BeamLineMessenger;

class Applicator80BeamLine : public G4VUserDetectorConstruction
{
public:

 
   Applicator80BeamLine();
  ~Applicator80BeamLine();

  G4VPhysicalVolume* Construct();  


  void FlashBeamLineVacuumSource();
  void FlashBeamLineTitaniumWindows();
  void FlashBeamLineFirstApplicator();
  //void FlashBeamLineMonitorChambers();
  //void FlashBeamLineBlocks() ;
  void FlashBeamLineJunctions(); 
  void FlashBeamLineFinalApplicator();

  void SetInnerRadiusFirstApplicatorFLASH(G4double); //this sets the inner radius of the first applicator
  void SetOuterRadiusFirstApplicatorFLASH(G4double); //this sets the outer radius of the first applicator
  
  void SetInnerRadiusFinalApplicatorFLASH(G4double);
  // This method allows to change the size of the inner radius of the 
  // final applicator

  void SetOuterRadiusFinalApplicatorFLASH(G4double);
  // This method allows to change the size of the outer radius of the 
  // final applicator
  
  //  void SetFinalApplicatorFLASHMaterial(G4String);
  // This method allows to change the material 
  // of the final applicator

  
 
private:
//Applicator80 line dimensions
  void SetDefaultDimensions(); 
  void ConstructApplicator80BeamLine();

 
  Applicator80BeamLineMessenger* applicatorMessenger;  
  G4VPhysicalVolume* physicalTreatmentRoom;
  FLASHDetectorConstruction* flashDetectorConstruction; 

  G4VisAttributes* blue;
  G4VisAttributes* gray;
  G4VisAttributes* white;
  G4VisAttributes* red;
  G4VisAttributes* yellow;
  G4VisAttributes* green;
  G4VisAttributes* darkGreen;
  G4VisAttributes* darkOrange3;
  G4VisAttributes* skyBlue;
  G4VisAttributes* magenta;

  // First Applicator FLASH
  G4double innerRadiusFirstApplicatorFLASH, OuterRadiusFirstApplicatorFLASH;
  G4Tubs* solidFirstApplicatorFLASH;
  G4VPhysicalVolume* physiFirstApplicatorFLASH;
  G4Material* firstApplicatorMaterialFLASH;

   // Final Applicator FLASH
  G4double innerRadiusFinalApplicatorFLASH, OuterRadiusFinalApplicatorFLASH;
  G4Tubs* solidFinalApplicatorFLASH; 
  G4VPhysicalVolume* physiFinalApplicatorFLASH;
  G4Material* finalApplicatorMaterialFLASH;
  //oooooooooooooooooooooooooooooooOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOoooooooooooooooooo//

  // Junction 1 FINAL COLLIMATOR FLASH
  G4Tubs* solidGiunz1FinalAppFLASH; 
  G4VPhysicalVolume* physiGiunz1FinalAppFLASH;
  G4Material* Giunz1FinalAppMaterialFLASH;

  // Junction 2 FINAL COLLIMATOR FLASH
  G4Tubs* solidGiunz2FinalAppFLASH; 
  G4VPhysicalVolume* physiGiunz2FinalAppFLASH;
  G4Material* Giunz2FinalAppMaterialFLASH;

  // Junction 3 FINAL COLLIMATOR FLASH
  G4Tubs* solidGiunz3FinalAppFLASH; 
  G4VPhysicalVolume* physiGiunz3FinalAppFLASH;
  G4Material* Giunz3FinalAppMaterialFLASH;   

  // Junction 3 FINAL COLLIMATOR intFLASH
  G4Cons* solidGiunz3FinalAppIntFLASH; 
  G4Material* Giunz3FinalAppMaterialIntFLASH;
  G4VPhysicalVolume* physiGiunz3FinalAppIntFLASH;

  // Junction 4 FINAL COLLIMATOR FLASH
  G4Tubs* solidGiunz4FinalAppFLASH; 
  G4VPhysicalVolume* physiGiunz4FinalAppFLASH;
  G4Material* Giunz4FinalAppMaterialFLASH;

  // Junction 5 FINAL COLLIMATOR FLASH
  G4Tubs* solidGiunz5FinalAppFLASH; 
  G4VPhysicalVolume* physiGiunz5FinalAppFLASH;
  G4Material* Giunz5FinalAppMaterialFLASH;
  
  // protector1 
  G4Tubs* protector1; 
  G4VPhysicalVolume* physiprotector1;
  G4Material* protector1material;
  
  // protector2 
  G4Tubs* protector2; 
  G4VPhysicalVolume* physiprotector2;
  G4Material* protector2material;
  
  // protector3
  G4Tubs* protector3; 
  G4VPhysicalVolume* physiprotector3;
  G4Material* protector3material;
  
  // protector4
  G4Tubs* protector4; 
  G4VPhysicalVolume* physiprotector4;
  G4Material* protector4material;
  
  // cover 1  
  G4Tubs* cover1; 
  G4VPhysicalVolume* physicover1FLASH;
  G4Material* cover1material;
  
  // cover 2  
  G4Tubs* cover2; 
  G4VPhysicalVolume* physicover2FLASH;
  G4Material* cover2material;
  
  // cover 3  
  G4Tubs* cover3; 
  G4VPhysicalVolume* physicover3FLASH;
  G4Material* cover3material;
  
  //  Titanium Window
  G4Tubs* solidFTFLASH; 
  G4VPhysicalVolume* physiFTFLASH;
  G4Material* FTFLASHMaterialFLASH;
  
  //  Vacuum Source
  G4Tubs* solidVSFLASH; 
  G4VPhysicalVolume* physiVSFLASH;
  G4Material* VSFLASHMaterialFLASH;

 
};
#endif



