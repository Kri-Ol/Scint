
#include "init.hh"
#include "source.hh"
#include "running.hh"
#include "event.hh"
#include "stepping.hh"

namespace B1 {

void init::BuildForMaster() const {
    auto run = new running();
    SetUserAction(run);
}

void init::Build() const {
    SetUserAction(new source);

    auto run = new running();
    SetUserAction(run);

    auto evt = new event(run);
    SetUserAction(evt);

    SetUserAction(new stepping(evt));
}

}
