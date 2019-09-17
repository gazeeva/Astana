#include "NDSD.hh"
#include "G4Step.hh"
#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4ios.hh"
#include "Randomize.hh"
#include "G4SDManager.hh"
#include "G4VProcess.hh"
namespace SET10LI
{
  NDSD::NDSD(G4String name)
    :G4VSensitiveDetector(name)
  {
    G4String HCname=name;
    
    collectionName.insert(HCname+="/HC");
 }
  
  NDSD::~NDSD()
  {
    
  }
  
  void NDSD::Initialize(G4HCofThisEvent* HCE)
  {
//    int hcID = -1;

//    G4cout << "__SensitiveDetectorName ______________     " << SensitiveDetectorName << G4endl;
//    G4cout << "__collectionName ______________     " << collectionName[0] << G4endl;
   
    HitsCollection =
      new NDHitsCollection(SensitiveDetectorName,
			    collectionName[0]);
//      G4cout << "  new event     " << G4endl;

    
//    G4int hcID= G4SDManager::GetSDMpointer()->
//      GetCollectionID(collectionName[0]);

//      G4cout << "______ND hcID 1 ______________     " << hcID << G4endl;


//      if(hcID<0)
      G4int hcID = GetCollectionID(0); 
//      G4cout << "______ND hcID 2 ______________     " << hcID << G4endl;
    HCE->AddHitsCollection(hcID,HitsCollection);
    //      G4cout << "_____________________test__________________" << G4endl;
   
    
  }

  G4bool
  NDSD::ProcessHits(G4Step* aStep, G4TouchableHistory*ROhist)
  {
    
    NDHit * hit = new  NDHit();
    G4int copynum = aStep->GetPreStepPoint()->GetTouchable()->GetCopyNumber();
    G4AffineTransform global_trans=aStep->GetPostStepPoint()->GetTouchable()->
            GetHistory()->GetTopTransform();
    G4AffineTransform global_trans_pre=aStep->GetPreStepPoint()->GetTouchable()->
            GetHistory()->GetTopTransform();

     G4String name= aStep->GetPreStepPoint()->
            GetTouchable()->GetVolume()->GetName();
     G4String particlename= aStep->GetTrack()->GetParticleDefinition()->GetParticleName();
     G4int trackID = aStep->GetTrack()->GetTrackID();  
     G4int parentID = aStep->GetTrack()->GetParentID(); 
     
     G4ThreeVector postpos=global_trans.TransformPoint(aStep->
		GetPostStepPoint()->GetPosition());
     G4ThreeVector prepos=global_trans_pre.TransformPoint(aStep->
		GetPreStepPoint()->GetPosition());

/*     
     if(trackID!=aStep->GetTrack()->GetTrackID() || aStep->GetTrack()->GetTrackID() == 2)
     {

	G4cout<<"  track ID   :" << "   " << aStep->GetTrack()->GetTrackID();
	G4cout<<"  particle name :" << "   " << aStep->GetTrack()->GetParticleDefinition()->GetParticleName();
	G4cout<<" Kin Energy pre:  " << "   " << aStep->GetPreStepPoint()->GetKineticEnergy()  << G4endl;
	trackID = aStep->GetTrack()->GetTrackID();       
    }
*/

//    G4cout<<" proc name pre   :" << "   " << aStep->GetPreStepPoint()->GetProcessDefinedStep()->GetProcessName()  << G4endl;
//    G4cout<<" proc name post  :" << "   " << aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()  << G4endl;

/*
     if(HitsCollection->entries()>-1&&aStep->GetPreStepPoint()->GetTouchable()->GetCopyNumber()==11)
     {    
    G4cout<<" Copy number                            :" << aStep->GetPreStepPoint()->GetTouchable()->GetCopyNumber() << G4endl;    
    G4cout<<"  neutron entries   :" << "   " << HitsCollection->entries() << G4endl;
//    G4cout<<"  mass   :" << "   " << aStep->GetPreStepPoint()->GetMass() << G4endl;
//    G4cout<<"  charge Pre  :" << "   " << aStep->GetPreStepPoint()->GetCharge() << G4endl;
//    G4cout<<"  charge Post  :" << "   " << aStep->GetPostStepPoint()->GetCharge() << G4endl;
    G4cout<<"  Total Energy Deposit   :" << "   " << aStep->GetTotalEnergyDeposit() << G4endl;
//    G4cout<<" Kin Energy post  :" << "   " << aStep->GetPostStepPoint()->GetKineticEnergy()  << G4endl;
//     if(aStep->GetNonIonizingEnergyDeposit()>0)
//     {
    G4cout<<"  Total non ion                                                 :" << "   " << aStep->GetNonIonizingEnergyDeposit() << G4endl;
//     }
    G4cout<<"  Pre Position   :" << "   " << prepos << G4endl;
    G4cout<<"  Post Position   :" << "   " << postpos << G4endl;
    G4cout<<"  particle name   :" << "   " << aStep->GetTrack()->GetParticleDefinition()->GetParticleName() << G4endl;
//    G4cout<<" proc name pre   :" << "   " << aStep->GetPreStepPoint()->GetProcessDefinedStep()->GetProcessName()  << G4endl;
    G4cout<<" proc name post  :" << "   " << aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()  << G4endl;

     }
*/
    hit->SetName( name);
    hit->SetParticleName( particlename);
    hit->SetCopyNum(copynum);
    hit->SetTrackID(trackID);
    hit->SetParentID(parentID);
    
    hit->SetPostPosition(postpos);
    hit->SetEt(aStep->GetTotalEnergyDeposit());
    hit->SetTime(aStep->GetPostStepPoint()->GetGlobalTime());
    HitsCollection->insert(hit);
    
    return true;
  }
  
void NDSD::EndOfEvent(G4HCofThisEvent*)
{
 
}

void NDSD::clear()
{
} 

//void Ne17setNDSD::DrawAll()
//{
//} 

void NDSD::PrintAll()
{
} 
}
