#pragma once


#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

namespace B1
{

/// Detector construction class to define materials and geometry.

class detector : public G4VUserDetectorConstruction
{
    public: detector() = default;
    public: ~detector() override = default;

    public: G4VPhysicalVolume* Construct() override;

    public: G4LogicalVolume* GetScoringVolume() const {
      return fScoringVolume;
    }

    protected: G4LogicalVolume* fScoringVolume = nullptr;
};

}
