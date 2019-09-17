#ifndef SRC10LINDSD_h
#define SRC10LINDSD_h 1

#include "G4VSensitiveDetector.hh"
#include "NDHit.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

namespace SET10LI
{
  class NDSD : public G4VSensitiveDetector
  {
    
  private:
    NDHitsCollection *HitsCollection;
    int trackID;
    
    
  public:
    NDSD(G4String name);
    ~NDSD();
    
    virtual void
    Initialize(G4HCofThisEvent*HCE);
    
    virtual bool
    ProcessHits(G4Step*aStep,G4TouchableHistory*ROhist);
    
    virtual void
    EndOfEvent(G4HCofThisEvent*HCE);
    
    void
    clear();
    
    NDHitsCollection *
    GetHC(){return HitsCollection;}
    
    void PrintAll();
  };
}
#endif
