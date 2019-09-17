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


#include "PrimaryGeneratorAction.hh"
#include "ParticleInfo.hh"
//#include "Functions.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "TMath.h"
//#include "G4ParticleGun.hh"

#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include <fstream>
#include <iostream>
#include "G4NistManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

namespace SET10LI
{  

  
  PrimaryGeneratorAction::PrimaryGeneratorAction()
    : G4VUserPrimaryGeneratorAction()
  {    
    // default particle kinematic
    particletable = G4ParticleTable::GetParticleTable();
    iontable = G4IonTable::GetIonTable();

  }
  
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  PrimaryGeneratorAction::~PrimaryGeneratorAction()
  {

  }
  
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  void
  PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
  {

    pd13C = iontable->GetIon(6,13);
    pd48Ti = iontable->GetIon(22,48);
    beam_mean_T =CLHEP::RandFlat::shoot(13.5,12.5);

    double L_loss = CLHEP::RandFlat::shoot(-265002.,-265000.);
    double E_loss = (L_loss + 265002.)*0.001500;

    const double mass13C=pd13C->GetPDGMass();
    const double mass48Ti=pd48Ti->GetPDGMass();
    const double beam_T = beam_mean_T-E_loss;
    const double pin13C = sqrt(beam_T*beam_T+2*mass13C*beam_T);


    G4cout<<"masses in MeV\n"
	  <<"13C  = "<<mass13C<<G4endl
	  <<"48Ti = "<<mass48Ti<<G4endl;

    G4LorentzVector Vin13C(0,0,pin13C,beam_T+mass13C);
    G4LorentzVector V48Ti (0,0,0,mass48Ti);
    G4LorentzVector Vofcm = Vin13C+V48Ti;
    G4ThreeVector boost = Vofcm.boostVector();
    Vin13C.boost(-boost);
    V48Ti.boost(-boost);

    double theta_lab1 = 40.*double(CLHEP::pi)/180.;
    double theta_lab2 = 43.*double(CLHEP::pi)/180.;
    double ratio = 13./48.;
    double theta_cm1 = theta_lab1 + asin(ratio-sin(theta_lab1));
    double theta_cm2 = theta_lab2 + asin(ratio-sin(theta_lab2));
    
    double theta_cm = CLHEP::RandFlat::shoot(49.*double(CLHEP::pi)/180.,52.*double(CLHEP::pi)/180.);
    // double theta_cm = CLHEP::RandFlat::shoot(theta_cm1,theta_cm2);
    //double phi_cm = CLHEP::RandFlat::shoot(-40.*double(CLHEP::pi)/180.,-40.*double(CLHEP::pi)/180.);
    double phi_cm = CLHEP::RandFlat::shoot(135.*double(CLHEP::pi)/180.,135.*double(CLHEP::pi)/180.);


    V48Ti.setTheta(CLHEP::pi-theta_cm);
    V48Ti.setPhi(2*double(CLHEP::pi)-phi_cm);
    Vin13C.setTheta(theta_cm);
    Vin13C.setPhi(phi_cm);
    
    Vin13C.boost(boost);
    V48Ti.boost(boost);

    G4PrimaryParticle * pp13C = new G4PrimaryParticle(pd13C);
    pp13C->SetKineticEnergy(Vin13C.e()-Vin13C.mag());
    pp13C->SetMomentumDirection(Vin13C.vect().unit() );
    pp13C->SetCharge(6);
    pp13C->SetPolarization(0,0,0);
/*
    G4PrimaryParticle * pp48Ti = new G4PrimaryParticle(pd48Ti);
    pp48Ti->SetKineticEnergy(V48Ti.e()-V48Ti.mag());
    pp48Ti->SetMomentumDirection(V48Ti.vect().unit() );
    pp48Ti->SetCharge(22);
    pp48Ti->SetPolarization(0,0,0);

    ParticleInfo *INelasticINFO = new ParticleInfo;
    pp48Ti->SetUserInformation(INelasticINFO);
    INelasticINFO->Set_BeamEnergy(beam_T);
*/
    G4ThreeVector VertexPosition(0*um,0*um,L_loss*um);

    G4PrimaryVertex * PV = new G4PrimaryVertex(VertexPosition,0);
    PV->SetPrimary(pp13C);
//    PV->SetPrimary(pp48Ti);
 //   G4cout<<"************************************************** "<< G4endl;
    G4cout<<"  Event : " << anEvent->GetEventID()<< G4endl;
    G4cout<<"  Vertex position X, mm   :" << "   " << PV->GetX0() << G4endl;
    G4cout<<"  Vertex position Y, mm   :" << "   " << PV->GetY0() << G4endl;
    G4cout<<"  Vertex position Z, mm   :" << "   " << PV->GetZ0() << G4endl;
    G4cout<<"  Kinetic beam energy, MeV   :" << "   " << beam_T << G4endl;
    
    //*180./TMath::Pi()
    anEvent->AddPrimaryVertex(PV);

//    G4cout<<"  Save to file  "  << G4endl;
//    FILE *fp = fopen("KineticBeamEnergy.dat","a");
//    fprintf(fp,"%f\n",beam_T);
    


  }


}
