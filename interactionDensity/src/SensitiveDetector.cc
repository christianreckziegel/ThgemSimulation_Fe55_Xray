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
#include "G4Gamma.hh"

SensitiveDetector::SensitiveDetector(const G4String& name, const G4String& hitsCollectionName):
G4VSensitiveDetector(name),
outRecI(0),
outRecS("NULL"),
idxPrimary(0),
isPhot(0),
fHitsCollection(NULL)
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
    G4double energyTrack = track->GetKineticEnergy();
    
    //Geting process name that the particle underwent
    G4String processName = ((aStep->GetPostStepPoint())->GetProcessDefinedStep())->GetProcessName();
    
    //Getting particle ID
    G4int particleID = track->GetTrackID();
    
    
    // Detecting fluorescence
    G4int fPhotoGamma = G4PhysicsModelCatalog::GetIndex("phot_fluo");
    G4int fComptGamma = G4PhysicsModelCatalog::GetIndex("compt_fluo");
    G4int idx = track->GetCreatorModelID();
    G4int idxSecond;
    if (track->GetDefinition() == G4Gamma::Gamma()) {
	    G4cout << "Gamma track!\n";
	    if(idx == fPhotoGamma || idx == fComptGamma) {
	      G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	      G4cout << "Fluorescence occurred!\n";
	      RootAnalysis* rootAnalysis = RootAnalysis::Instance();
              rootAnalysis->Write(energyTrack);
	    }
    
  }  
    
    
    //Energy deposit
    G4double energy = aStep->GetTotalEnergyDeposit();
    
    
    if (energy == 0.) return false; //Particle inside sensitive detector, but no interaction with the medium
    
    //
    //Getting the secondary electron information
    //
    const std::vector<const G4Track*>* secondary = aStep->GetSecondaryInCurrentStep();
    
    int number_secondaries = (*secondary).size();
    
    // X-ray and Fluorescence
    if (particleName=="gamma" && particleID == 1 && number_secondaries!=0) {
        G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
        G4double kinEnergy = 0;
        G4ThreeVector secondaryPosition;
        G4ThreeVector momentumDirection;
        for (int i=0; i<number_secondaries; i++) {
            const G4ParticleDefinition* secondaryDefinition = (*secondary)[i]->GetParticleDefinition();
            G4String secondaryName = secondaryDefinition->GetParticleName();
            idxSecond = (*secondary)[i]->GetCreatorModelID();
            if (secondaryName == "e-") {
                //Kinectic energy of the secondary
                kinEnergy = (*secondary)[i]->GetKineticEnergy();
                secondaryPosition = (*secondary)[i]->GetPosition();
                momentumDirection = (*secondary)[i]->GetMomentumDirection();

                G4cout << "PrimaryGammaElectron energy: " << std::setw(10) << G4BestUnit(kinEnergy,"Energy") << G4endl;

                RootAnalysis* rootAnalysis = RootAnalysis::Instance();
                rootAnalysis->Write(kinEnergy, secondaryPosition, momentumDirection);
                
                // Outside rectangle
                if(secondaryPosition.getX()/cm > 1.5 || secondaryPosition.getX()/cm < -1.5 || secondaryPosition.getY()/cm > 1.5 || secondaryPosition.getY()/cm < -1.5){
                	
                	G4cout << "Process outside rectangle at (" 
                	<< secondaryPosition.getX()/cm
                	<< "; " << secondaryPosition.getY()/cm
                	<<")cm: " << G4PhysicsModelCatalog::GetModelName(idxSecond)
                	<< G4endl;
                	outRecI++;
                	outRecS = G4PhysicsModelCatalog::GetModelName(idxSecond);
                	if(outRecS == "phot" ){ isPhot++; }
                }
            }
        }
    } else if(particleName=="gamma" && particleID != 1 && number_secondaries!=0){ // if not the primary gamma
    	// if occurred fluorescence, from photoelectric ef. or compton sc.
    	if(idx == fPhotoGamma || idx == fComptGamma){ 
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

		        G4cout << "FluoElectron energy: " << std::setw(10) << G4BestUnit(kinEnergy,"Energy") << G4endl;

		        RootAnalysis* rootAnalysis = RootAnalysis::Instance();
		        rootAnalysis->WriteFluElec(kinEnergy, secondaryPosition, momentumDirection);
		    }
		}
    	}
    }
    
    // Auger electrons
    /*if (particleName=="e-" && particleID == 1 && number_secondaries!=0) {
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

                G4cout << "SecondaryElectron energy: " << std::setw(10) << G4BestUnit(kinEnergy,"Energy") << G4endl;

                RootAnalysis* rootAnalysis = RootAnalysis::Instance();
                rootAnalysis->Write(kinEnergy, secondaryPosition, momentumDirection);
            }
        }
    }*/
    
    

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



void SensitiveDetector::EndOfEvent(G4HCofThisEvent*){
	G4cout << "There were " << outRecI << " electrons outside the rectangle in this event.\n";
	G4cout << "The last one was " << outRecS << G4endl;
	G4cout << "From these, " << isPhot << " were phot processes\n";
}
