#include "SiSD.hh"
#include "G4Step.hh"
#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4ios.hh"
#include "Randomize.hh"
#include "G4SDManager.hh"
namespace SET10LI
{
  SiSD::SiSD(G4String name)
    :G4VSensitiveDetector(name),
     HitsCollection(NULL)
  {
    G4String HCname=name;
    
    collectionName.insert(HCname+="/HC");
  }
  
  SiSD::~SiSD()
  {
    
  }
  
  void SiSD::Initialize(G4HCofThisEvent* HCE)
  {
     int hcID = -1;
    
    HitsCollection =
      new SiHitsCollection(SensitiveDetectorName,
			   collectionName[0]);
    
//     hcID= G4SDManager::GetSDMpointer()->
//      GetCollectionID(collectionName[0]);
//      G4cout << "______SiSD hcID 1 ______________     " << hcID << G4endl;
    if(hcID<0)
      { hcID = GetCollectionID(0); }
    HCE->AddHitsCollection(hcID,HitsCollection);
//      G4cout << "______SiSD hcID 2 ______________     " << hcID << G4endl;
    
    
  }
  
  G4bool
  SiSD::ProcessHits(G4Step* aStep, G4TouchableHistory*ROhist)
  {
    
    SiHit * hit = new  SiHit();
    G4int copynum = aStep->GetPreStepPoint()->
      GetTouchable()->GetCopyNumber(1);
    G4AffineTransform global_trans=
      aStep->GetPostStepPoint()->GetTouchable()->
      GetHistory()->GetTopTransform();
    
    G4String name= aStep->GetPreStepPoint()->
      GetTouchable()->GetVolume()->GetName();
    hit->SetName( name);
    G4ThreeVector prepos= global_trans.TransformPoint(aStep->
     						      GetPreStepPoint()->
     						      GetPosition());
    
    G4ThreeVector postpos=global_trans.TransformPoint(aStep->
     						      GetPostStepPoint()->
     						      GetPosition());
    //   G4ThreeVector prepos= aStep-> GetPreStepPoint()->GetPosition();
    
    //  G4ThreeVector postpos=aStep-> GetPostStepPoint()-> GetPosition();
    
    hit->SetCopyNum(copynum);
    hit->SetPrePosition(prepos);
    hit->SetPostPosition(postpos);
    hit->SetEt(aStep->GetTotalEnergyDeposit());
    int n_e = HitsCollection->entries();
/*
    G4cout<<"  n_e   :" << "   " << n_e << G4endl;
    G4cout<<"  deposit   :" << "   " << aStep->GetTotalEnergyDeposit() << G4endl;
    G4cout<<"  name   :" << "   " << name << G4endl;
    G4cout<<"  pre pos   :" << "   " << prepos << G4endl;
    G4cout<<"  post pos   :" << "   " << postpos << G4endl;
    G4cout<<"  particle name   :" << "   " << aStep->GetTrack()->GetParticleDefinition()->GetParticleName() << G4endl;
*/

    if(n_e>0)
      {
	bool newhit =true;
	for(G4int i = 0;i<n_e;i++){
	  SiHit* phit= ( SiHit*)HitsCollection->GetHit(i);
	  G4ThreeVector post= phit->GetPostPosition();
	  if(post==hit->GetPrePosition()){
	    phit->add(*hit);
	    newhit=false;
	    break;
	  }
	}
	if(newhit)
	  {
	    HitsCollection->insert(hit);
	  }
      }
    else
 
      {
	HitsCollection->insert(hit);
      }
    return true;
  }
  
  void SiSD::EndOfEvent(G4HCofThisEvent*)
  {
    
  }
  
  void SiSD::clear()
  {
  } 
  
  //void Ne17setSiSD::DrawAll()
  //{
  //} 
  
  void SiSD::PrintAll()
  {
  } 
}
