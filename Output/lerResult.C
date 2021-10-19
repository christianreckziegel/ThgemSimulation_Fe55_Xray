/*Esta macro lê dados do arquivo result.root proveniente 
da simulação no Garfield++. 
Imprime as posições e respectivos erros, ganho e nº do 
evento para cada entrada do arquivo particles.root simulada.*/

#include <iostream>
#include <fstream>

#include <TApplication.h>
#include <TTree.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TF1.h>
#include <TGraphErrors.h>


using namespace std;

void lerResult(){
	TFile *inputFile = TFile::Open("ArCO2_70-30_Result_2.0GeV_0.5T_30cm_final.root");
	TTree* theTree = (TTree*) inputFile->Get("Results");
	Double_t xi, yi, xf, yf, incxf, incyf;
	Int_t nEndPoint, eventN;
	theTree->SetBranchAddress("Avalanche_xi",&xi);
	theTree->SetBranchAddress("Avalanche_yi",&yi);
	theTree->SetBranchAddress("Avalanche_x",&xf);
	theTree->SetBranchAddress("Avalanche_y",&yf);
	theTree->SetBranchAddress("Avalanche_incx",&incxf);
	theTree->SetBranchAddress("Avalanche_incy",&incyf);
	theTree->SetBranchAddress("Number_of_Electrons_endpoint",&nEndPoint);
	theTree->SetBranchAddress("Event_number_in_Geant4",&eventN);
	
	int n_events = theTree->GetEntries();
	int status, np, nEnd;
	cout << "There are " << n_events << " entries(s).\n";
	double maior = 0.;
	
	//creating arrays for the plot
	double x[n_events];
	double y[n_events];
	double ex[n_events];
	double ey[n_events];
	
	for (int i = 0; i < n_events; i++) {
		theTree->GetEntry(i);
		
		cout << "Avalanche número " << i << endl;
		cout << "Posição inicial: ";
		cout << "(" << xi << "," << yi << ")cm\n";
		cout << "Média da posição final: ";
		cout << "(" << xf << "+-" << incxf << "," << yf << "+-" << incyf << ")cm\n";
		cout << "Ganho/Número de elétrons finais: " << nEndPoint << "\n";
		cout << "Evento número: " << eventN << "\n";
		cout << endl;
		if(maior < yi){ maior = yi; }
		
		// filling arrays
		x[i] = xf;
		y[i] = yf;
		ex[i] = incxf;
		ey[i] = incyf;
		
	}
	cout << endl << "maior = " << maior << endl;
	
}



int main(){
	lerResult();
	return 0;
}
