#pragma once

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class G4LogicalVolume;

namespace B1
{

class event;

/// Stepping action class

class stepping : public G4UserSteppingAction
{
    public: stepping(event* eventAction);
    public: ~stepping() override = default;

    public: void UserSteppingAction(const G4Step*) override;

    private: event* _event_action = nullptr;

    private: G4LogicalVolume* _scoring_volume = nullptr;
};

}
