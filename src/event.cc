
#include "event.hh"
#include "running.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

namespace B1
{

event::event(running* runAction):
    _run(runAction) {
}

void event::EndOfEventAction(const G4Event*) {
    // accumulate statistics in run action
    _run->AddEdep(_edep);
}

}
