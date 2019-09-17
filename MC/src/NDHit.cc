#include "NDHit.hh"

namespace SET10LI
{
  G4Allocator<NDHit> NDHitAllocator;
  
  NDHit::NDHit()
  {;}
  
  NDHit::~NDHit()
  {;}

  NDHit::NDHit(const NDHit &right): G4VHit()
  {
//    detectorname =right.detectorname;
    // copynum = right.copynum;
    Et = right.Et;
    time=right.time;
    postposition = right.postposition;
  }
  
  const NDHit&
  NDHit::operator=(const NDHit &right)
  {
//    detectorname =right.detectorname;
    // copynum = right.copynum;
    Et = right.Et;
    time=right.time;
    postposition = right.postposition;
    return *this;
  }
  void
  NDHit::add(const NDHit &right)
  {
//    detectorname =right.detectorname;
    Et+= right.Et;
    postposition = right.postposition; 
  }
  

  int
  NDHit::operator==(const NDHit &right) const
  {
    return (this==&right) ? 1 : 0;
  }
 
  void
  NDHit::Print()
  {
    G4cout<<"Detector name: "<<detectorname<<G4endl
	  <<"Particle name: "<<particlename<<G4endl
	  <<"copynum: "<<copynum<<G4endl
	  <<"Energy deposit: "<<Et<<G4endl
	  <<"time: "<<time<<G4endl
	  <<"Post position: ("<<postposition(0)<<','<<postposition(1)
	  <<','<<postposition(2)<<")"<<G4endl;
    
  }
}
