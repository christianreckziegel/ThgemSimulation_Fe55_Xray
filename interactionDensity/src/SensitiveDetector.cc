#include "DetectorHit.hh"
#include "RootAnalysis.hh"
#include "SensitiveDetector.hh"
#include "G4HCofThisEvent.hh"
#include "G4THitsCollection.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4TouchableHistory.hh"
#include <G4VProcess.hh>
#include "G4RunManager.hh"
#include "RunAction.hh"
#include "Analysis.hh"
#include "G4UnitsTable.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

SensitiveDetector::SensitiveDetector(const G4String& name,
                                     const G4String& hitsCollectionName) :
G4VSensitiveDetector(name)
,fHitsCollection(NULL)
{
  collectionName.insert(hitsCollectionName);
}

SensitiveDetector::~SensitiveDetector()
{}

void SensitiveDetector::Initialize(G4HCofThisEvent* hce)
{
    fHitsCollection
    = new DetectorHitsCollection(SensitiveDetectorName, collectionName[0]);

    static G4int hcID = -1;
    if(hcID<0){
        hcID= G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    }
    hce->AddHitsCollection( hcID, fHitsCollection );
}

G4bool SensitiveDetector::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{
    //Printing particle name in current step
    G4Track* track         = aStep->GetTrack();
    const G4ParticleDefinition* particle = (track->GetParticleDefinition());
    const G4String particleName = particle->GetParticleName();
    const G4int pdgID = particle->GetPDGEncoding();
    G4cout << "Particle: " << std::setw(10) << particleName << G4endl;
    
    //Geting process name that the particle underwent
    G4String processName = ((aStep->GetPostStepPoint())->GetProcessDefinedStep())->GetProcessName();
    
    //Getting particle ID
    //G4int particleID = track->GetTrackID();
    
    //Energy deposit
    G4double energy = aStep->GetTotalEnergyDeposit();
    
    
    if (energy == 0.) return false; //Particle inside sensitive detector, but no interaction with the medium
    
    //
    //Getting the secondary electron information
    //
    const std::vector<const G4Track*>* secondary = aStep->GetSecondaryInCurrentStep();
    
    int number_secondaries = (*secondary).size();
    
    if (particleName=="gamma" && number_secondaries!=0) {
        G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
        G4double kinEnergy = 0;
        G4ThreeVector secondaryPosition;
        G4ThreeVector momentumDirection;
        for (int i=0; i<number_secondaries; i++) {
            const G4ParticleDefinition* secondaryDefinition = (*secondary)[i]->GetParticleDefinition();
            G4String secondaryName = secondaryDefinition->GetParticleName();
            
            if (secondaryName == "e-") {
                //Kinectic energy of the secondary
                kinEnergy = (*secondary)[i]->GetKineticEnergy();
                secondaryPosition = (*secondary)[i]->GetPosition();
                momentumDirection = (*secondary)[i]->GetMomentumDirection();

                G4cout << std::setw(10) << G4BestUnit(kinEnergy,"Energy") << G4endl;

                RootAnalysis* rootAnalysis = RootAnalysis::Instance();
                rootAnalysis->Write(kinEnergy, secondaryPosition, momentumDirection);
            }
            if(secondaryName == "gamma"){
            	G4cout << "COMPTON SCATTERING OCCURRED!" << G4endl;
            }
        }
    }
    //Getting the secondary electron information
    if(particleName=="e-" && number_secondaries !=0){
    	for (int i=0; i<number_secondaries; i++) {
	    	const G4ParticleDefinition* secondaryDefinition = (*secondary)[i]->GetParticleDefinition();
		G4String secondaryName = secondaryDefinition->GetParticleName();
	    	if(secondaryName == "gamma"){
		    G4cout << "ATOMIC DEEXCITATION FLUORESCENCE OCCURRED!" << G4endl;
		}
	}
    }
    

    //Storing the hit (interation) information of the current step
    DetectorHit* newHit = new DetectorHit();
    
    newHit->SetEnergyDeposit(energy);
    newHit->SetPosition (aStep->GetPostStepPoint()->GetPosition());
    newHit->SetParticleName(particleName);
    newHit->SetProcessName(processName);
    newHit->SetPDGid(pdgID);

    fHitsCollection->insert(newHit);

    newHit->Print();

    return true;
    
}



void SensitiveDetector::EndOfEvent(G4HCofThisEvent*)
{
}
