#ifndef RootAnalysis_h
#define RootAnalysis_h 1

// Include root files
#include "TROOT.h"
#include "TFile.h"
#include "TSystem.h"
#include "TTree.h"

// Include geant4 files
#include "DetectorHit.hh"

typedef struct {
    Double_t energy;
    //Int_t pdgID;
    Float_t x, y, z;
    Float_t dx, dy, dz;
} PARTICLE;

class RootAnalysis 
{
public: 
  virtual ~RootAnalysis();
  
  static RootAnalysis* Instance();
  void Write(G4double kinEnergy, G4ThreeVector position, G4ThreeVector momentum);
  void Close();

protected:
  RootAnalysis(); 
  
private:
  TTree* fTTree;
  TFile* fFile;
  int fNevents;
  PARTICLE electron;
  
};
#endif
