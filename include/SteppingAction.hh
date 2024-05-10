#pragma once

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class G4LogicalVolume;

namespace B1
{

class event;

/// Stepping action class

class SteppingAction : public G4UserSteppingAction
{
  public:
    SteppingAction(event* eventAction);
    ~SteppingAction() override = default;

    // method from the base class
    void UserSteppingAction(const G4Step*) override;

  private:
    event* fEventAction = nullptr;
    G4LogicalVolume* fScoringVolume = nullptr;
};

}
