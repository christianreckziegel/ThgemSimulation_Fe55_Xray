#include "RunAction.hh"
#include "Analysis.hh"
#include "G4Run.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "RootAnalysis.hh"

//
// This class is called before and after the run of the simulation.
// The ROOT data files are created here.
//

RunAction::RunAction()
{}

RunAction::~RunAction()
{
   delete G4AnalysisManager::Instance();
}

void RunAction::BeginOfRunAction(const G4Run*)
{
    
}

void RunAction::EndOfRunAction(const G4Run*)
{ 
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
    
    RootAnalysis* rootAnalysis = RootAnalysis::Instance();
    rootAnalysis->Close();
}
