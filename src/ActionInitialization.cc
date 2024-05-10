
#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "event.hh"
#include "SteppingAction.hh"

namespace B1
{

void ActionInitialization::BuildForMaster() const
{
    auto runAction = new RunAction();
    SetUserAction(runAction);
}

void ActionInitialization::Build() const
{
    SetUserAction(new PrimaryGeneratorAction);

    auto runAction = new RunAction;
    SetUserAction(runAction);

    auto evt = new event(runAction);
    SetUserAction(evt);

    SetUserAction(new SteppingAction(evt));
}

}
