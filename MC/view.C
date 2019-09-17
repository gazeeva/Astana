{
  TFile * f1 = new TFile("out/simevents.root");
  TTree* simtree = (TTree*) f1->Get("simevents");
  
  TFile * f2 = new TFile("out/analysed-events.root");
  TTree* otree = (TTree*) f2->Get("otree");
  otree->AddFriend(simtree);

  otree->SetLineColor(1);
  otree->Draw("combine_mass>>h1(200,-5,5)","missing_mass_trigger&&neutron_trigger","");
  otree->SetLineColor(4);
  otree->Draw("missing_mass","missing_mass_trigger&&neutron_trigger","same"); 
}
