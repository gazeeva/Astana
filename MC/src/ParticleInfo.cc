#include "ParticleInfo.hh"

ParticleInfo::ParticleInfo()
{}

ParticleInfo::~ParticleInfo()
{}

void ParticleInfo::Set_LV_Beam(G4LorentzVector lv_Beam)
{
	ParticleInfo_LV_Beam = lv_Beam;
}

void ParticleInfo::Set_LV_2H_CM(G4LorentzVector lv2H_CM)
{
	ParticleInfo_LV_2H_CM = lv2H_CM;
}
void ParticleInfo::Set_LV_6He_CM(G4LorentzVector lv_6He_CM)
{
	ParticleInfo_LV_6He_CM = lv_6He_CM;
}
void ParticleInfo::Set_LV_n_CM(G4LorentzVector lv_n_CM)
{
	ParticleInfo_LV_n_CM = lv_n_CM;
}

void ParticleInfo::Set_E7He(double E7He)
{
	ParticleInfo_E7He = E7He;
}

void ParticleInfo::Set_BeamEnergy(double BeamEnergy)
{
	ParticleInfo_BeamEnergy = BeamEnergy;
}

G4LorentzVector ParticleInfo::Get_LV_Beam()
{
	return ParticleInfo_LV_Beam;
}

G4LorentzVector ParticleInfo::Get_LV_2H_CM()
{
	return ParticleInfo_LV_2H_CM;
}

G4LorentzVector ParticleInfo::Get_LV_6He_CM()
{
	return ParticleInfo_LV_6He_CM;
}
G4LorentzVector ParticleInfo::Get_LV_n_CM()
{
	return ParticleInfo_LV_n_CM;
}

double ParticleInfo::Get_E7He()
{
	return ParticleInfo_E7He;
}

double ParticleInfo::Get_BeamEnergy()
{
	return ParticleInfo_BeamEnergy;
}

void ParticleInfo::Print() const 
{}

