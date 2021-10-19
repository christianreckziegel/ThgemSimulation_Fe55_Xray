/*Esta macro lê o resultFinal.root selecionando as entries que pertencem ao mesmo evento,
realiza o ajuste de curva obtendo o raio da circunferência para cada caso,
preenche um histograma com o raio para cada evento,
preenche um histograma 2D do raio em função do nº de pontos dos ajustes,
preenche um histograma 1D do valor de chi quadrado reduzido dos ajustes,
preenche um histograma 2D do chi quadrado reduzido em função do número de pontos.*/

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

//função para ajuste de Poisson
Double_t myPoisson(Double_t*x,Double_t*par){
  return par[0]*TMath::Poisson(x[0],par[1]);
}     

void resultAnalysis(){
	
	/* 1 - select same event, fit curve, fill histograms*/
	TString strEnergy = "6"; // in keV
	TString strBase = "ArResult_UpTo"+strEnergy+"keV_";
	TString strGas = "ArCO2(70/30)";
	//abrindo arquivo que salvará o histograma de energia
	//TFile f("Canvas_"+strEnergy+"keV.root","recreate");
	//abrindo arquivo contendo as avalanches
	TFile *inputFile = TFile::Open(strBase + "final.root");
	TTree* theTree = (TTree*) inputFile->Get("Results");
	Double_t xi, yi, xf, yf, monoEnergy, enRec1, enRec2;
	Int_t nEndPoint;
	theTree->SetBranchAddress("Avalanche_xi",&xi);
	theTree->SetBranchAddress("Avalanche_yi",&yi);
	theTree->SetBranchAddress("Avalanche_x",&xf);
	theTree->SetBranchAddress("Avalanche_y",&yf);
	theTree->SetBranchAddress("Gain",&nEndPoint);
	theTree->SetBranchAddress("Primary_eletron_initial_energy",&monoEnergy);
	
	int n_entries = theTree->GetEntries();
	cout << "Há " << n_entries << " entries.\n";
	
	TCanvas* cPosition = new TCanvas("Position", "2D position canvas");
	int nBinsX = 100;
	int nBinsY = 100;
	TH2D* hPosition = new TH2D("Position", "Avalanche position in X-Y plane", 
				nBinsX, -5., 5., //X position from 0 to 10 cm
				nBinsY, -5., 5.0); //Y position from 0 to 10 cm
	hPosition->GetXaxis()->SetTitle("X (cm)");
	hPosition->GetYaxis()->SetTitle("Y (cm)");
	hPosition->GetZaxis()->SetTitle("Entries");
	
	//creating avalanche gain histogram
	TCanvas *cAval = new TCanvas("cA","Canvas Avalanche gain");
	int nbinsA = 100; //50 é o ideal para 1000 elétrons
	TH1I* hAval = new TH1I("Avalanche", "Avalanche Gain for a "+strEnergy+"keV X-ray "+strGas, 
				nbinsA, 
				0., 5000.0);
	hAval->GetXaxis()->SetTitle("n^{o} of electrons");
	hAval->GetYaxis()->SetTitle("Entries");
	
	// creating electrons initial energy histogram
	TCanvas *cElec = new TCanvas("cE","Canvas Electrons initial energy");
	int nbinsE = 100;
	TH1D* hElec = new TH1D("Electrons_initial_energy", "Electrons initial energy for a "+strEnergy+"keV X-ray "+strGas, 
				nbinsE, 
				0., 5000.0);
	hElec->GetXaxis()->SetTitle("Energy (eV)");
	hElec->GetYaxis()->SetTitle("Entries");
	
	// creating electrons initial energy reconstruction histogram
	TCanvas *cRecon1 = new TCanvas("cR1","Canvas Electrons initial energy reconstruction");
	int nbinsR1 = 100;
	TH1D* hRecon1 = new TH1D("Electrons_initial_recon_energy1", "Electrons initial energy reconstruction for a "+strEnergy+"keV X-ray "+strGas, 
				nbinsR1, 
				0., 5000.0);
	hRecon1->GetXaxis()->SetTitle("Energy (eV)");
	hRecon1->GetYaxis()->SetTitle("Entries");
	
	// creating electrons initial energy reconstruction histogram
	TCanvas *cRecon2 = new TCanvas("cR2","Canvas Electrons initial energy reconstruction without lin. coef.");
	int nbinsR2 = 100;
	TH1D* hRecon2 = new TH1D("Electrons_initial_recon_energy2", "Electrons initial energy reconstruction for a "+strEnergy+"keV X-ray "+strGas+" without lin. coef.", 
				nbinsR1, 
				0., 5000.0);
	hRecon2->GetXaxis()->SetTitle("Energy (eV)");
	hRecon2->GetYaxis()->SetTitle("Entries");
	
	for(int i = 0; i < n_entries; i++){
		theTree->GetEntry(i);
		hAval->Fill(nEndPoint);
		hElec->Fill(monoEnergy);
		hPosition->Fill(xf, yf);
		// calculating energy reconstructed from fitting
		enRec1 = 1.004*nEndPoint - 17.91;
		hRecon1->Fill(enRec1);
		// calculating energu reconstructed from fitting without linear coefficient
		enRec2 = 1.004*nEndPoint;
		hRecon2->Fill(enRec2);
		
		
	}
	
	
	
	
	cPosition->cd();
	gStyle->SetPalette(55,0);
	hPosition->Draw("colz");
	cPosition->SaveAs(strBase+"PlanePosition.png","png");
	
	
	cAval->cd();
	hAval->Draw();
	cAval->SaveAs(strBase+"Gain.png","png");
	
	cElec->cd();
	hElec->Draw();
	cElec->SaveAs(strBase+"InitialElectrons.png","png");
	
	cRecon1->cd();
	hRecon1->Draw();
	//cElec->SaveAs(strBase+"InitialAndReconElectrons.png","png");
	cRecon1->SaveAs(strBase+"InitialRecon1.png","png");
	
	cRecon2->cd();
	hRecon2->Draw();
	//cElec->SaveAs(strBase+"InitialAndReconElectrons.png","png");
	cRecon2->SaveAs(strBase+"InitialRecon2.png","png");
	
	TCanvas *cMerged = new TCanvas("cR2","Canvas Electrons initial energy merged");
	cMerged->cd();
	hElec->SetStats(false);
	hElec->Draw();
	hRecon1->SetLineColor(kRed);
	hRecon1->SetStats(false);
	hRecon1->Draw("same");
	hRecon2->SetLineColor(kGreen);
	hRecon2->SetStats(false);
	hRecon2->Draw("same");
	TLegend* leg = new TLegend(0.6,0.7,0.95,0.9);
	leg->SetHeader("Initial electrons energy","C"); // option "C" allows to center the header
	leg->AddEntry(hElec,"True energy","l");
	leg->AddEntry(hRecon1,"Reconstructed energy","l");
	leg->AddEntry(hRecon2,"Reconstructed energy without lin. coef.","l");
	gStyle->SetLegendFont(50);
	leg->Draw();
	//cMerged->Write();
	cMerged->SaveAs(strBase+"ElectronsEnergyMerged.png","png");
	
	
	inputFile->Close();
	//f.Close();
	
	// Statistics Display
	// ======================================
	// The type of information shown in the histogram statistics box
	//  can be selected with gStyle->SetOptStat(mode).
	//
	//  The mode has up to seven digits that can be set to on(1) or off(0).
	//
	//  mode = iourmen  (default = 0001111)
	//    n = 1;  name of histogram is printed
	//    e = 1;  number of entries printed
	//    m = 1;  mean value printed
	//    r = 1;  rms printed
	//    u = 1;  number of underflows printed
	//    o = 1;  number of overflows printed
	//    i = 1;  integral of bins printed
	//
	// For example: gStyle->SetOptStat(11);
	// displays only the name of histogram and the number of entries.
	// For example: gStyle->SetOptStat(1101); 
	// displays the name of histogram, mean value and RMS.
	// WARNING: never call SetOptStat(000111); but SetOptStat(1111), 0001111
	// will  be taken as an octal number !!
	
	
	
}

int main(){
	resultAnalysis();
	return 0;
	
}
