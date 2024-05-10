
#include "event.hh"
#include "RunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

namespace B1
{

event::event(RunAction* runAction):
    fRunAction(runAction)
{
}

void event::BeginOfEventAction(const G4Event*)
{
    fEdep = 0.0;
}

void event::EndOfEventAction(const G4Event*)
{
    // accumulate statistics in run action
    fRunAction->AddEdep(fEdep);
}

}
