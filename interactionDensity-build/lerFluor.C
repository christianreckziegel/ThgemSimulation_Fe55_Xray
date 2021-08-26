#include <iostream>
#include <fstream>

#include <TApplication.h>
#include <TTree.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TH1F.h>

using namespace std;

void lerFluor(){ //"/home/christian/Documents/Simulação/Geant4Parte2/Teste-build/particles.root"
	TFile *inputFile = TFile::Open("particles.root");
	TTree* theTree = (TTree*) inputFile->Get("Fluorescence");
	TBranch* fluor_branch = theTree->GetBranch("fluor_branch");
	double fluorEnergy;
	fluor_branch->SetAddress(&fluorEnergy);

	int n_events = theTree->GetEntries();
	double gammaEnergy;
	int status, np;
	cout << "There are " << n_events << " events.\n";
	
	// Energy canvas
	TCanvas *cEnergy = new TCanvas("cE","Canvas Energy");
	// Energy histogram
	int nBins = 10000;
	double xMin = 0.;
	double xMax = 10000.;
	TH1D* hEnergy = new TH1D("hEnergy","Gamma fluorescence spectrum", nBins, xMin, xMax);
	hEnergy->GetXaxis()->SetTitle("E(eV)");
	hEnergy->GetYaxis()->SetTitle("Entries");
	
	// Looping through root file
	for (int i = 0; i < n_events; i++) {
		theTree->GetEntry(i);
		gammaEnergy = fluorEnergy;
		hEnergy->Fill(fluorEnergy);
		
	}
	/*double meanVal = hEnergy->GetMean();
	double mpvBin = hEnergy->GetMaximumBin();
	cout << "Mean value = " << meanVal << " keV\n";
	cout << "Most probable value = " << hEnergy->GetXaxis()->GetBinCenter(mpvBin) << " keV\n";*/
	cEnergy->cd();
	hEnergy->Draw();
	cEnergy->SaveAs("fluorSpectrum.png","png");
	
}



int main(){
	lerFluor();
	return 0;
}
