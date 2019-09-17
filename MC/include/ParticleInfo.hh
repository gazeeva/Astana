
#ifndef ParticleInfo_h
#define ParticleInfo_h 1

#include "G4VUserPrimaryParticleInformation.hh"
#include "globals.hh"
#include "G4LorentzVector.hh"
class ParticleInfo : public G4VUserPrimaryParticleInformation {

public:
ParticleInfo();
virtual ~ParticleInfo();
virtual void Print() const;
//Set methods	

void Set_LV_Beam(G4LorentzVector lv_Beam);
void Set_LV_2H_CM(G4LorentzVector lv2H_CM);
void Set_LV_6He_CM(G4LorentzVector lv_6He_CM);
void Set_LV_n_CM(G4LorentzVector lv_n_CM);
void Set_E7He(double E7He);
void Set_BeamEnergy(double BeamEnergy);


G4LorentzVector Get_LV_Beam();
G4LorentzVector Get_LV_2H_CM();
G4LorentzVector Get_LV_6He_CM();
G4LorentzVector Get_LV_n_CM();
double Get_E7He();
double Get_BeamEnergy();
	
private:
G4LorentzVector ParticleInfo_LV_Beam;
G4LorentzVector ParticleInfo_LV_2H_CM;
G4LorentzVector ParticleInfo_LV_6He_CM;
G4LorentzVector ParticleInfo_LV_n_CM;
double ParticleInfo_E7He;
double ParticleInfo_BeamEnergy;
};

#endif
