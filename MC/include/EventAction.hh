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
// $Id: B1EventAction.hh 75216 2013-10-29 16:08:11Z gcosmo $
//
/// \file B1EventAction.hh
/// \brief Definition of the B1EventAction class

#ifndef SET10LIEventAction_h
#define SET10LIEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "ParticleInfo.hh"


/// Event action class
///
namespace SET10LI
{
  class EventAction : public G4UserEventAction
  {
  public:
    EventAction();
    EventAction(TTree* T);
    virtual ~EventAction();
    
    virtual void
    BeginOfEventAction(const G4Event* event);

    virtual void
    EndOfEventAction(const G4Event* event);
    
    inline void
    AddEdep(G4double edep) { fEdep += edep; }
    
  private:
    G4double  fEdep;
    bool store;
    TTree* tree;

    //vertex
    TLorentzVector * v13C;
    TLorentzVector * v48Ti;
    TVector3 *vr;
    
    
   
    // digitizing
    double rho;
    double phi;
    int rmult;
    int snum[16];
    int rnum[16];
    double Edep[16];
    double Rdeposit[16];
    double Sim_theta13C;
    double Sim_phi13C;
    double Sim_energy13C;
    double Sim_theta48Ti;
    double Sim_phi48Ti;
    double Sim_energy48Ti;
    int    EventID;
    double Sim_xbt;
    double Sim_ybt;
    double Sim_zbt;
    double xhit;
    double yhit;
    double zhit;
//    double Sim_BeamEnergy;

  };
}


#endif

