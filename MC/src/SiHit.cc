#include "SiHit.hh"

namespace SET10LI
{
  G4Allocator<SiHit> SiHitAllocator;
  
  SiHit::SiHit()
  {;}
  
  SiHit::~SiHit()
  {;}

  SiHit::SiHit(const SiHit & right): G4VHit()
  {
    detectorname =right.detectorname;
    copynum = right.copynum;
    Et = right.Et;
    preposition = right.preposition;
    postposition = right.postposition;
  }
  
  const SiHit&
  SiHit::operator=(const SiHit &right)
  {
    detectorname =right.detectorname;
    Et = right.Et;
    copynum = right.copynum;
    preposition = right.preposition;
    postposition = right.postposition;
    return *this;
  }
  void
  SiHit::add(const SiHit &right)
  {
    detectorname =right.detectorname;
    
    Et+= right.Et;
    postposition = right.postposition;
    
  }
  

  int
  SiHit::operator==(const SiHit &right) const
  {
    return (this==&right) ? 1 : 0;
  }
  
  void
  SiHit::Print()
  {
    G4cout<<"Detector name: "<<detectorname<<G4endl
	  <<"copynum      : "<<copynum<<G4endl
	  <<"Energy deposit: "<<Et<<G4endl
	  <<"Pre position: ("<<preposition(0)<<','<<preposition(1)
	  <<','<<preposition(2)<<")"<<G4endl
	  <<"Post position: ("<<postposition(0)<<','<<postposition(1)
	  <<','<<postposition(2)<<")"<<G4endl;
    
  }
}
