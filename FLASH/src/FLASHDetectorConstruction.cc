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
// * technical work of the GEANT4 appaboration.                      *
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

#include <cmath>
#include "G4SystemOfUnits.hh"
#include "globals.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"
#include "G4GeometryManager.hh"
#include "G4SolidStore.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"
#include "G4Colour.hh"
#include "G4UserLimits.hh"
#include "G4UnitsTable.hh"
#include "G4VisAttributes.hh"
#include "G4NistManager.hh"
#include "FLASHDetectorConstruction.hh"
#include "G4Tubs.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSDoseDeposit3D.hh"
#include "FLASHDetectorMessenger.hh"

/////////////////////////////////////////////////////////////////////////////
FLASHDetectorConstruction::FLASHDetectorConstruction(G4VPhysicalVolume* physicalTreatmentRoom)
  : motherPhys(physicalTreatmentRoom), // pointer to WORLD volume 
    phantom(0), detector(0),
    phantomLogicalVolume(0), detectorLogicalVolume(0), 
    phantomPhysicalVolume(0), detectorPhysicalVolume(0),
    aRegion(0)

{

  

  // Messenger to change parameters of the phantom/detector geometry
  detectorMessenger = new FLASHDetectorMessenger(this);

  // Define here the material of the water phantom and of the detector
  SetPhantomMaterial("G4_WATER"); 

  // Construct geometry (messenger commands)

  // Detector
  // Default detector sizes in cm!!!!
  detectorSizeX = 6.* cm;
  detectorSizeY = 10.* cm;
  detectorSizeZ = 10.* cm;

  SetDetectorSize(detectorSizeX,  detectorSizeY,  detectorSizeZ); 
 
  // Phantom 
  SetPhantomSize(20. *cm, 20. *cm, 20. *cm);   
  SetPhantomPosition(G4ThreeVector(-99.4 *mm, 0. *mm, 0. *mm)); 
  SetDetectorToPhantomPosition(G4ThreeVector(0 *mm, 50 *mm, 50 *mm));  

 

  // Write virtual parameters to the real ones and check for consistency      
  UpdateGeometry(); 
}

/////////////////////////////////////////////////////////////////////////////
FLASHDetectorConstruction::~FLASHDetectorConstruction()
{ 
    delete detectorMessenger;
}

/////////////////////////////////////////////////////////////////////////////
// ConstructPhantom() is the method that reconstuct a water box (called phantom 
// (or water phantom)). 
// A water phantom can be considered a good
// approximation of a an human body. 
////////////////////////////////////////////////////////////////////////////

void FLASHDetectorConstruction::ConstructPhantom()
{
    // Definition of the solid volume of the Phantom
    phantom = new G4Box("Phantom", 
			phantomSizeX/2, 
			phantomSizeY/2, 
			phantomSizeZ/2);
    
// Definition of the logical volume of the Phantom
    phantomLogicalVolume = new G4LogicalVolume(phantom,	
					     phantomMaterial, 
					     "phantomLog", 0, 0, 0);
  
    // Definition of the physics volume of the Phantom
    phantomPhysicalVolume = new G4PVPlacement(0,
	                                    phantomPosition,
					    "phantomPhys",
					    phantomLogicalVolume,
					    motherPhys,
					    false,
					    0);

// Visualisation attributes of the phantom
    red = new G4VisAttributes(G4Colour(0/255., 255/255. ,0/255.));
    red -> SetVisibility(true);
    //red -> SetForceSolid(true);
    //red -> SetForceWireframe(true);
    phantomLogicalVolume -> SetVisAttributes(red); 
    //phantomLogicalVolume -> SetVisAttributes(G4VisAttributes::GetInvisible());
}

/////////////////////////////////////////////////////////////////////////////
// ConstructDetector() it the method the reconstruct a detector region 
// inside the water phantom. It is a volume, located inside the water phantom
// and with two coincident faces:
//
//           **************************
//           *   water phantom        *
//           *                        *
//           *                        *
//           *---------------         *
//  Beam     *              -         *
//  ----->   * detector     -         *
//           *              -         *
//           *---------------         *
//           *                        *
//           *                        *
//           *                        *
//           **************************
//

void FLASHDetectorConstruction::ConstructDetector()
{

    // Definition of the solid volume of the Detector
    detector = new G4Box("Detector", 
			 detectorSizeX/2, 
			 detectorSizeY/2, 
			 detectorSizeZ/2);
    
    // Definition of the logic volume of the Phantom
    detectorLogicalVolume = new G4LogicalVolume(detector,
						detectorMaterial,
						"DetectorLog",
						0,0,0);
// Definition of the physical volume of the Phantom 
    detectorPhysicalVolume = new G4PVPlacement(0, 
					       detectorPosition, // Setted by displacement 
					       "DetectorPhys", 
					       detectorLogicalVolume, 
					       phantomPhysicalVolume, 
					       false,0);

// Visualisation attributes of the detector 
   
    G4VisAttributes * skyBlue1 = new G4VisAttributes( G4Colour(135/255. , 206/255. ,  235/255. ));
    detectorLogicalVolume -> SetVisAttributes(skyBlue1);
   
  // **************
  // Cut per Region    
  // **************
  
  // A smaller cut is fixed in the phantom to calculate the energy deposit with the
  // required accuracy 
    if (!aRegion)
    {
	aRegion = new G4Region("DetectorLog");
	detectorLogicalVolume -> SetRegion(aRegion);
	aRegion -> AddRootLogicalVolume(detectorLogicalVolume);
    }
 G4cout << "The Detector has been built --- Add a scoring mesh for it  in the GUI if appropriate (similar to the phantom one)" << G4endl;
 
}


/////////////////////////////////////////////////////////////////////////////

void  FLASHDetectorConstruction::ParametersCheck()
{
    // Check phantom/detector sizes & relative position
    if (!IsInside(detectorSizeX, 
		detectorSizeY, 
		detectorSizeZ,
		phantomSizeX,
		phantomSizeY,
		phantomSizeZ,
		detectorToPhantomPosition
		))
      G4Exception("FLASHDetectorConstruction::ParametersCheck()", "FLASH0001", FatalException, "Error: Detector is not fully inside Phantom!");
}

/////////////////
// MESSENGERS //
////////////////

G4bool FLASHDetectorConstruction::SetPhantomMaterial(G4String material)
{

    if (G4Material* pMat = G4NistManager::Instance()->FindOrBuildMaterial(material, false) )
    {
	phantomMaterial  = pMat;
	detectorMaterial = pMat;
	if (detectorLogicalVolume && phantomLogicalVolume) 
	{
	    detectorLogicalVolume -> SetMaterial(pMat); 
	    phantomLogicalVolume ->  SetMaterial(pMat);

	    G4RunManager::GetRunManager() -> PhysicsHasBeenModified();
	    G4RunManager::GetRunManager() -> GeometryHasBeenModified();
	    G4cout << "The material of Phantom/Detector has been changed to " << material << G4endl;
	}
    }
    else
    {
	G4cout << "WARNING: material \"" << material << "\" doesn't exist in NIST elements/materials"
	    " table [located in $G4INSTALL/source/materials/src/G4NistMaterialBuilder.cc]" << G4endl; 
	G4cout << "Use command \"/parameter/nist\" to see full materials list!" << G4endl; 
	return false;
    }

    return true;
}




/////////////////////////////////////////////////////////////////////////////
void FLASHDetectorConstruction::SetPhantomSize(G4double sizeX, G4double sizeY, G4double sizeZ)
{
    if (sizeX > 0.) phantomSizeX = sizeX;
    if (sizeY > 0.) phantomSizeY = sizeY;
    if (sizeZ > 0.) phantomSizeZ = sizeZ;
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
void FLASHDetectorConstruction::SetDetectorSize(G4double sizeX, G4double sizeY, G4double sizeZ)
{
    if (sizeX > 0.) {detectorSizeX = sizeX;}
    if (sizeY > 0.) {detectorSizeY = sizeY;}
    if (sizeZ > 0.) {detectorSizeZ = sizeZ;}
}
/////////////////////////////////////////////////////////////////////////////

void FLASHDetectorConstruction::SetVoxelSize(G4double , G4double , G4double)
{
    G4cout<< "SetVoxelSize method is not needed anymore " << G4endl;
}
void FLASHDetectorConstruction::SetPhantomPosition(G4ThreeVector pos)
{
    phantomPosition = pos;
}

/////////////////////////////////////////////////////////////////////////////
void FLASHDetectorConstruction::SetDetectorToPhantomPosition(G4ThreeVector displ)
{
    detectorToPhantomPosition = displ;
}


////////////////////////////////////////////////////////////////////////////////
void FLASHDetectorConstruction::UpdateGeometry()
{
    /* 
     * Check parameters consistency
     */
    ParametersCheck();

    G4GeometryManager::GetInstance() -> OpenGeometry();
    if (phantom)
    {
	phantom -> SetXHalfLength(phantomSizeX/2);
	phantom -> SetYHalfLength(phantomSizeY/2);
	phantom -> SetZHalfLength(phantomSizeZ/2);
	phantomPhysicalVolume -> SetTranslation(phantomPosition);
    }
    else   ConstructPhantom();

    // Get the center of the detector 
    SetDetectorPosition();
    if (detector)
    {
	detector -> SetXHalfLength(detectorSizeX/2);
	detector -> SetYHalfLength(detectorSizeY/2);
	detector -> SetZHalfLength(detectorSizeZ/2);
	detectorPhysicalVolume -> SetTranslation(detectorPosition);      
    }
    else    ConstructDetector();

   

    // Inform the kernel about the new geometry
    G4RunManager::GetRunManager() -> GeometryHasBeenModified();
    G4RunManager::GetRunManager() -> PhysicsHasBeenModified();

    PrintParameters();
}



void FLASHDetectorConstruction::PrintParameters()
{

    G4cout << "The (X,Y,Z) dimensions of the phantom are : (" << 
	G4BestUnit( phantom -> GetXHalfLength()*2., "Length") << ',' << 
	G4BestUnit( phantom -> GetYHalfLength()*2., "Length") << ',' << 
	G4BestUnit( phantom -> GetZHalfLength()*2., "Length") << ')' << G4endl; 
    
    G4cout << "The (X,Y,Z) dimensions of the detector are : (" << 
	G4BestUnit( detector -> GetXHalfLength()*2., "Length") << ',' << 
	G4BestUnit( detector -> GetYHalfLength()*2., "Length") << ',' << 
	G4BestUnit( detector -> GetZHalfLength()*2., "Length") << ')' << G4endl; 

    G4cout << "Displacement between Phantom and World is: "; 
    G4cout << "DX= "<< G4BestUnit(phantomPosition.getX(),"Length") << 
	"DY= "<< G4BestUnit(phantomPosition.getY(),"Length") << 
	"DZ= "<< G4BestUnit(phantomPosition.getZ(),"Length") << G4endl;
}

