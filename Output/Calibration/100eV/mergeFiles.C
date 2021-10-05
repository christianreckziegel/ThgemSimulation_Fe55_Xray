/*Esta macro junta os results_i.root em um resultFinal.root só,
lê o resultFinal.root selecionando as entries que pertencem ao mesmo evento,
realiza o ajuste de curva obtendo o raio da circunferência para cada caso,
e preenche um histograma com o raio para cada evento.*/

#include <iostream>
#include <fstream>
#include <sstream> 
#include <vector> 

#include <TApplication.h>
#include <TTree.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TH1D.h>
#include <TF1.h>
#include "TGraph.h"
#include <TGraphErrors.h>
#include <TString.h>
#include "Fit/Fitter.h"
#include "TMath.h"

using namespace std;

//cria struct de nome PARTICLE para conter os dados do elétron inicial da ionização
typedef struct {
    Double_t energy;
    Float_t x, y, z;
    Float_t dx, dy, dz;
    Int_t eventNumber;
} PARTICLE;

void mergeFiles(){
	/* 1 - merging ROOT files*/
	//https://root-forum.cern.ch/t/how-to-use-tchain-to-combine-many-root-files/25164
	TChain* chain = new TChain ("Results"); //"Results" is one of the trees inside the file
	TString strEnergy = "100eV"; // specify unit
	TString strBase = "CalibResult"+strEnergy+"_";
	for(int i = 0; i <= 29; i++){
		TString resultPart = strBase + i +".root";
		chain->Add(resultPart);
		
	}
	chain->Merge(strBase + "final.root");
	
	/* 2 - select same event, fit curve, fill histograms*/
	TFile *inputFile = TFile::Open(strBase + "final.root");
	TTree* theTree = (TTree*) inputFile->Get("Results");
	Double_t xi, yi, xf, yf, incxf, incyf, eEnerg;
	Int_t gain, eventN;
	theTree->SetBranchAddress("Avalanche_xi",&xi);
	theTree->SetBranchAddress("Avalanche_yi",&yi);
	theTree->SetBranchAddress("Avalanche_x",&xf);
	theTree->SetBranchAddress("Avalanche_y",&yf);
	theTree->SetBranchAddress("Gain",&gain);
	theTree->SetBranchAddress("Primary_eletron_initial_energy",&eEnerg);
	
	int n_entries = theTree->GetEntries();
	int status, np, nEnd;
	cout << "There are " << n_entries << " entries.\n";
	
	
	inputFile->Close();
	
	
	
	
	
}

int main(){
	mergeFiles();
	return 0;
	
}
