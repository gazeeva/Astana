#ifndef SRC10LISiSD_h
#define SRC10LISiSD_h 1

#include "G4VSensitiveDetector.hh"
#include "SiHit.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

namespace SET10LI
{
  class SiSD : public G4VSensitiveDetector
  {
    
  private:
    SiHitsCollection *HitsCollection;
    G4int mult;
    //  int copynum[20];
    G4double post_x[20],post_y[20],pre_x[20],pre_y[20];
    G4double Edep[20];
    
    
  public:
    SiSD(G4String name);
    ~SiSD();
    
    virtual void
    Initialize(G4HCofThisEvent*HCE);
    
    virtual bool
    ProcessHits(G4Step*aStep,G4TouchableHistory*ROhist);
    
    virtual void
    EndOfEvent(G4HCofThisEvent*HCE);
    
    void
    clear();
    
    SiHitsCollection *
    GetHC(){return HitsCollection;}
    
    void PrintAll();
  };
}
#endif
