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
	TString strEnergy = "100eV";
	TString strEnergTitle = "100 eV";
	TString strBase = "CalibResult"+strEnergy+"_";
	TString strGas = "ArCO2(70/30)";
	//abrindo arquivo que salvará o histograma de energia
	//TFile f("Histog_"strEnergy+"keV.root","recreate");
	//abrindo arquivo contendo as avalanches
	TFile *inputFile = TFile::Open(strBase + "final.root");
	TTree* theTree = (TTree*) inputFile->Get("Results");
	Double_t xi, yi, xf, yf, eEnerg;
	Int_t gain;
	theTree->SetBranchAddress("Avalanche_xi",&xi);
	theTree->SetBranchAddress("Avalanche_yi",&yi);
	theTree->SetBranchAddress("Avalanche_x",&xf);
	theTree->SetBranchAddress("Avalanche_y",&yf);
	theTree->SetBranchAddress("Gain",&gain);
	theTree->SetBranchAddress("Primary_eletron_initial_energy",&eEnerg);
	
	
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
	
	//creating avalanche histogram
	TCanvas *cAval = new TCanvas("cA","Canvas Avalanche");
	int nbinsA = 75; //75 é o ideal para 1000 elétrons
	TH1I* hAval = new TH1I("Avalanche", "Avalanche Gain for a "+strEnergTitle+" X-ray "+strGas, 
				nbinsA, 
				0., 2000.0);
	hAval->GetXaxis()->SetTitle("n^{o} of electrons");
	hAval->GetYaxis()->SetTitle("Entries");
	
	for(int i = 0; i < n_entries; i++){
		theTree->GetEntry(i);
		hAval->Fill(gain);
		cout << "gain = " << gain << endl;
		hPosition->Fill(xf, yf);
		
	}
	
	
	
	
	cPosition->cd();
	gStyle->SetPalette(55,0);
	hPosition->Draw("colz");
	cPosition->SaveAs(strBase+"PlanePosition.png","png");
	
	
	cAval->cd();
	hAval->Draw();
	cAval->SaveAs(strBase+"Gain.png","png");
	
	
	//fitting gaussian distribuition for GAIN histogram
	cAval->cd();
	TF1 *fE = new TF1("fitE","gaus");
	hAval->Fit(fE);
	Double_t parE[3]; //array to store the fit parameters
	Double_t parError[3] = {fE->GetParError(0),fE->GetParError(1),fE->GetParError(2)};
	//par[0]=constant
	//par[1]=most probable value
	//par[2]=sigma
	fE->GetParameters(&parE[0]);
	cout << "parE[] = [" << parE[0] << ","<< parE[1] << ","<< parE[2] << "]\n";
	cout << "parError[] = [" << parError[0] << ","<< parError[1] << ","<< parError[2] << "]\n";
	//parError = fE->GetParErrors();
	cAval->Update();
	//configuring statistics box
	gStyle->SetOptStat("e");
	gStyle->SetOptFit(0011);
	/*gStyle->SetStatY(0.9);// Set y-position (fraction of pad size)
	gStyle->SetStatX(0.9);// Set x-position (fraction of pad size)
	gStyle->SetStatW(0.4);// Set width of stat-box (fraction of pad size)
	gStyle->SetStatH(0.5);// Set height of stat-box (fraction of pad size)*/
	cAval->Update();
	hAval->Draw();
	cAval->SaveAs(strBase+"HistGainFitted.png","png");
	
	
	
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
