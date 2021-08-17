#include "globals.hh"
#include "PhysicsList.hh"
#include "G4PhysicsListHelper.hh"

#include "G4EmPenelopePhysics.hh"
//#include "G4EmStandardPhysics.hh"

#include "G4PenelopeComptonModel.hh"
#include "G4ComptonScattering.hh"

#include "G4PenelopePhotoElectricModel.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4LivermorePhotoElectricModel.hh"

#include "G4RayleighScattering.hh"
#include "G4PenelopeRayleighModel.hh"

#include "G4PenelopeIonisationModel.hh"
#include "G4eIonisation.hh"

#include "G4PenelopeBremsstrahlungModel.hh"
#include "G4eBremsstrahlung.hh"

#include "G4UniversalFluctuation.hh"

#include "G4ParticleTypes.hh"
#include "G4ProcessManager.hh"

#include "G4eMultipleScattering.hh"

#include "G4VAtomDeexcitation.hh"
#include "G4UAtomicDeexcitation.hh"
#include "G4LossTableManager.hh"
#include "G4EmProcessOptions.hh"

#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

//
// This class defines all the particles and physical processes they can undergo.
//

PhysicsList::PhysicsList():  G4VModularPhysicsList()
{
    
    SetVerboseLevel(0);
    defaultCutValue = 0.1*mm;
    
}

PhysicsList::~PhysicsList()
{}

void PhysicsList::ConstructParticle()
{
    //Gamma
    G4Gamma::GammaDefinition();
    
    //Electron
    G4Electron::ElectronDefinition();
    
    //Positron
    G4Positron::PositronDefinition();
}

void PhysicsList::ConstructProcess()
{
    AddTransportation();
    
    //RegisterPhysics( new G4EmPenelopePhysics() );
    //RegisterPhysics( new G4EmStandardPhysics() );
    
    G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();
    
    auto particleIterator=GetParticleIterator();
    particleIterator->reset();

    while( (*particleIterator)() ){
        G4ParticleDefinition* particle = particleIterator->value();
        G4String particleName = particle->GetParticleName();
    
    
        //
        //Gamma processes
        //
        if (particleName == "gamma") {
    
            //Compton Scattering
            G4ComptonScattering* theComptonScattering = new G4ComptonScattering();
            G4PenelopeComptonModel* comptModel = new G4PenelopeComptonModel();
            comptModel->SetHighEnergyLimit(1.*GeV);
            theComptonScattering->SetEmModel(comptModel);
            ph->RegisterProcess(theComptonScattering, particle);
    
            //Photo Electric Effect
            G4PhotoElectricEffect* thePhotoEletric = new G4PhotoElectricEffect();
            G4PenelopePhotoElectricModel* photoEletric = new G4PenelopePhotoElectricModel();
            //G4LivermorePhotoElectricModel* photoEletric = new G4LivermorePhotoElectricModel();
            photoEletric->SetHighEnergyLimit(1.*GeV);
            thePhotoEletric->SetEmModel(photoEletric);
            ph->RegisterProcess(thePhotoEletric, particle);
            
            //Rayleigh Scattering
            G4RayleighScattering* theRayleigh = new G4RayleighScattering();
            G4PenelopeRayleighModel* theRayleighPenelopeModel = new G4PenelopeRayleighModel();
            theRayleighPenelopeModel->SetHighEnergyLimit(1.*GeV);
            theRayleigh->SetEmModel(theRayleighPenelopeModel, 1);
            ph->RegisterProcess(theRayleigh, particle);
        }

        //
        //Electron processes
        //
        else if (particleName == "e-") {
           
            //e- Ionisation
            G4eIonisation* eIoni = new G4eIonisation();
            G4PenelopeIonisationModel* theIoniPenelope = new G4PenelopeIonisationModel();
            theIoniPenelope->SetHighEnergyLimit(1.*GeV);
            eIoni->AddEmModel(0,theIoniPenelope,new G4UniversalFluctuation());
            eIoni->SetStepFunction(0.1, 100*um);
            ph->RegisterProcess(eIoni, particle);
    
            //Bremsstrahlung
            G4eBremsstrahlung* eBrem = new G4eBremsstrahlung();
            G4PenelopeBremsstrahlungModel* theBremPenelope = new G4PenelopeBremsstrahlungModel();
            theBremPenelope->SetHighEnergyLimit(1*GeV);
            eBrem->AddEmModel(0,theBremPenelope);
            ph->RegisterProcess(eBrem, particle);
            
            //Multiple Scattering
            ph->RegisterProcess(new G4eMultipleScattering(), particle);
        }
    
    }
    
    // Em options
    G4EmProcessOptions opt;
    
    // Ionization
    opt.SetSubCutoff(true);
    
    //
    // Deexcitation
    //
    G4VAtomDeexcitation* deexcitation = new G4UAtomicDeexcitation();
    G4LossTableManager::Instance()->SetAtomDeexcitation(deexcitation);
    deexcitation->SetFluo(true);
    
}

void PhysicsList::SetCuts()
{
    //SetCutsWithDefault();
    G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(250*eV, 10*MeV); //until 1MeV is ok
}
