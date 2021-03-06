#include <iostream>
#include <fstream>

#include <TApplication.h>
#include <TTree.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TH1F.h>

//cria struct de nome PARTICLE para conter os dados do elétron inicial da ionização
typedef struct {
    Double_t energy;
    Float_t x, y, z;
    Float_t dx, dy, dz;
} PARTICLE;

using namespace std;

void lerParticles(){ //"/home/christian/Documents/Simulação/Geant4Parte2/Teste-build/particles.root"
	TFile *inputFile = TFile::Open("particles.root");
	TTree* theTree = (TTree*) inputFile->Get("Particles");
	TBranch* electron_branch = theTree->GetBranch("electron_branch");
	PARTICLE electron;
	electron_branch->SetAddress(&electron);

	int n_events = theTree->GetEntries();
	double x0, y0, z0, xi, yi, zi, xa, ya, ea, x1, y1, z1, ti, t1, ei, e1;
	int status, np;
	cout << "There are " << n_events << " events.\n";
	
	// Energy canvas
	TCanvas *cEnergy = new TCanvas("cE","Canvas Energy");
	// Energy histogram
	int nBins = 100;
	double xMin = 0.;
	double xMax = 10.;
	TH1D* hEnergy = new TH1D("hEnergy","Primary electron energy", nBins, xMin, xMax);
	hEnergy->GetXaxis()->SetTitle("E(keV)");
	hEnergy->GetYaxis()->SetTitle("Entries");
	
	// Looping through root file
	for (int i = 0; i < n_events; i++) {
		theTree->GetEntry(i);

		xi=electron.x;
		yi=electron.y;
		zi=electron.z;
		ei = electron.energy; //measured in eV
		/*cout << "Ionization number " << i << endl;
		cout << "Position: ";
		cout << "(" << xi << "," << yi << "," << zi << ")cm\t";
		cout << "Energy: " << ei << "eV\n";
		cout << endl;*/
		hEnergy->Fill(ei/1000.); //stored in keV
		
	}
	double meanVal = hEnergy->GetMean();
	double mpvBin = hEnergy->GetMaximumBin();
	cout << "Mean value = " << meanVal << " keV\n";
	cout << "Most probable value = " << hEnergy->GetXaxis()->GetBinCenter(mpvBin) << " keV\n";
	cEnergy->cd();
	hEnergy->Draw();
	cEnergy->SaveAs("HistEnergy.png","png");
	
}



int main(){
	lerParticles();
}
