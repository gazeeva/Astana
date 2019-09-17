// class thate describe hit in Si det.

#ifndef SET10LINDHit_h
#define SET10LINDHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class G4AttDef;
namespace SET10LI
{
  class NDHit : public G4VHit
  {
  private:
    G4String detectorname;
    G4String particlename;
    G4double Et; //Energy deposit
    double time;
    int copynum;
    int trackID;
    int parentID;
    G4ThreeVector postposition;
  
  public:
    NDHit();
    ~NDHit();

    NDHit(const NDHit &right);
    const NDHit& operator=(const NDHit &right);
    G4int operator==(const NDHit &right) const;
    
    inline void
    *operator new(size_t);
    
    inline void
    operator delete(void *aHit);
  
    // void Draw();
    
    void Print();

    inline void
    SetCopyNum(int n){ copynum = n; }
    inline int
    GetCopyNum(){ return copynum; }

    inline void
    SetTrackID(int track){ trackID = track; }
    inline int
    GetTrackID(){ return trackID; }

    inline void
    SetParentID(int parent){ parentID = parent; }
    inline int
    GetParentID(){ return parentID; }
    
    inline void
    SetEt(G4double E){ Et = E; }
    inline G4double
    GetEt(){ return Et; }

    inline void
    SetTime(double T){ time = T; }
    inline double
    GetTime(){ return time; }
    
    inline void SetName(G4String name){ detectorname = name; }
    inline G4String GetName(){ return detectorname; }
      
    inline void SetParticleName(G4String name){ particlename = name; }
    inline G4String GetParticleName(){ return particlename; }

      
    inline void SetPostPosition(G4ThreeVector r){ postposition = r; }
    inline G4ThreeVector GetPostPosition(){ return postposition; }
    
  void add(const NDHit & right);
  
  };
  
  typedef G4THitsCollection<NDHit> NDHitsCollection;

  extern G4Allocator<NDHit> NDHitAllocator;

  inline void*
  NDHit::operator new(size_t)
  {
    void *aHit;
    aHit = (void *) NDHitAllocator.MallocSingle();
    return aHit;
  }

  inline void
  NDHit::operator delete(void *aHit)
  {
    NDHitAllocator.FreeSingle((NDHit*) aHit);
  }
}
#endif
