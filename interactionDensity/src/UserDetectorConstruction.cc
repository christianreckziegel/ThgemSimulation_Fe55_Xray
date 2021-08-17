//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "UserDetectorConstruction.hh"
#include "SensitiveDetector.hh"

#include "globals.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SubtractionSolid.hh"
#include "G4PVParameterised.hh"
#include "G4SDManager.hh"
#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"
#include "G4Torus.hh"
#include "G4UserLimits.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4ios.hh"

#include "G4NistManager.hh"


UserDetectorConstruction::UserDetectorConstruction() : G4VUserDetectorConstruction()
{}

UserDetectorConstruction::~UserDetectorConstruction()
{}

G4VPhysicalVolume* UserDetectorConstruction::Construct()
{
    // Get nist material manager
    G4NistManager* nist = G4NistManager::Instance();
    
    //Materials
    G4Material* air  = nist->FindOrBuildMaterial("G4_AIR");
    G4Material* kapton = nist->FindOrBuildMaterial("G4_KAPTON");
    G4Material* copper = nist->FindOrBuildMaterial("G4_Cu");

    //Creating gas mixture
    
    G4double z, a, fractionOfNobleGas, density,temperature, pressure;
    G4String name, symbol;
    G4int ncomponents, natoms;

    a = 4.00*g/mole;
    G4Element* elHe  = new G4Element(name="Helium", symbol="He", z= 2., a);

    a = 21.18*g/mole;
    G4Element* elNe  = new G4Element(name="Neon", symbol="Ne", z= 10., a);
    
    a = 39.95*g/mole;
    G4Element* elAr  = new G4Element(name="Argon", symbol="Ar", z= 18., a);
    
    a = 131.29*g/mole;
    G4Element* elXe  = new G4Element(name="Xenon", symbol="Xe", z= 54., a);
    
    a = 16.00*g/mole;
    G4Element* elO  = new G4Element(name="Oxygen", symbol="O", z= 8., a);
    
    a = 12.01*g/mole;
    G4Element* elC  = new G4Element(name="Carbon", symbol="C", z= 6., a);
    
    //The constructor checks the density and automatically sets the state to gas in STP conditions
    //below a given threshold (10 mg/cm3)
    
    density = 1.960*mg/cm3;
    G4Material* CO2 = new G4Material(name="Carbonic Gas", density, ncomponents=2);
    CO2->AddElement(elC, natoms=1);
    CO2->AddElement(elO, natoms=2);
    // Choosing gas composition from executable parameter
    G4Material* gas;
    if (*argument == '1') {
        density = 1.780*mg/cm3; //Density for Argon alone
        
        gas = new G4Material(name="Gas", density, ncomponents=1, kStateGas, temperature=298*kelvin, pressure=1*atmosphere);
        
        gas->AddElement(elAr, 1);
    }
    
    else if (*argument == '2') {
        density = 5.894*mg/cm3; //Density for Xenon alone
        
        gas = new G4Material(name="Gas", density, ncomponents=1, kStateGas, temperature=298*kelvin, pressure=atmosphere);
        
        gas->AddElement(elXe, 1);
    }
    
    else if (*argument == '3') {
        //CO2 alone
        
        gas = new G4Material(name="Gas", density, ncomponents=1, kStateGas, temperature=298*kelvin, pressure=1*atmosphere);
        
        gas->AddMaterial(CO2, 1);
    }
    
    else if (*argument == '4') {
        
        density = (0.7*1.780+0.3*1.960)*mg/cm3; //Density for mix of Argon and CO2
        
        gas = new G4Material(name="Gas", density, ncomponents=2, kStateGas, temperature=298*kelvin, pressure=1*atmosphere);
        
        fractionOfNobleGas = 70.0*perCent;
        gas->AddElement(elAr, fractionOfNobleGas);
        gas->AddMaterial(CO2, 1-fractionOfNobleGas);
    }
    
    else{
        
        density = (0.7*5.894+0.3*1.960)*mg/cm3; //Density for mix of Xenon and CO2
        
        gas = new G4Material(name="Gas", 4*density, ncomponents=2, kStateGas, temperature=298*kelvin, pressure=4*atmosphere);
        
        fractionOfNobleGas = 70.0*perCent;
        gas->AddElement(elXe, fractionOfNobleGas);
        gas->AddMaterial(CO2, 1-fractionOfNobleGas);
    }
    
    //
    // World
    //
    
    G4Box* world =
        new G4Box("World",                          //its name
            1.*m, 1.*m, 1.*m);                   //its size
    
    G4LogicalVolume* logicalWorld =
        new G4LogicalVolume(world,                  //its solid
                            air,                    //its material
                            "World");               //its name
    
    G4VPhysicalVolume* physicalWorld =
        new G4PVPlacement(0,                        //no rotation
                          G4ThreeVector(),          //at (0,0,0)
                          logicalWorld,             //its logical volume
                          "World",                  //its name
                          0,                        //its mother volume (none)
                          false,                    //no boolean operation
                          0,                        //copy number
                          true);                    //check overlaps
    
    
    /* Dimensional parameters */
    G4double internalEdge = 10.*cm;
    G4double driftThick = 0.9*cm;
    G4double inductionThick = 0.9*cm;
    G4double wallThick = 0.3*cm;
    G4double kaptonThick = 0.05*mm;
    G4double copperThick = 1.5*mm;
    // thgem dimensions
    G4double thgem_up_copp = 0.001*cm;
    G4double thgem_down_copp = 0.001*cm;
    G4double thgem_kapt = 0.05*cm;
    G4double thgemThick = thgem_up_copp + thgem_kapt + thgem_down_copp;
    
    
    // Position parameters (thgem at origin, oriented in the z plane)
    G4double z_gas = (driftThick+thgemThick-inductionThick)/2.;
    //G4double z_kapton = driftThick + thgemThick + kaptonThick/2.;
    G4double z_kapton = z_gas + (driftThick+thgemThick+inductionThick+kaptonThick)/2.;
    //G4double z_copper = -(thgemThick + 2.*inductionThick + copperThick)/2.;
    G4double z_copper = z_gas -thgemThick - (driftThick+inductionThick+copperThick)/2.;
    
    
    
    
    // Gas Box
    G4Box* gasBox =
        new G4Box("Gas",                   //its name
                  internalEdge/2., internalEdge/2., (driftThick+thgemThick+inductionThick)/2.);     //its size
    G4LogicalVolume* logicalGasBox =
        new G4LogicalVolume(gasBox,           //its solid
                            gas,                    //its material
                            "Gas");        //its name
    // Definig walls for the gaseous volume with boolean operation
    G4Box* BigBox = new G4Box("Walls", 
    				(internalEdge/2.) + wallThick, (internalEdge/2.) + wallThick, 
    				(driftThick+thgemThick+inductionThick)/2.);
    G4SubtractionSolid* wallBox = new G4SubtractionSolid("BigBox-GasBox", BigBox, gasBox);
    G4LogicalVolume* logWallBox = new G4LogicalVolume(wallBox,
    						      kapton,
    						      "Walls");
    G4PVPlacement* wallPosition = new G4PVPlacement(0,
    						    G4ThreeVector(0*mm,0*mm,z_gas),
    						    logWallBox,
    						    "Walls",
    						    logicalWorld,
    						    false,
    						    0,
    						    true);
    G4PVPlacement* gasPosition = new G4PVPlacement(0,                            //no rotation
					      G4ThreeVector(0*mm,0*mm,z_gas),      //at (0,0,z_gas)
					      logicalGasBox,          //its logical volume
					      "Gas",               //its name
					      logicalWorld,                 //its mother volume, logWallBox or logicalWorld?
					      false,                        //no boolean operation
					      1,                            //copy number
					      true);                        //check overlaps
    
    // Defining upper cover made of kapton
    G4Box* kaptUpCover = new G4Box("KaptonUpperCover", (internalEdge/2.)+wallThick,(internalEdge/2.)+wallThick,kaptonThick/2.);
    G4LogicalVolume* logKaptUpCover = new G4LogicalVolume(kaptUpCover, kapton, "KaptonUpperCover");
    G4PVPlacement* kaptUpCoverPosition = new G4PVPlacement(0,
    							   G4ThreeVector(0*cm,0*cm, z_kapton),
    							   logKaptUpCover,
    							   "KaptonUpperCover",
    							   logicalWorld,
    							   false,
    							   2,
    							   true);
    // Defining lower cover made of copper
    G4Box* CuLowCover = new G4Box("CopperLowerCover",(internalEdge/2.)+wallThick,(internalEdge/2.)+wallThick,copperThick/2.);
    G4LogicalVolume* logCuLowCover = new G4LogicalVolume(CuLowCover, copper, "CopperLowerCover");
    G4PVPlacement* CuLowCoverPosition = new G4PVPlacement(0,
    							   G4ThreeVector(0,0,z_copper),// -2.5cm - 0.15cm
    							   logCuLowCover,
    							   "CopperLowerCover",
    							   logicalWorld,
    							   false,
    							   3,
    							   true);
    // Defining ThickGEM
    //copper upper cover
    G4Box* coppUpTG = new G4Box("CopperUpperTGEM", internalEdge/2.,internalEdge/2.,thgem_up_copp/2.);
    G4LogicalVolume* logcoppUpTG = new G4LogicalVolume(coppUpTG, copper, "CopperUpperTGEM");
    G4PVPlacement* coppUpTGPosition = new G4PVPlacement(0,
    							   G4ThreeVector(0,0,thgem_kapt/2. + thgem_up_copp/2.),// 0.245*mm
    							   logcoppUpTG,
    							   "CopperUpperTGEM",
    							   logicalGasBox,
    							   false,
    							   4,
    							   true);
    //kapton middle layer
    G4Box* kapTG = new G4Box("KaptonMiddleLayer", internalEdge/2.,internalEdge/2.,thgem_kapt/2.);
    G4LogicalVolume* logkapTG = new G4LogicalVolume(kapTG, kapton, "KaptonMiddleLayer");
    G4PVPlacement* kapTGPosition = new G4PVPlacement(0,
    							   G4ThreeVector(0,0,0*cm),
    							   logkapTG,
    							   "KaptonMiddleLayer",
    							   logicalGasBox,
    							   false,
    							   5,
    							   true);
    //copper lower cover
    G4Box* coppLowTG = new G4Box("CopperLowerTGEM", internalEdge/2.,internalEdge/2.,thgem_down_copp/2.);
    G4LogicalVolume* logcoppLowTG = new G4LogicalVolume(coppLowTG, copper, "CopperLowerTGEM");
    G4PVPlacement* coppLowTGPosition = new G4PVPlacement(0,
    							   G4ThreeVector(0,0,-thgem_kapt/2. - thgem_up_copp/2.),
    							   logcoppLowTG,
    							   "CopperLowerTGEM",
    							   logicalGasBox,
    							   false,
    							   6,
    							   true);
    
    
    
    
    
    
    
    
    
    // Changing colors for better visualization of materials
    // Kapton materials
    G4VisAttributes* visKapton = new G4VisAttributes(G4Colour(255./255.,128./255.,0.)); //light brown
    //visKapton->SetForceWireframe(true);
    visKapton->SetVisibility(true);
    logKaptUpCover->SetVisAttributes(visKapton);
    logkapTG->SetVisAttributes(visKapton);
    G4VisAttributes* visWalls = new G4VisAttributes(G4Colour(160./255.,160./255.,160./255.)); //grey
    //visWalls->SetForceWireframe(true);
    //visWalls->SetForceSolid(true);
    visWalls->SetVisibility(true);
    logWallBox->SetVisAttributes(visWalls);
    // Copper materials
    G4VisAttributes* visCopper = new G4VisAttributes(G4Colour(102./255.,51./255.,0./255.)); //dark brown
    //visCopper->SetForceWireframe(true);
    //visCopper->SetForceSolid(true);
    visCopper->SetVisibility(true);
    logcoppUpTG->SetVisAttributes(visCopper);
    logcoppLowTG->SetVisAttributes(visCopper);
    logCuLowCover->SetVisAttributes(visCopper);
    // Gas
    G4VisAttributes* visGas = new G4VisAttributes(G4Colour(153./255.,204./255.,255./255.)); //light blue
    //visGas->SetForceWireframe(true);
    //visGas->SetForceSolid(true);
    visGas->SetVisibility(true);
    logicalGasBox->SetVisAttributes(visGas);
    
    
    
    //
    //Sensitive Detector
    //
    G4String nameSD = "TrackerSD";
    
    SensitiveDetector* aTrackerSD = new SensitiveDetector(nameSD, "DetectorHitsCollection");
    G4SDManager::GetSDMpointer()->AddNewDetector(aTrackerSD);
    SetSensitiveDetector("Gas", aTrackerSD, true);
    SetSensitiveDetector("Walls", aTrackerSD, true);
    SetSensitiveDetector("KaptonUpperCover", aTrackerSD, true);
    SetSensitiveDetector("CopperLowerCover", aTrackerSD, true);
    SetSensitiveDetector("CopperUpperTGEM", aTrackerSD, true);
    SetSensitiveDetector("KaptonMiddleLayer", aTrackerSD, true);
    SetSensitiveDetector("CopperLowerTGEM", aTrackerSD, true);
    
    
    
    return physicalWorld;
    
}



