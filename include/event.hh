#pragma once

#include "G4UserEventAction.hh"
#include "globals.hh"

namespace B1
{

class RunAction;

/// Event action class

class event: public G4UserEventAction
{
  public:
    event(RunAction* runAction);
    ~event() override = default;

    void BeginOfEventAction(const G4Event* event) override;
    void EndOfEventAction(const G4Event* event) override;

    void AddEdep(const double edep) {
      fEdep += edep;
    }

  private:
      RunAction* fRunAction = nullptr;
      double     fEdep      = 0.;
};

}
