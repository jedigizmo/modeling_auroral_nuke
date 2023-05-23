#include "generator.hh"
#include <iostream>

using namespace std;

MyPrimaryGenerator::MyPrimaryGenerator()
{
	fParticleGun = new G4ParticleGun(1);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
	delete fParticleGun;
}


void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	G4String particleName="electron";
	G4ParticleDefinition *particle = particleTable->FindParticle("e-");
	
	G4ThreeVector pos(0. *m ,0. *m ,5. *m);
	G4ThreeVector mom(0.,-0.21644,-0.976296);

	fParticleGun->SetParticlePosition(pos);
	fParticleGun->SetParticleMomentumDirection(mom);
	fParticleGun->SetParticleEnergy(5.*keV);
	fParticleGun->SetParticleDefinition(particle);


	for(int i = 0; i < 10; i++){
	double num1 = ((rand() % 100) / 10.0) - 5.0;
	double num2 = ((rand() % 100) / 10.0) - 5.0;
  	pos.set(num1*m  , num2*m, 5. *m);
	fParticleGun->SetParticlePosition(pos);
	fParticleGun->GeneratePrimaryVertex(anEvent);
	}
}


