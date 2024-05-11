#pragma once

#include "G4UserEventAction.hh"
#include "globals.hh"

namespace B1
{

class RunAction;

/// Event action class

class event: public G4UserEventAction {
    
    public: event(RunAction* runAction);
    public: ~event() override = default;

    public: void BeginOfEventAction(const G4Event* event) override {
        _edep = 0.0;
    }
    
    public: void EndOfEventAction(const G4Event* event) override;

    public: void AddEdep(const double edep) {
        _edep += edep;
    }

    private: RunAction* _run  = nullptr;
    private: double     _edep = 0.0;
};

}
