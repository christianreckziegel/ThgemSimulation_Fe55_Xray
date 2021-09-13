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
	TFile *inputFile = TFile::Open("ArParticles.root");
	TTree* particleTree = (TTree*) inputFile->Get("Particles");
	TBranch* electron_branch = particleTree->GetBranch("electron_branch");
	PARTICLE electron;
	electron_branch->SetAddress(&electron);
	
	double x0, y0, z0, xi, yi, zi, xa, ya, ea, x1, y1, z1, ti, t1, ei, e1;
	int status, np;
	/* Primary X-ray electrons */
	int n_events = particleTree->GetEntries();
	cout << "There are " << n_events << " events in Particles TTree.\n";
	// Energy canvas
	TCanvas *cParticleEnergy = new TCanvas("cE","Canvas: Primary X-ray Electron Energy");
	// Energy histogram
	int nBins = 100;
	double eMin = 0.;
	double eMax = 10.;
	TH1D* hParticleEnergy = new TH1D("hParticleEnergy","Primary X-ray electron energy", nBins, eMin, eMax);
	hParticleEnergy->GetXaxis()->SetTitle("E(keV)");
	hParticleEnergy->GetYaxis()->SetTitle("Entries");
	// Looping through root file
	for (int i = 0; i < n_events; i++) {
		particleTree->GetEntry(i);

		xi=electron.x;
		yi=electron.y;
		zi=electron.z;
		ei = electron.energy; //measured in eV
		/*cout << "Ionization number " << i << endl;
		cout << "Position: ";
		cout << "(" << xi << "," << yi << "," << zi << ")cm\t";
		cout << "Energy: " << ei << "eV\n";
		cout << endl;*/
		hParticleEnergy->Fill(ei/1000.); //stored in keV
		
	}
	/*double meanVal = hParticleEnergy->GetMean();
	double mpvBin = hParticleEnergy->GetMaximumBin();
	cout << "Mean value = " << meanVal << " keV\n";
	cout << "Most probable value = " << hParticleEnergy->GetXaxis()->GetBinCenter(mpvBin) << " keV\n";*/
	cParticleEnergy->cd();
	hParticleEnergy->Draw();
	cParticleEnergy->SaveAs("primaryXrayElectronEnergy.png","png");
	
	/* Fluorescence electrons */
	// Getting TTree
	TTree* fluorElecTree = (TTree*) inputFile->Get("Fluorescence_electrons");
	TBranch* fluorElec_branch = fluorElecTree->GetBranch("electron_branch");
	fluorElec_branch->SetAddress(&electron);
	n_events = fluorElecTree->GetEntries();
	cout << "There are " << n_events << " events in fluorescence electrons TTree.\n";
	// Creating energy histogram for fluorescence electrons
	TCanvas *cFluorElecEnergy = new TCanvas("cFluorElec","Canvas: Fluorescence Electron Energy");
	TH1D* hFluorElecEnergy = new TH1D("hFluorElecEnergy","Fluorescence electron energy", nBins, eMin, eMax);
	hFluorElecEnergy->GetXaxis()->SetTitle("E(keV)");
	hFluorElecEnergy->GetYaxis()->SetTitle("Entries");
	for (int i = 0; i < n_events; i++) {
		fluorElecTree->GetEntry(i);

		xi=electron.x;
		yi=electron.y;
		zi=electron.z;
		ei = electron.energy; //measured in eV
		/*cout << "Ionization number " << i << endl;
		cout << "Position: ";
		cout << "(" << xi << "," << yi << "," << zi << ")cm\t";
		cout << "Energy: " << ei << "eV\n";
		cout << endl;*/
		hFluorElecEnergy->Fill(ei/1000.); //stored in keV
		
	}
	cFluorElecEnergy->cd();
	hFluorElecEnergy->Draw();
	cFluorElecEnergy->SaveAs("fluorElectronEnergy.png","png");
	
	/* Fluorescence X-ray */
	double fluorEnergy;
	double XrayEnergy;
	TTree* fluorGammaTree = (TTree*) inputFile->Get("Fluorescence_gammas");
	TBranch* fluorGamma_branch = fluorGammaTree->GetBranch("fluor_branch");
	fluorGamma_branch->SetAddress(&fluorEnergy);
	n_events = fluorGammaTree->GetEntries();
	cout << "There are " << n_events << " events in fluorescence X-ray TTree.\n";
	// Creating energy histogram for fluorescence X-ray
	nBins = 1000;
	eMin = 0.;
	eMax = 5.;
	TCanvas *cFluorGammaEnergy = new TCanvas("cFluorGamma","Canvas: Fluorescence X-ray Energy");
	TH1D* hFluorGammaEnergy = new TH1D("hFluorGammaEnergy","Fluorescence X-ray spectrum", nBins, eMin, eMax);
	hFluorGammaEnergy->GetXaxis()->SetTitle("E(keV)");
	hFluorGammaEnergy->GetYaxis()->SetTitle("Entries");
	for (int i = 0; i < n_events; i++) {
		fluorGammaTree->GetEntry(i);
		XrayEnergy = fluorEnergy;
		hFluorGammaEnergy->Fill(XrayEnergy/1000.); //stored in keV
		
	}
	cFluorGammaEnergy->cd();
	hFluorGammaEnergy->Draw();
	cFluorGammaEnergy->SaveAs("fluorGammaEnergy.png","png");
	
	
	
	
}



int main(){
	lerParticles();
}
