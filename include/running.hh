#pragma once

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "globals.hh"

class G4Run;

namespace B1 {

/// Run action class
///
/// In EndOfRunAction(), it calculates the dose in the selected volume
/// from the energy deposit accumulated via stepping and event actions.
/// The computed dose is then printed on the screen.

class running : public G4UserRunAction {
    public: running();
    public: ~running() override = default;

    public: void BeginOfRunAction(const G4Run*) override;
    public: void   EndOfRunAction(const G4Run*) override;

    public: void AddEdep(const double edep);

    private: G4Accumulable<double> _edep  = 0.0;
    private: G4Accumulable<double> _edep2 = 0.0;
};

}
