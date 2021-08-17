#include "PrimaryGeneratorAction.hh"
#include "UserDetectorConstruction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4MuonMinus.hh"
#include "globals.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "Randomize.hh"

//
// Primary Generator creates the first particle to be tracked.
// Hence, our beam is defined here.
//
//

PrimaryGeneratorAction::PrimaryGeneratorAction(): 
G4VUserPrimaryGeneratorAction() {
    
    G4int n_particle = 1;
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle("gamma"); //"e-"
    gun = new G4ParticleGun(n_particle);
    gun->SetParticleDefinition(particle);
    gun->SetParticleMomentumDirection(G4ThreeVector(0,0,-1));// original (0,0,-1)
    gun->SetParticlePosition(G4ThreeVector(0,0, 4.*cm)); // (0,0, 4.*cm)
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() {
    delete gun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {

    
    //G4double phi = (G4RandGauss::shoot(0., 1./12))*pi;       //Mean and standard deviation
    //G4double theta = G4UniformRand()*twopi;                  //Uniform range from 0 to 2pi
    
    //Spherical coordinates for r=1
    //gun->SetParticleMomentumDirection(G4ThreeVector(sin(phi)*cos(theta),sin(phi)*sin(theta),cos(phi)));

    G4double x = (15 - G4UniformRand()*30)*mm;
    G4double y = (15 - G4UniformRand()*30)*mm;

    gun->SetParticlePosition(G4ThreeVector(x,y, 4.*cm)); //(x,y,4.*cm)

    //Gamma energy
    double energy = (G4RandGauss::shoot(5900, 50))*eV; //Gaussian distribuition mu = 5900, sigma = 50
    //double energy = 5900*eV;
    
    gun->SetParticleEnergy(energy);
    gun->GeneratePrimaryVertex(anEvent);
}

