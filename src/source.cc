
#include <string>

#include "source.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

namespace B1
{

source::source() {
    
    int n_particle = 1;
    _part_gun  = new G4ParticleGun(n_particle);

    // default particle kinematic
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    std::string particleName;
    G4ParticleDefinition* particle = particleTable->FindParticle(particleName="gamma");
    
    _part_gun->SetParticleDefinition(particle);
    _part_gun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
    _part_gun->SetParticleEnergy(6.0*MeV);
}


source::~source() {
    delete _part_gun;
}


void source::GeneratePrimaries(G4Event* anEvent)
{
    //this function is called at the begining of each event

    // In order to avoid dependence of PrimaryGeneratorAction
    // on DetectorConstruction class we get Envelope volume
    // from G4LogicalVolumeStore.

    double envSizeXY = 0.0;
    double envSizeZ  = 0.0;

    if (!_envelope_box) {
        G4LogicalVolume* envLV = G4LogicalVolumeStore::GetInstance()->GetVolume("Envelope");
        if ( envLV )
            _envelope_box = dynamic_cast<G4Box*>(envLV->GetSolid());
    }

    if ( _envelope_box ) {
        envSizeXY = _envelope_box->GetXHalfLength() * 2.0;
        envSizeZ  = _envelope_box->GetZHalfLength() * 2.0;
    } else {
        G4ExceptionDescription msg;
        msg << "Envelope volume of box shape not found.\n";
        msg << "Perhaps you have changed geometry.\n";
        msg << "The gun will be place at the center.";
        G4Exception("PrimaryGeneratorAction::GeneratePrimaries()", "MyCode0002",JustWarning,msg);
    }

    double size = 0.8;
    double x0 = size * envSizeXY * (G4UniformRand() - 0.5);
    double y0 = size * envSizeXY * (G4UniformRand() - 0.5);
    double z0 = -0.5 * envSizeZ;

    _part_gun->SetParticlePosition(G4ThreeVector(x0,y0,z0));
    _part_gun->GeneratePrimaryVertex(anEvent);
}

}
