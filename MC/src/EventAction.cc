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
// * work  make  any representation or  warranty, lv_Neutronpress or implied, *
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
// $Id: B1EventAction.cc 75117 2013-10-28 09:38:37Z gcosmo $
//
/// \file B1EventAction.cc
/// \brief Implementation of the B1EventAction class

#include "EventAction.hh"
//#include "B1Run.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "SiHit.hh"
#include "NDHit.hh"
#include "CLHEP/Random/RandGauss.h"

namespace SET10LI
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
{
  EventAction::EventAction()
    : G4UserEventAction(),
      fEdep(0.)
  {    
    store=false;
    tree =NULL;
    v13C=NULL;
    v48Ti=NULL;

  }

  EventAction::EventAction(TTree* T)
    : G4UserEventAction(),
      fEdep(0.)
  {

    store=true;
    tree =T;

    
    v13C=new TLorentzVector();
    v48Ti=new TLorentzVector();

    vr=new TVector3();
    tree->Bronch("v13C.","TLorentzVector",&v13C);
    tree->Bronch("v48Ti.","TLorentzVector",&v48Ti);
    tree->Bronch("vr.","TVector3",&vr);
    tree->Branch("Rdeposit",Rdeposit,"Rdeposit[16]/D");
    tree->Branch("rho",&rho,"rho/D");
    tree->Branch("phi",&phi,"phi/D");
    tree->Branch("Sim_theta48Ti",&Sim_theta48Ti,"Sim_theta48Ti/D");
    tree->Branch("Sim_phi48Ti",&Sim_phi48Ti,"Sim_phi48Ti/D");
    tree->Branch("Sim_energy48Ti",&Sim_energy48Ti,"Sim_energy48Ti/D");
    tree->Branch("Sim_theta13C",&Sim_theta13C,"Sim_theta13C/D");
    tree->Branch("Sim_phi13C",&Sim_phi13C,"Sim_phi13C/D");
    tree->Branch("Sim_energy13C",&Sim_energy13C,"Sim_energy13C/D");
    tree->Branch("EventID",&EventID,"EventID/I");
    tree->Branch("Sim_xbt",&Sim_xbt,"Sim_xbt/D");
    tree->Branch("Sim_ybt",&Sim_ybt,"Sim_ybt/D");
    tree->Branch("Sim_zbt",&Sim_zbt,"Sim_zbt/D");
    tree->Branch("xhit",&xhit,"xhit/D");
  	tree->Branch("yhit",&yhit,"yhit/D");
  	tree->Branch("zhit",&zhit,"zhit/D");
//  	tree->Branch("Sim_BeamEnergy",&Sim_BeamEnergy,"Sim_BeamEnergy/D");





    
    
  }


  EventAction::~EventAction()
  {

    if(v13C) delete v13C;
    G4cout<<"delete\n";
    if(v48Ti) delete v48Ti;
    G4cout<<"delete\n";
 


  }

  void
  EventAction::BeginOfEventAction(const G4Event* evt )
  {
    // std::cout<<"begin of event\n";
    using namespace CLHEP;
    if(store)
      {
/*	G4PrimaryParticle* p = evt->GetPrimaryVertex(0)->GetPrimary(1);
	double px=p->GetPx()/MeV;
	double py=p->GetPy()/MeV;
	double pz=p->GetPz()/MeV;
	v48Ti->SetXYZM(px,py,pz,p->GetMass()/MeV);
	Sim_theta48Ti = v48Ti->Theta();
  G4cout<<"  Sim_theta48Ti  " << Sim_theta48Ti*180./double(CLHEP::pi)<< G4endl;
	Sim_phi48Ti = v48Ti->Phi();
	Sim_energy48Ti = v48Ti->E() - v48Ti->M();	
*/
	G4PrimaryParticle* p= evt->GetPrimaryVertex(0)->GetPrimary(0);
	double px=p->GetPx()/MeV;
	double py=p->GetPy()/MeV;
	double pz=p->GetPz()/MeV;

	v13C->SetXYZM(px,py,pz,p->GetMass()/MeV);
	Sim_theta13C = v13C->Theta();
  G4cout<<"  Sim_theta13C  " << Sim_theta13C*180./double(CLHEP::pi) << G4endl;
	Sim_phi13C = v13C->Phi();
	Sim_energy13C = v13C->E() - v13C->M();


 //   ParticleInfo* particleInfo=(ParticleInfo*)p->GetUserInformation();
	
	Sim_xbt = evt->GetPrimaryVertex(0)->GetX0();
	Sim_ybt = evt->GetPrimaryVertex(0)->GetY0();
	Sim_zbt = evt->GetPrimaryVertex(0)->GetZ0();

//	Sim_BeamEnergy = particleInfo->Get_BeamEnergy();
//	G4cout<<"  Sim_BeamEnergy  " << Sim_BeamEnergy << G4endl;
      }
    else
      {
	evt->GetPrimaryVertex(0)->Print();
      }
    fEdep = 0.;
    rmult=0;
  }


  void
  EventAction::EndOfEventAction(const G4Event* evt)
  {

    EventID = evt->GetEventID();


   
    G4HCofThisEvent* HC=evt->GetHCofThisEvent();
    SiHitsCollection * DSRDHC=NULL;

    for (int i=0;i<HC->GetNumberOfCollections();i++)
      {
	G4VHitsCollection* hc=HC->GetHC(i);
//	 G4cout<<" i =  "<<i<<" hc name: "<<hc->GetName()<<G4endl;
	if(hc->GetName()== "/sense/DSRD_log/HC")
	  {
	    // G4cout<<"match "<<"/sense/DSRD_log/HC"<<G4endl;
	    DSRDHC=(SiHitsCollection*) hc;
	  }
	else if(hc->GetName()== "/sense/ND_log/HC")
	  {
	    // G4cout<<"match "<<"/sense/ND_log/HC"<<G4endl;

	  }
	
      }

    //G4VHitsCollection* Rhits = HC->GetHC(0);
    if(DSRDHC)
      {
	for (unsigned int j=0;j<DSRDHC->GetSize();j++)
	  {
	    SiHit* hit= (SiHit*) DSRDHC->GetHit(j);
//	    hit->Print();
	    if(hit->GetEt()>0)
	      {
		using namespace CLHEP;
		Edep[rmult]=hit->GetEt();
		vr->SetXYZ(hit->GetPrePosition().x(),
			   hit->GetPrePosition().y(),
			   hit->GetPrePosition().z());
		rho=hit->GetPrePosition().perp();
		phi = hit->GetPrePosition().phi();
		xhit = rho*cos(phi);
        yhit = rho*sin(phi);
        zhit = -10.;
		rmult++;
	      }
	  }

	//write to array;
	std::fill(Rdeposit,Rdeposit+16,0);

	for (int i=0;i<rmult;i++)
	  {
	    using CLHEP::MeV;
	    Rdeposit[rnum[i]]=CLHEP::RandGauss::shoot(Edep[i]/MeV,0.0212314225);//Edep[i]/MeV;
	  }
      }

    if(!store)
      {
	G4cout<<"End of event\n";
	if(HC)
	  {
	    G4cout<<"number of hit collections: "
		  <<HC->GetNumberOfCollections()<<G4endl;
	    for (int i=0;i<HC->GetNumberOfCollections();i++)
	      {
		G4VHitsCollection* hits = HC->GetHC(i);
		G4cout<<i+1<<". HC: "<<hits->GetName()<<G4endl
		      <<"Number of hits: "<<hits->GetSize()<<G4endl;
		for (unsigned int j=0;j<hits->GetSize();j++)
		  {
		    G4VHit * hit=  hits->GetHit(j);
		    hit->Print();
		  }
	      }
	  }
	else
	  {
	    G4cout<<"There are no HC ! "<<G4endl;
	  }
      }

    if (store)
      {
	tree->Fill();
      }

  }

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
