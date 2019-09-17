// class thate describe hit in Si det.

#ifndef SET10LISiHit_h
#define SET10LISiHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class G4AttDef;
namespace SET10LI
{
  class SiHit : public G4VHit
  {
  private:
    G4String detectorname;
    int copynum;
    G4double Et; //Energy deposit
    G4ThreeVector preposition;
    G4ThreeVector postposition;
  
  public:
    SiHit();
    ~SiHit();
    SiHit(const SiHit &right);
    const SiHit& operator=(const SiHit &right);
    G4int operator==(const SiHit &right) const;
    
    inline void
    *operator new(size_t);
    
    inline void
    operator delete(void *aHit);
    
    // void Draw();
    
    void Print();
    
    inline void SetEt(G4double E){ Et = E; }
    inline G4double GetEt(){ return Et; }

    inline void SetCopyNum(int n){ copynum=n; }
    inline G4double GetCopyNum(){ return copynum; }
    
    inline void SetName(G4String name){ detectorname = name; }
    inline G4String GetName(){ return detectorname; }
    
    inline void
    SetPrePosition(G4ThreeVector r){ preposition = r; }
    inline G4ThreeVector
    GetPrePosition(){ return preposition; }
    
    inline void SetPostPosition(G4ThreeVector r){ postposition = r; }
    inline G4ThreeVector GetPostPosition(){ return postposition; }
    
  void add(const SiHit & right);
    
  };
  
  typedef G4THitsCollection<SiHit> SiHitsCollection;

  extern G4Allocator<SiHit> SiHitAllocator;

  inline void*
  SiHit::operator new(size_t)
  {
    void *aHit;
    aHit = (void *) SiHitAllocator.MallocSingle();
    return aHit;
  }

  inline void
  SiHit::operator delete(void *aHit)
  {
    SiHitAllocator.FreeSingle((SiHit*) aHit);
  }
}
#endif
