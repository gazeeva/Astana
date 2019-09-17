#include <math.h>
{
	double m1,m2;
										//m1 - projectile mass, m2 - target mass 
	double E1_labIn, E2_labIn;			//LAB system: E1_labIn - initial kinetic energy of m1, E2_labIn - initial kinetic energy of m2
	double E1_cmIn, E2_cmIn;			//CM system: E1_cmIn - initial kinetic energy of m1, E2_cmIn - initial kinetic energy of m2

	double E1_labF, E2_labF;			//LAB system: E1_labF - final kinetic energy of m1, E1_labF - final kinetic energy of m2
	double E1_cmF, E2_cmF;				//CM system: E1_cmF - final kinetic energy of m1, E2_cmF - final kinetic energy of m2
	double theta_lab, theta_cm;			//
	double phi_lab, phi_cm;
	double theta_lab_max;

	double Sm1,Sm2, Rm, Mratio;
/*
	m1 = 13;
	m2 = 48;
	E1_labIn = 13.;
	theta_lab = 40.*M_PI/180.;
*/

	m1 = 13;
	m2 = 2;
	E1_labIn = 13.;
	theta_lab = 40.*M_PI/180.;

	Sm1 = m1/(m1+m2);
	Sm2 = m2/(m1+m2);
	Rm = m1*m1/(m1+m2);
	Mratio = m1/m2;

	E1_cmIn = Sm2*Sm2/(E1_labIn);

	E1_cmF = E1_cmIn;
	E2_cmF = Sm1*Sm2/E1_labIn;
	if (m1<m2){
		E1_labF = Sm1*Sm1*pow(cos(theta_lab)+sqrt(1/(Mratio*Mratio)-pow(sin(theta_lab),2)),2);
	}
	else{
		E1_labF = Sm1*Sm1*pow(cos(theta_lab)-sqrt(1/(Mratio*Mratio)-pow(sin(theta_lab),2)),2);
	}
	theta_lab_max = asin(Mratio);
	E2_labF = (1 - E1_labF*m1/E1_labIn)*E1_labIn;
	theta_cm = theta_lab + asin(Mratio*sin(theta_lab));
	phi_lab = (M_PI-theta_cm)/2.;
	phi_cm = M_PI-theta_cm;

	cout << "m1\t=\t" << m1 <<endl;
	cout << "m2\t=\t" << m2 <<endl;
	cout << "E1_labIn\t=\t" << E1_labIn <<endl;
	cout << "theta_lab\t=\t" << theta_lab*180./M_PI <<endl;
	cout << "E1_cmF\t=\t" << E1_cmF <<endl;
	cout << "E2_cmF\t=\t" << E2_cmF <<endl;
	cout << "E1_labF\t=\t" << E1_labF <<"MeV/A"<<endl;
	cout << "E2_labF\t=\t" << E2_labF/m2 <<"MeV/A"<<endl;
	cout << "theta_cm\t=\t" << theta_cm*180./M_PI <<endl;
	cout << "phi_cm\t=\t" << phi_cm*180./M_PI <<endl;
	cout << "phi_lab\t=\t" << phi_lab*180./M_PI <<endl;
	cout << "theta_lab_max\t=\t" << theta_lab_max*180./M_PI <<endl;


/*
	double theta_lab1 = 41.0884*M_PI/180.;
    double theta_lab2 = 41.54*M_PI/180.;
    double ratio = 13./48;
    double theta_cm1 = theta_lab1 + asin(ratio-sin(theta_lab1));
    double theta_cm2 = theta_lab2 + asin(ratio-sin(theta_lab2));
    

    cout << "theta_lab1\t=\t" << theta_lab1*180./M_PI<<endl;
    cout << "theta_lab2\t=\t" << theta_lab2*180./M_PI<<endl;
    cout << "theta_cm1\t=\t" << theta_cm1*180./M_PI<<endl;
    cout << "theta_cm1\t=\t" << theta_cm1*180./M_PI<<endl;
    */
}