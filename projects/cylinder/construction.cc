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
	density = 1.e-3 *mg/cm3;
	pressure = 50. *atmosphere;
	temperature = 325. *kelvin;
	G4Material* atomicOAir = new G4Material(name="Atomic_Air",density, ncomponents=1, kStateGas,  temperature, pressure);
	atomicOAir->AddElement(elO, natoms=1);

	//G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
	G4double dens = 1e-25 *g/cm3;
	G4Material * Vacuum = new G4Material("Vacuum", dens, 1);
	G4Element * elN = new G4Element(name="Nitrogen", symbol="N", meanProtons= 7., 14.01*g/mole);
	Vacuum -> AddElement(elN, 1);

	G4Cons *solidWorld = new G4Cons("solidWorld", 0*m, 1.0*m, 0*m, 5.0*m,5.0*m, 0.0*deg, 360.0*deg);
	
	
	G4ThreeVector posm(0,0,-25e-4*tesla);
	G4MagneticField *mag = new G4UniformMagField(posm);

	G4FieldManager* fieldMgr = G4TransportationManager::GetTransportationManager() -> GetFieldManager();
	fieldMgr -> SetDetectorField(mag);
	fieldMgr->CreateChordFinder(mag);
//fieldMgr->GetChordFinder()->SetDeltaChord(0.1);


	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, atomicOAir, "logicWorld", fieldMgr);

	logicWorld-> SetVisAttributes(new G4VisAttributes(G4Colour(0.5,0.5,0.5)));
	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicWorld, "physWorld", 0, false, 0, true);

	return physWorld;
}
