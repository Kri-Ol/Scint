
#include "stepping.hh"
#include "event.hh"
#include "detector.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

namespace B1
{

stepping::stepping(event* eventAction):
    _event_action(eventAction) {

}

void stepping::UserSteppingAction(const G4Step* step) {
    if (!_scoring_volume) { // 
        const auto detConstruction = static_cast<const detector*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
        _scoring_volume = detConstruction->GetScoringVolume();
    }

    // get volume of the current step
    G4LogicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

    // check if we are in scoring volume
    if (volume != _scoring_volume)
        return;

    // collect energy deposited in this step
    double edep_step = step->GetTotalEnergyDeposit();
    _event_action->AddEdep(edep_step);
}

}
