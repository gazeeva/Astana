//#include "/home/golovkov/10Li_analysis/include/analysis.h"

{
  
  TFile * ifile = new TFile("out/simevents.root");
  TTree * itree= (TTree*) ifile->Get("simevents");
  TFile * ofile = new TFile("out/analysed-events.root","recreate");
  TTree * otree = new TTree("otree","analysed-events.root");
 
  analysis b(itree,otree);
  cout<<"Loop!\n";
  b.loop();
  ofile->cd();
  otree->Write();
  ofile->Close();

}
