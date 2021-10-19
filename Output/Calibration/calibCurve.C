

void calibCurve(){
	// Obs.: 1eV and 10eV failed the gaussian fit
	// Data
	Int_t n = 8;
	Double_t x[] = {26.56,25.36,108.9,508.1,1012.,2856.,5145.,10200.}; // gain
	Double_t y[] = {1.,10.,100.,500.,1000.,3000.,5000.,10000.}; // electron energy in eV
	Double_t ex[] = {30.69,22.74,76.28,148.2,192.6,224.4,410.1,666.5};
	Double_t ey[] = {0.,0.,0.,0.,0.,0.,0.,0.};
	
	TCanvas* c1 = new TCanvas("c1","Calibration curve");
	//gPad->SetLogx();
	//gPad->SetLogy();
	TGraphErrors* gr1 = new TGraphErrors(n,x,y,ex,ey);
	gr1->SetTitle("Calibration Curve");
	gr1->GetYaxis()->SetTitle("Primary electron energy (eV)");
	gr1->GetXaxis()->SetTitle("Gain (n^{o} of electrons)");
	gr1->SetMarkerColor(4);
	gr1->SetMarkerStyle(kFullDotLarge);
	c1->cd();
	gr1->Draw("AP");
	
	// Linear fitting
	TF1 *fStrLine = new TF1("fStrLine","x*[0] + [1]");
	fStrLine->SetParNames("Angular_coef","Linear_coef");
	fStrLine->SetParameters(0.5,0.);
	gr1->Fit(fStrLine);
	Double_t par[2]; //array to store the fit parameters
	//par[0]=angular coeficient
	//par[1]=linear coeficient
	fStrLine->GetParameters(&par[0]);
	
	c1->SaveAs("calibrationCurve1.png","png");
	
	// Configuring statistics box
	gStyle->SetOptFit();
	//gStyle->SetOptStat("e");
	//gStyle->SetOptFit(0011);
	//gStyle->SetStatY(0.1);// Set y-position (fraction of pad size)
	//gStyle->SetStatX(0.1);// Set x-position (fraction of pad size)
	//gStyle->SetStatW(0.5);// Set width of stat-box (fraction of pad size)
	//gStyle->SetStatH(0.6);
	
	c1->SaveAs("calibrationCurve.root","root");
	c1->SaveAs("calibrationCurve2.png","png");
}



int main(){
	calibCurve();
	return 0;
}
