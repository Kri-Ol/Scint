#pragma once

#include "G4VUserActionInitialization.hh"

namespace B1

{

/// Action initialization class.

class init : public G4VUserActionInitialization {
    
    public: init() = default;
    public: ~init() override = default;

    public: void BuildForMaster() const override;
    public: void Build() const override;
};

}
