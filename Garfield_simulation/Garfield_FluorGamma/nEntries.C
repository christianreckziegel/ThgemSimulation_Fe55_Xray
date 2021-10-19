#include <iostream>
#include <fstream>

#include <TApplication.h>
#include <TTree.h>
#include <TFile.h>

//cria struct de nome PARTICLE para conter os dados do elétron inicial da ionização
typedef struct {
    Double_t energy;
    Float_t x, y, z;
    Float_t dx, dy, dz;
    Int_t eventNumber;
} PARTICLE;

using namespace std;

TString strGas = "FullSet";

int nEntries(){ //"/home/christian/Documents/Simulação/Geant4Parte2/Teste-build/particles.root"
	TFile *inputFile = TFile::Open("particlesFullSet.root");
	TTree* theTree = (TTree*) inputFile->Get("Fluorescence_electrons");
	TBranch* electron_branch = theTree->GetBranch("electron_branch");
	PARTICLE electron;
	electron_branch->SetAddress(&electron);

	int entries = theTree->GetEntries();
	double x0, y0, z0, xi, yi, zi, xa, ya, ea, x1, y1, z1, ti, t1, ei, e1;
	int status, np, eventN;
	return entries;
}


# ifndef __CINT__
int main(){
	int entries = nEntries();
	int nJobs = entries/10;
	int resto = entries%10;
	int ultimoJob = nJobs;
	if(resto == 0){
		ultimoJob = nJobs - 1;
	}
	cout << entries << "\t" << ultimoJob << "\t" << resto << endl;
	return 0;
}
# endif
