
#ifndef SET10LIDetectorConstruction_h
#define SET10LIDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4Material.hh"
class G4VPhysicalVolume;
class G4LogicalVolume;

namespace SET10LI
{
  class DetectorConstruction : public G4VUserDetectorConstruction
  {
  public:
    DetectorConstruction();
    virtual ~DetectorConstruction();
    
    virtual G4VPhysicalVolume*
    Construct();
    
  protected:
    void
    creatematerials();

    G4LogicalVolume* create_exp_hall(double x, double y, double z);
    G4LogicalVolume* create_Chamber_WindowIn(G4String name, double thickness, double radius);
    G4LogicalVolume* create_Chamber_WindowOut(G4String name, double thickness, double radius);
    
//    G4LogicalVolume* create_target(G4Material * mat, G4String name, double thickness, double radiusT, double radiusCh);
    G4LogicalVolume* create_DSRD(G4String name, double thickness);
    
    G4Material * Vacuum;
//    G4Material * target_mat;
    G4Material * Si;
    G4Material * Ti;
    G4Material * Fe;
  };
}

#endif

