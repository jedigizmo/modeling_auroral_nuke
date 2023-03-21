#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
	G4double temperature, pressure, density, elementMole, meanProtons;
	G4int n, ncomponents, natoms;
	G4String name, symbol;

	elementMole = 16.00*g/mole;
	G4Element* elO = new G4Element(name="Oxygen", symbol="O", meanProtons = 8., elementMole);
	G4NistManager *nist = G4NistManager::Instance();
	density = 27. *mg/cm3;
	pressure = 50. *atmosphere;
	temperature = 325. *kelvin;
	G4Material* atomicOAir = new G4Material(name="Atomic_Air",density, ncomponents=1, kStateGas,  temperature, pressure);
	atomicOAir->AddElement(elO, natoms=1);	
	//G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");

	G4Box *solidWorld = new G4Box("solidWorld", 1*m, 1*m, 1*m);
	
	
	G4ThreeVector posm(0,-0.5,0);
	G4MagneticField *mag = new G4UniformMagField(posm);

	G4FieldManager* fieldMgr = G4TransportationManager::GetTransportationManager() -> GetFieldManager();
	fieldMgr -> SetDetectorField(mag);
	fieldMgr->CreateChordFinder(mag);
//fieldMgr->GetChordFinder()->SetDeltaChord(0.1);


	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, atomicOAir,"logicWorld", fieldMgr);

	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicWorld, "physWorld", 0, false, 0, true);

	return physWorld;
}
