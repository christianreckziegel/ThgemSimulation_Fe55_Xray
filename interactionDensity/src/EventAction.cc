#include "EventAction.hh"
#include "DetectorHit.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "Analysis.hh"
#include "RunAction.hh"
#include "G4UnitsTable.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "RootAnalysis.hh"

//
// This class controls action before and after an event.
// The total energy collected from the hits is stored here as the total deposit energy of that event.
//

EventAction::EventAction()
: G4UserEventAction()
{}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event* )
{

}

void EventAction::EndOfEventAction(const G4Event* anEvent)
{
    G4cout << "Event " << anEvent->GetEventID() << " end!\n" << G4endl;
    
}
