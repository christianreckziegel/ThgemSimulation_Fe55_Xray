#include "DetectorHit.hh"
#include "G4HCofThisEvent.hh"
#include "G4THitsCollection.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4TouchableHistory.hh"
#include "G4UnitsTable.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include <iomanip>

#include "G4RunManager.hh"
//#include "RunAction.hh"

G4ThreadLocal G4Allocator<DetectorHit>* DetectorHitAllocator=0;

DetectorHit::DetectorHit()
: G4VHit(),
energyDeposit(0.),
position(G4ThreeVector()),
momentum_direction(G4ThreeVector()),
particleName(""),
processName(""),
pdgID(-1),
eventID(-1)
{}

DetectorHit::~DetectorHit()
{}


DetectorHit::DetectorHit(const DetectorHit& right) :
G4VHit()
{
    energyDeposit = right.energyDeposit;
    position = right.position;
    momentum_direction = right.momentum_direction;
    particleName = right.particleName;
    processName = right.processName;
    pdgID = right.pdgID;
    eventID = right.eventID;
}

const DetectorHit& DetectorHit::operator=(const DetectorHit& right)
{
    energyDeposit = right.energyDeposit;
    position = right.position;
    momentum_direction = right.momentum_direction;
    particleName = right.particleName;
    processName = right.processName;
    pdgID = right.pdgID;
    eventID = right.eventID;
    return *this;
}

G4int DetectorHit::operator==(const DetectorHit& right) const
{
    return (this==&right) ? 1 : 0;
}

//void B2TrackerHit::Draw()
//{}

void DetectorHit::Print()
{
    G4cout
    << "Process: " << std::setw(7) << processName
    << "\n PDG ID: "  << std::setw(7) << pdgID
    << "\n Edep: "
    << std::setw(7) << G4BestUnit(energyDeposit,"Energy")
    << "    Position in x: "
    << std::setw(7) <<  G4BestUnit(position.getX(), "Length")
    << G4endl;

}
