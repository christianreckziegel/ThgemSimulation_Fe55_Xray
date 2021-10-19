#include <iostream>
#include <fstream>

#include <TApplication.h>
#include <TTree.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TRandom1.h>

#include "Garfield/ComponentElmer.hh"
#include "Garfield/ComponentAnalyticField.hh"
#include "Garfield/ViewField.hh"
#include "Garfield/ViewFEMesh.hh"
#include "Garfield/ViewCell.hh"
#include "Garfield/ViewSignal.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/AvalancheMicroscopic.hh"
#include "Garfield/AvalancheMC.hh"
#include "Garfield/Random.hh"
#include "Garfield/Plotting.hh"

using namespace Garfield;
using namespace std;
typedef struct {
    Double_t energy;
    Float_t x, y, z;
    Float_t dx, dy, dz;
} PARTICLE;

int main(int argc, char * argv[]) {
  float t;
  t = clock();

  int index = int(atoi(argv[1]));
  std::string strIndex = std::string(argv[1]);


  //int monoEnergy = int(atoi(argv[2]));
  //std::string strEnergy = std::string(argv[2]);
  std::string strEnergy = "1";
  double monoEnergy = 1.;
  
  //TApplication app("app", &argc, argv); //it doesn't plot without that
  //plottingEngine.SetDefaultStyle();
  //Garfield::randomEngine.Seed(1);
  // Dimensions of the GEM [m]
  const double pitch = 0.1;//0.0003;
  //const double kapton = 50.e-4;
  //const double metal = 5.e-4;
  //const bool debug = true;
  const double pad_side = 0.95;

  // Setup the gas.
  MediumMagboltz* gas = new MediumMagboltz();
  gas->SetComposition("ar", 70., "co2", 30.);
  gas->SetTemperature(293.15);
  gas->SetPressure(760.); // 1 atm in [Torr]
  gas->EnableDrift();
  gas->SetMaxElectronEnergy(7000.);
  //gas->Initialise();
  gas->EnablePenningTransfer(0.6, 0);
  //gas->LoadGasFile("xe_70_co2_30.gas");

  // Define path to executable
  std::string path = "~/Documents/Simulação/Publication_Lucas/Garfield_step_of_simulation";
  // Load the electric field map.
  ComponentElmer* elm = new ComponentElmer(
      "thgem/mesh.header", 
      "thgem/mesh.elements", 
      "thgem/mesh.nodes",
      "thgem/dielectrics.dat", 
      "thgem/thgem.result", "cm");
  elm->EnablePeriodicityY();
  elm->EnableMirrorPeriodicityX();
  elm->PrintRange();
  elm->SetMedium(0, gas);
  //elm->SetMagneticField(0., 0., 0.); // Magnetic field in Tesla


  // Set up a sensor object.
  Sensor* sensor = new Sensor();
  sensor->AddComponent(elm);
  sensor->SetArea(-50., -50., -10., 50.,  50.,  10.);

  const double tmin = 0., tmax = 200;
  const int nTimeBins = 5000;
  const double tstep = (tmax-tmin)/nTimeBins;

  sensor->SetTimeWindow(tmin, tstep, nTimeBins);

  // Create an avalanche object
  AvalancheMicroscopic* aval = new AvalancheMicroscopic();
  aval->SetSensor(sensor);
  aval->EnableSignalCalculation();
  aval->SetCollisionSteps(100);

  
  double xi, yi, zi, xa, ya, ea, x1, y1, z1, ti, t1, ei, e1;
  int status, np, dxi, dyi, dzi;

  //TH2* multiplied_hist = new TH2D("h1","Electrons after multiplied", /* X-dimension */ 10, -1.5, 1.5, /* Y-dimension */ 10, -1.5, 1.5);

  double bin_width = 0.05; // In centimeters
  double x_start = -10., x_end = 10.;
  int n_bins = (x_end - x_start)/bin_width;

  TH1D *readout_x = new TH1D("readout_x","X (cm) position of electrons",n_bins,x_start,x_end);
  TH1D *readout_y = new TH1D("readout_y","Y (cm) position of electrons",n_bins,x_start,x_end);

  //
  // Creating the file and Tree object that will contain the results
  //
  
  TString fileName = "Result/CalibResult"+strEnergy+"eV_"+strIndex+".root";
  TFile * resultFile = new TFile(fileName,"RECREATE","Results from THGEM simulation");
  TTree* resultTree = new TTree("Results","Tree that contains the electrons from the avalanche");
  
  resultTree->Branch("Avalanche_xi",&xi);
  resultTree->Branch("Avalanche_yi",&yi);
  resultTree->Branch("Avalanche_x",&xa);
  resultTree->Branch("Avalanche_y",&ya);
  resultTree->Branch("Gain",&np);
  resultTree->Branch("Primary_eletron_initial_energy",&monoEnergy);
  
  TRandom1 r1(0);
  
  // Run only once
  for (int i = 0; i < 1; i++) {
    //// Sorting initial position inside -1.5 < x,y < 1.5
    //xi=(1.5 - (gRandom->Rndm(0))*3.0);
    //yi=(1.5 - (gRandom->Rndm(0))*3.0);
    xi=(1.5 - (r1.Rndm())*3.0);
    yi=(1.5 - (r1.Rndm())*3.0);
    zi=0.8; //cm
    
    // Initial direction
    dxi = 0;
    dyi = 0;
    dzi = -1;
    
    //ei = 0.;
    ei = monoEnergy;
    
    aval->AvalancheElectron(xi, yi, zi, 0., ei, dxi, dyi, dzi);
    std::cout << "X coordinate: " << xi << std::endl;
    std::cout << "Y coordinate: " << yi << std::endl;
    std::cout << "Z coordinate: " << zi << std::endl;
    std::cout << "Avalanche number " << i+1 << " is done." << std::endl;
    np=aval->GetNumberOfElectronEndpoints();
    std::cout << "Energy: " << ei << " eV\n";
    std::cout << "There were " << np << " electron endpoints.\n";
    for (int j=0; j<np; j++){
        aval->GetElectronEndpoint(j, xi, yi, zi, ti, ei, x1, y1, z1, t1, e1, status);
        readout_x->Fill(x1);
        readout_y->Fill(y1);
        //multiplied_hist->Fill(x1,y1);
    }

    int e_total_x = 0, e_total_y = 0, e_temp_x, e_temp_y;
    double x_parcial = 0, y_parcial = 0;
    for (int k = 1; k <= n_bins; k++) {
    	e_temp_x = readout_x->GetBinContent(k);
        e_total_x += e_temp_x;
        
        x_parcial += (x_start + (k*1.0-0.5)*bin_width)*e_temp_x;

	e_temp_y = readout_y->GetBinContent(k);
        e_total_y += e_temp_y;

        y_parcial += (x_start + (k*1.0-0.5)*bin_width)*e_temp_y;
    }

    if (e_total_x != 0 && e_total_y != 0){
            xa = x_parcial/e_total_x;
	    ya = y_parcial/e_total_y;
            //std::cout << "The x0 is " << x0 << std::endl;
            //std::cout << "The xa is " << xm << std::endl;
                
            resultTree->Fill();
    }

    readout_x->Reset();
    readout_y->Reset();

 }

  resultTree->Print();
  resultFile->Write();
  resultFile->Close();

  std::cout << "Simulation done!" << std::endl;
  t=clock()-t;
  std::cout << "It took " << t/CLOCKS_PER_SEC << " seconds to run" << std::endl;

  //multiplied_hist->Draw("colz");
  //app.Run(kTRUE);
  
  return 0;
}
