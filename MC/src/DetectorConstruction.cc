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
// $Id: B1DetectorConstruction.cc 75117 2013-10-28 09:38:37Z gcosmo $
//
/// \file B1DetectorConstruction.cc
/// \brief Implementation of the B1DetectorConstruction class

#include "DetectorConstruction.hh"
#include "G4VisAttributes.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "SiSD.hh"
namespace SET10LI
{
  DetectorConstruction::DetectorConstruction()
    : G4VUserDetectorConstruction()
  { }



  DetectorConstruction::~DetectorConstruction()
  { }



  G4VPhysicalVolume*
  DetectorConstruction::Construct()
  {
    creatematerials();
    G4bool checkOverlaps = true;

    G4double world_sizeXY = 600*cm;
    G4double world_sizeZ  = 800*cm;

    G4LogicalVolume* logicWorld = create_exp_hall(0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);

    G4VPhysicalVolume* physWorld = new G4PVPlacement(0,                     //no rotation
			                                               G4ThreeVector(),       //at (0,0,0)
			                                               logicWorld,            //its logical volume
			                                               "expHall_phys",               //its name
			                                               0,                     //its mother  volume
			                                               false,                 //no boolean operation
			                                               0,                     //copy number
			                                               checkOverlaps);        //overlaps checking

    //chamber windowIn
    G4LogicalVolume* logicChWinIn = create_Chamber_WindowIn("ChWinIn", 1.*um, 8.*cm);		// thickness of the Chumber Window
                                    new G4PVPlacement(0,                       //no rotation
		                                                  G4ThreeVector(0,0,-26.65001*cm),         //at (0,0,0)
		                                                  logicChWinIn,             //its logical volume
		                                                  "ChamberWindowIn",                //its name
		                                                  logicWorld,              //its mother  volume
		                                                  false,                   //no boolean operation
		                                                  0,                       //copy number
		                                                  checkOverlaps);          //overlaps checking

    //chamber windowOut
    G4LogicalVolume* logicChWinOut = create_Chamber_WindowOut("ChWinOut", 1500.*um, 8.*cm);   // thickness of the Chumber Window
                                    new G4PVPlacement(0,                       //no rotation
                                                      G4ThreeVector(0,0,26.65*cm),         //at (0,0,0)
                                                      logicChWinOut,             //its logical volume
                                                      "ChamberWindowOut",                //its name
                                                      logicWorld,              //its mother  volume
                                                      false,                   //no boolean operation
                                                      0,                       //copy number
                                                      checkOverlaps);          //overlaps checking

/* 
    //target
    G4LogicalVolume* logictarget = create_target(Vacuum,
					                                     "target_log",
					                                     26.5*cm,	//gas 1/2 thick
					                                     7.75*cm,   // radius of target
                                               8.*cm);		//radius of chamber

                                  new G4PVPlacement(0,                       //no rotation
		                                                G4ThreeVector(),         //at (0,0,0)
		                                                logictarget,             //its logical volume
		                                                "target",                //its name
		                                                logicWorld,              //its mother  volume
		                                                false,                   //no boolean operation
		                                                0,                       //copy number
		                                                checkOverlaps);          //overlaps checking
                                                    */
    // DSRD
    G4LogicalVolume* logicDSRD = create_DSRD("DSRD_log",375*um);

                                  new G4PVPlacement(0,                       //no rotation
		                                                G4ThreeVector(-4.42*cm,4.42*cm,-19.39*cm),         //at (0,0,0)
		                                                logicDSRD,             //its logical volume
		                                                "DSRD",                //its name
		                                                logicWorld,              //its mother  volume
		                                                false,                   //no boolean operation
		                                                0,                       //copy number
		                                                checkOverlaps);          //overlaps checking


    //always return the physical World
    //
    return physWorld;
  }

  void
  DetectorConstruction::creatematerials()
  {
    using namespace CLHEP;
    G4NistManager* man = G4NistManager::Instance();
    man->SetVerbose(0);
    //create simple materials:
    Vacuum =  man->FindOrBuildMaterial("G4_Galactic");
    Si = man->FindOrBuildMaterial("G4_Si");
    Fe = man->FindOrBuildMaterial("G4_Fe");
    Ti = man->FindOrBuildMaterial("G4_Ti");
    //target material
  //  target_mat = new G4Material("H_t",0.0000052991*g/cm3,1); 
  //  G4Element * el_he = man->FindOrBuildElement("He");
  //  target_mat->AddElement(el_he,1);				// gas,liquid


  }

  G4LogicalVolume*
  DetectorConstruction::create_exp_hall(G4double x, G4double y,G4double z)
  {
    // create experimental hall
    G4Box* experimentalHall_box = new G4Box("expHall_box",x,y,z);
    G4LogicalVolume* experimentalHall_log = new G4LogicalVolume(experimentalHall_box, Vacuum,"expHall_log",0,0,0);
    experimentalHall_log->SetVisAttributes(new G4VisAttributes(false));
    return experimentalHall_log;
  }

  G4LogicalVolume*
  DetectorConstruction::create_Chamber_WindowIn(G4String name,double thickness,double radius=1*CLHEP::cm)
  {
    G4String wname =name;
     wname+="_tube";
     G4Tubs* ChWinIn = new G4Tubs(wname,0.0,radius,thickness,0.*deg,360.*deg); 
     G4String lname =name;
     lname+="_log";
     G4LogicalVolume* ChWinIn_log  = new G4LogicalVolume(ChWinIn,Ti,lname,0,0,0);    
     ChWinIn_log-> SetVisAttributes(new G4VisAttributes(true,G4Color::Yellow()));
     return ChWinIn_log;
  }

  G4LogicalVolume*
  DetectorConstruction::create_Chamber_WindowOut(G4String name,double thickness,double radius=1*CLHEP::cm)
  {
    G4String wname =name;
     wname+="_tube";
     G4Tubs* ChWinOut = new G4Tubs(wname,0.0, radius,thickness,0.*deg,360.*deg); 
     G4String lname =name;
     lname+="_log";
     G4LogicalVolume* ChWinOut_log  = new G4LogicalVolume(ChWinOut,Fe,lname,0,0,0);  
     ChWinOut_log-> SetVisAttributes(new G4VisAttributes(true,G4Color::Yellow()));  
     return ChWinOut_log;
  }
/*

  G4LogicalVolume*
  DetectorConstruction::create_target(G4Material * mat, G4String name, double thickness, double radiusT=1*CLHEP::cm, double radiusCh=1*CLHEP::cm)
  {
    using namespace CLHEP;
    // Create target H will be used for body, Fe --- for walls
    // chamber material
    G4String tname =name;
    tname+="_tub";
    G4Tubs* target_tub = new G4Tubs(tname,0.0,radiusCh,thickness,0.*deg,360.*deg);
    G4String lname =name;
    lname+="_log";
    G4LogicalVolume* target_log  = new G4LogicalVolume(target_tub,Fe,lname,0,0,0);
    target_log-> SetVisAttributes(new G4VisAttributes(new G4VisAttributes(false)));

    G4String tbname =name;
    tbname+="_body_tub";
    // helium
    G4Tubs* target_body_tub = new G4Tubs(tbname,0.0,radiusT,thickness,0.*deg,360.*deg);
    G4String lbname =name;
    lbname+="_body_log";
    G4LogicalVolume* target_body_log = new G4LogicalVolume(target_body_tub, mat,lbname,0,0,0);
    target_body_log-> SetVisAttributes(new G4VisAttributes(false));
    // target_body_log->SetVisAttributes(vis_target);
    G4String bname =name;
    bname+="_body";
    new G4PVPlacement(0,G4ThreeVector(), target_body_log,bname,target_log,false,0);
    return target_log ;
  }
*/
  G4LogicalVolume*
  DetectorConstruction::create_DSRD(G4String name, double thickness)
  {
    using namespace CLHEP;

    // create double side ring detector
    const double deadlayer= 0.8*um;
    G4String tname =name;
    tname+="_tub";
  //  G4Tubs* DSRD_tub = new G4Tubs(tname,0.0*mm,0.5*mm,thickness*0.5, 0.*deg,360.*deg);
    G4Tubs* DSRD_tub = new G4Tubs(tname,0.0*mm,7*mm,thickness*0.5, 0.*deg,360.*deg);
    G4String lname =name;
    lname+="_log";
    G4LogicalVolume* DSRD_log = new G4LogicalVolume(DSRD_tub,Si,lname,0,0,0);

    DSRD_log -> SetVisAttributes(new G4VisAttributes(true,G4Colour(0,1,0,0.1)));

    double DSRDslthick = thickness*0.5- deadlayer;
    G4String tbname =name;
    tbname+="_sense_tub";
  //  G4Tubs* DSRD_sl_tub = new G4Tubs(tbname,0*mm,0.5*mm,DSRDslthick,0.*deg,360.*deg);
    G4Tubs* DSRD_sl_tub = new G4Tubs(tbname,0*mm,7*mm,DSRDslthick,0.*deg,360.*deg);
    G4String lsname =name;
    lsname+="_sense_log";    // Envelope parameters


    G4LogicalVolume* DSRD_sense_layer_log = new G4LogicalVolume(DSRD_sl_tub, Si,lsname,0,0,0);
    DSRD_sense_layer_log-> SetVisAttributes(new G4VisAttributes(true,G4Color::Green()));
    G4ThreeVector body_pos(0.0*cm,0.0*cm,0*cm);
    G4String sname =name;
    sname+="_sense";
    new G4PVPlacement(0,body_pos, DSRD_sense_layer_log,sname, DSRD_log,false,0);

    //------------------------------------------------------------------
    // Sensitive Detector
    //------------------------------------------------------------------

    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    G4String sdname = "/sense/";
    sdname+=name;
    SiSD * SD = new SiSD(sdname);
    SDman->AddNewDetector(SD);
    DSRD_sense_layer_log->SetSensitiveDetector(SD);
    return DSRD_log;
  }

}
