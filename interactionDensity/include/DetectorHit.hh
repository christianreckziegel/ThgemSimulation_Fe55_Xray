#ifndef DetectorHit_h
#define DetectorHit_h 1

#include <vector>
#include <utility>
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4TouchableHistory.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"

//class G4Step;
//class G4HCofThisEvent;

class DetectorHit : public G4VHit
{
    public:
    DetectorHit();
    DetectorHit(const DetectorHit&);
    virtual ~DetectorHit();
    
    // Operators
    const DetectorHit& operator=(const DetectorHit&);
    G4int operator==(const DetectorHit&) const;
    
    inline void* operator new(size_t);
    inline void operator delete(void*);
    
    //virtual void Draw() const;
    virtual void Print();
    
    // Set methods
    void SetEnergyDeposit(G4double energy) {energyDeposit = energy;};
    void SetPosition(G4ThreeVector pos) {position = pos;};
    void SetMomentumDirection(G4ThreeVector momento) {momentum_direction = momento;};
    void SetParticleName(G4String name) {particleName = name;};
    void SetProcessName(G4String name) {processName = name;};
    void SetPDGid(G4int iD) {pdgID = iD;};
    void SetEventID(G4int iD) {eventID = iD;};
    
    // Get methods
    G4double GetEnergyDeposit() {return energyDeposit;};
    G4ThreeVector GetPosition(){ return position;};
    G4ThreeVector GetMomentumDirection(){ return momentum_direction;};
    G4String GetParticleName() {return particleName;};
    G4String GetProcessName() {return processName;};
    G4int GetPDGid() {return pdgID;};
    G4int GetEventID() {return eventID;};

    private:
    
    G4double energyDeposit;
    G4ThreeVector position;
    G4ThreeVector momentum_direction;
    G4String particleName;
    G4String processName;
    G4int pdgID;
    G4int eventID;
    
};

typedef G4THitsCollection<DetectorHit> DetectorHitsCollection;

extern G4ThreadLocal G4Allocator<DetectorHit>* DetectorHitAllocator;

inline void* DetectorHit::operator new(size_t)
{
    if(!DetectorHitAllocator)
        DetectorHitAllocator = new G4Allocator<DetectorHit>;
    return (void *) DetectorHitAllocator->MallocSingle();
}

inline void DetectorHit::operator delete(void *aHit)
{
    DetectorHitAllocator->FreeSingle((DetectorHit*) aHit);
}

#endif

