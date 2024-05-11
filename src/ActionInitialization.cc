
#include "ActionInitialization.hh"
#include "source.hh"
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
    SetUserAction(new source);

    auto runAction = new RunAction;
    SetUserAction(runAction);

    auto evt = new event(runAction);
    SetUserAction(evt);

    SetUserAction(new SteppingAction(evt));
}

}
