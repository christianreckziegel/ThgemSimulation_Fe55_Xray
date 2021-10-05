

void calibCurve(){
	// Obs.: 1eV and 10eV failed the gaussian fit
	// Data
	Int_t n = 8;
	Double_t y[] = {26.56,25.36,108.9,508.1,1012.,2856.,5145.,10200.}; // gain
	Double_t x[] = {1.,10.,100.,500.,1000.,3000.,5000.,10000.}; // electron energy in eV
	Double_t ey[] = {30.69,22.74,76.28,148.2,192.6,224.4,410.1,666.5};
	Double_t ex[] = {0.,0.,0.,0.,0.,0.,0.,0.};
	
	TCanvas* c1 = new TCanvas("c1","Calibration curve");
	//gPad->SetLogx();
	//gPad->SetLogy();
	TGraphErrors* gr1 = new TGraphErrors(n,x,y,ex,ey);
	gr1->SetTitle("Calibration Curve");
	gr1->GetXaxis()->SetTitle("Gain (# of electrons)");
	gr1->GetYaxis()->SetTitle("Primary electron energy (eV)");
	gr1->SetMarkerColor(4);
	gr1->SetMarkerStyle(kFullDotLarge);
	c1->cd();
	gr1->Draw("AP");
	
	c1->SaveAs("calibrationCurveLogXY2.png","png");
}



int main(){
	calibCurve();
	return 0;
}
