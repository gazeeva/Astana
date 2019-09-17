
#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"
#include "G4PrimaryVertex.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "TF1.h"
#include "TRandom.h"
//#include "ParticleInfo.hh"

#include "G4EmCalculator.hh"
 



class G4ParticleGun;
class G4Event;
class G4Box;

/// The primary generator action class with particle gun.
///
/// The default kinematic is a 6 MeV gamma, randomly distribued 
/// in front of the phantom across 80% of the (X,Y) phantom size.
namespace SET10LI
{

  class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
  {
  public:
    PrimaryGeneratorAction();    
    virtual ~PrimaryGeneratorAction();
    
    // method from the base class
    virtual void GeneratePrimaries(G4Event*);         
    
    // method to access particle gun
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }


    
  private:
    G4ParticleGun*  fParticleGun; // pointer a to G4 gun class
    G4Box* fEnvelopeBox;
    double beam_mean_T;
    G4ParticleTable* particletable;
    G4IonTable* iontable;
    G4ParticleDefinition * pd13C;
    G4ParticleDefinition * pd48Ti;
    G4VUserPrimaryParticleInformation* partINFO;
    G4PrimaryVertex * generator1();
    G4EmCalculator * ELC;


    

  };
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


