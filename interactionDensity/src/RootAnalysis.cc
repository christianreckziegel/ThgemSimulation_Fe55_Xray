#include <sstream>

#include "RootAnalysis.hh"
#include "DetectorHit.hh"
//
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4EventManager.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

static RootAnalysis* instance = 0;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RootAnalysis::RootAnalysis()
{
  fFile = new TFile("particles.root","RECREATE");
  fTTree = new TTree("Particles","Tree that contains primary electron info");
  fluorTTree = new TTree("Fluorescence","Tree that contains fluorescence gamma energy");
  
  //static HIT hit;
  fTTree->Branch("electron_branch", &electron, "energy/D:x/F:y/F:z/F:dx/F:dy/F:dz/F");
  fluorTTree->Branch("fluor_branch", &fluorEnergy, "fluorEnergy/D");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RootAnalysis::~RootAnalysis()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RootAnalysis* RootAnalysis::Instance()
{
  if (instance == 0 )
  {
    instance = new RootAnalysis();
  }
  return instance;
}

// Write electrons data
void RootAnalysis::Write(G4double gammaEnergy)
{
  
  fluorEnergy = gammaEnergy/eV;
  fluorTTree->Fill();
  
}

// Write electrons data
void RootAnalysis::Write(G4double kinEnergy, G4ThreeVector position, G4ThreeVector momentum)
{

  electron.energy = kinEnergy/eV;
  electron.x = position.getX()/cm;
  electron.y = position.getY()/cm;
  electron.z = position.getZ()/cm;
  electron.dx = momentum.getX();
  electron.dy = momentum.getY();
  electron.dz = momentum.getZ();

  fTTree->Fill();
  //fFile->Write();
  //G4cout << hit.eDep << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RootAnalysis::Close()
{
  fTTree->Print();
  fluorTTree->Print();
  fFile->Write();
  fFile->Close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
