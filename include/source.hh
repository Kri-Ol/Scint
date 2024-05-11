#pragma once

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;
class G4Box;

namespace B1
{

/// The primary generator action class with particle gun.
///
/// The default kinematic is a 6 MeV gamma, randomly distribued
/// in front of the phantom across 80% of the (X,Y) phantom size.

class source : public G4VUserPrimaryGeneratorAction
{
    public: source();
    public: ~source() override;

    // method from the base class
    public: void GeneratePrimaries(G4Event*) override;

    // method to access particle gun
    const G4ParticleGun* GetParticleGun() const {
        return _part_gun;
    }

    private: G4ParticleGun* _part_gun     = nullptr;
    private: G4Box*         _envelope_box = nullptr;
};

}
