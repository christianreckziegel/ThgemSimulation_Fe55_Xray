void FluorescenceSpectrumCopper()
{
//=========Macro generated from canvas: cFluorGamma/Canvas: Fluorescence X-ray Energy
//=========  (Tue Oct  5 16:23:14 2021) by ROOT version 6.14/06
   TCanvas *cFluorGamma = new TCanvas("cFluorGamma", "Canvas: Fluorescence X-ray Energy",67,55,1213,745);
   cFluorGamma->Range(-0.43,-0.525,5.57,4.725);
   cFluorGamma->SetFillColor(0);
   cFluorGamma->SetBorderMode(0);
   cFluorGamma->SetBorderSize(2);
   cFluorGamma->SetFrameBorderMode(0);
   cFluorGamma->SetFrameBorderMode(0);
   
   TH1D *hFluorGammaEnergy__1 = new TH1D("hFluorGammaEnergy__1","Fluorescence X-ray spectrum in Copper",1000,0,5);
   hFluorGammaEnergy__1->SetBinContent(1,52);
   hFluorGammaEnergy__1->SetBinContent(164,2);
   hFluorGammaEnergy__1->SetBinContent(586,1);
   hFluorGammaEnergy__1->SetBinContent(587,4);
   hFluorGammaEnergy__1->SetBinContent(633,1);
   hFluorGammaEnergy__1->SetEntries(60);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *ptstats_LaTex = ptstats->AddText("hFluorGammaEnergy");
   ptstats_LaTex->SetTextSize(0.0368);
   ptstats_LaTex = ptstats->AddText("Entries = 60     ");
   ptstats_LaTex = ptstats->AddText("Mean  =  2.432");
   ptstats_LaTex = ptstats->AddText("Std Dev   =  0.935");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   hFluorGammaEnergy__1->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(hFluorGammaEnergy__1);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hFluorGammaEnergy__1->SetLineColor(ci);
   hFluorGammaEnergy__1->GetXaxis()->SetTitle("E(keV)");
   hFluorGammaEnergy__1->GetXaxis()->SetRange(35,994);
   hFluorGammaEnergy__1->GetXaxis()->SetLabelFont(42);
   hFluorGammaEnergy__1->GetXaxis()->SetLabelSize(0.035);
   hFluorGammaEnergy__1->GetXaxis()->SetTitleSize(0.035);
   hFluorGammaEnergy__1->GetXaxis()->SetTitleFont(42);
   hFluorGammaEnergy__1->GetYaxis()->SetTitle("Entries");
   hFluorGammaEnergy__1->GetYaxis()->SetLabelFont(42);
   hFluorGammaEnergy__1->GetYaxis()->SetLabelSize(0.035);
   hFluorGammaEnergy__1->GetYaxis()->SetTitleSize(0.035);
   hFluorGammaEnergy__1->GetYaxis()->SetTitleOffset(0);
   hFluorGammaEnergy__1->GetYaxis()->SetTitleFont(42);
   hFluorGammaEnergy__1->GetZaxis()->SetLabelFont(42);
   hFluorGammaEnergy__1->GetZaxis()->SetLabelSize(0.035);
   hFluorGammaEnergy__1->GetZaxis()->SetTitleSize(0.035);
   hFluorGammaEnergy__1->GetZaxis()->SetTitleFont(42);
   hFluorGammaEnergy__1->Draw("");
   
   TPaveText *pt = new TPaveText(0.1640688,0.9343684,0.8359312,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("Fluorescence X-ray spectrum in Copper");
   pt->Draw();
   cFluorGamma->Modified();
   cFluorGamma->cd();
   cFluorGamma->SetSelected(cFluorGamma);
}
