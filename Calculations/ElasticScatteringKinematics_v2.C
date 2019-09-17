void ElasticScatteringKinematics_v2()
{
	TCanvas *c1 = new TCanvas("c1","multigraph",200,10,700,500);
   	c1->Divide(2,2);

	Double_t 	m1,m2;
	Int_t		binN = 160;									//m1 - projectile mass, m2 - target mass 
	Double_t 	E1_labIn, E2_labIn;			//LAB system: E1_labIn - initial kinetic energy of m1, E2_labIn - initial kinetic energy of m2
	Double_t 	E1_cmIn, E2_cmIn;			//CM system: E1_cmIn - initial kinetic energy of m1, E2_cmIn - initial kinetic energy of m2

	Double_t E1_labF[binN], E2_labF[binN];			//LAB system: E1_labF - final kinetic energy of m1, E1_labF - final kinetic energy of m2
	Double_t E1_cmF, E2_cmF;				//CM system: E1_cmF - final kinetic energy of m1, E2_cmF - final kinetic energy of m2
	Double_t theta_lab[binN], theta_cm[binN];			//
	Double_t phi_lab[binN], phi_cm[binN];
	Double_t Sm1,Sm2, Rm, Mratio;

/*
	m1 = 13;
	m2 = 48;
	E1_labIn = 13.;
*/

	m1 = 13;
	m2 = 2;
	E1_labIn = 13.;

//	theta_lab = 40.*M_PI/180.;

	
	Double_t 	theta1 = 2.;
	Double_t 	theta2 = 180.;
	Double_t	dtheta = (theta2-theta1)/binN;


	Sm1 = m1/(m1+m2);
	Sm2 = m2/(m1+m2);
	Rm = m1*m1/(m1+m2);
	Mratio = m1/m2;

	E1_cmIn = Sm2*Sm2/(E1_labIn);
	E1_cmF = E1_cmIn;
	E2_cmF = Sm1*Sm2/E1_labIn;


	for (Int_t i = 0; i<binN;i++){
		theta_lab[i] = (dtheta+i*dtheta)*M_PI/180.;
		theta_cm[i] = theta_lab[i] + asin(Mratio*sin(theta_lab[i]));
		phi_lab[i] = (M_PI-theta_cm[i])/2.;
		phi_cm[i] = M_PI-theta_cm[i];

		if (m1<m2){
			E1_labF[i] = Sm1*Sm1*pow(cos(theta_lab[i])+sqrt(1/(Mratio*Mratio)-pow(sin(theta_lab[i]),2)),2);
			}
		else{
			E1_labF[i] = Sm1*Sm1*pow(cos(theta_lab[i])-sqrt(1/(Mratio*Mratio)-pow(sin(theta_lab[i]),2)),2);
			}
		if (phi_lab[i]<M_PI/2.){
			E2_labF[i] = 4*Sm1*Sm2*pow(cos(phi_lab[i]),2);
		}
	//	E2_labF[i] = (1 - E1_labF[i]*m1/E1_labIn)*E1_labIn;

	}




	for (Int_t i=0; i<binN;i++){
		theta_lab[i] = theta_lab[i]*180./M_PI;
		theta_cm[i] = theta_cm[i]*180./M_PI;
		phi_lab[i] = phi_lab[i]*180./M_PI;
		phi_cm[i] = phi_cm[i]*180./M_PI;
		E2_labF[i] = E2_labF[i];
	}

	c1->cd(1);
	TGraph *gr1  = new TGraph(binN,theta_cm, theta_lab);
	gr1->SetTitle("ThetaCM vs ThetaLab;Theta in c.m., degrees; Theta in lab.s., degrees");
   	gr1->SetMarkerStyle(20);
   	gr1->SetMarkerSize(1);
   	gr1->SetMarkerColor(kRed);
   	gr1->SetLineColor(4);
   	gr1->SetLineWidth(3);   	
   	gr1->Draw("AP");
   	TGraph *gr11  = new TGraph(binN,phi_cm, phi_lab);
	gr11->SetTitle("PhiCM vs PhiLab;Phi in c.m., degrees; Phi in lab.s., degrees");
   	gr11->SetMarkerStyle(20);
   	gr11->SetMarkerSize(1);
   	gr11->SetMarkerColor(kBlue);
   	gr11->SetLineColor(4);
   	gr11->SetLineWidth(3);   	
   	gr11->Draw("same");

  
   	c1->cd(2);
/*
   	TGraph *gr2  = new TGraph(binN,theta_cm, E1_labF);
   	gr2->SetTitle("E1Lab vs ThetaCM;Theta in c.m., degrees;E1 in lab.s.,MeV/A");
   	gr2->SetMarkerStyle(20);
   	gr2->SetMarkerSize(1);
   	gr2->SetMarkerColor(kRed);
   	gr2->SetLineColor(4);
   	gr2->SetLineWidth(3);   	
   	gr2->Draw("AP");
*/

   	TGraph *gr22  = new TGraph(binN,phi_cm, E2_labF);
   	gr22->SetTitle("E2Lab vs PhiCM;Phi in c.m., degrees;E2 in lab.s.,MeV/A");
   	gr22->SetMarkerStyle(20);
   	gr22->SetMarkerSize(1);
   	gr22->SetMarkerColor(kBlue);
   	gr22->SetLineColor(4);
   	gr22->SetLineWidth(3);   	
   	gr22->Draw("AP");

   	c1->cd(3);
	TGraph *gr3  = new TGraph(binN,theta_lab, phi_lab);
	gr3->SetTitle("ThetaLab vs PhiLab;Theta in lab.s.,degrees; Phi in lab.s., degrees");
   	gr3->SetMarkerStyle(20);
   	gr3->SetMarkerSize(1);
   	gr3->SetMarkerColor(kRed);
   	gr3->SetLineColor(4);
   	gr3->SetLineWidth(3);   	
   	gr3->Draw("AP");

   	c1->cd(4);
	TGraph *gr4  = new TGraph(binN,theta_lab,E1_labF);
	gr4->SetTitle("E1Lab vs ThetaLab;theta in lab.s., degrees;E1 in lab.s.,MeV/A");
   	gr4->SetMarkerStyle(20);
   	gr4->SetMarkerSize(1);
   	gr4->SetMarkerColor(kRed);
   	gr4->SetLineColor(4);
   	gr4->SetLineWidth(3);   	
   	gr4->Draw("AP");



}