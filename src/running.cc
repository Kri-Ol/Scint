#include <string>

#include "running.hh"
#include "source.hh"
#include "detector.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

namespace B1 {

running::running() {
    
    // add new units for dose
    const G4double milligray = 1.e-3*gray;
    const G4double microgray = 1.e-6*gray;
    const G4double nanogray  = 1.e-9*gray;
    const G4double picogray  = 1.e-12*gray;

    new G4UnitDefinition("milligray", "milliGy" , "Dose", milligray);
    new G4UnitDefinition("microgray", "microGy" , "Dose", microgray);
    new G4UnitDefinition("nanogray" , "nanoGy"  , "Dose", nanogray);
    new G4UnitDefinition("picogray" , "picoGy"  , "Dose", picogray);

    // Register accumulable to the accumulable manager
    G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->RegisterAccumulable(_edep);
    accumulableManager->RegisterAccumulable(_edep2);
}


void running::BeginOfRunAction(const G4Run*) {
    // inform the runManager to save random number seed
    G4RunManager::GetRunManager()->SetRandomNumberStore(false);

    // reset accumulables to their initial values
    G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->Reset();
}


void running::EndOfRunAction(const G4Run* run) {
    int nofEvents = run->GetNumberOfEvent();
    if (nofEvents == 0)
        return;

    // Merge accumulables
    G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->Merge();

    // Compute dose = total energy deposit in a run and its variance
    double edep  = _edep.GetValue();
    double edep2 = _edep2.GetValue();

    double rms = edep2 - edep*edep/nofEvents;
    rms =  (rms > 0.) ? std::sqrt(rms) : 0.0;

    const auto det = static_cast<const detector*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    double mass    = det->GetScoringVolume()->GetMass();
    double dose    = edep/mass;
    double rmsDose = rms/mass;

    // Run conditions
    //  note: There is no primary generator action object for "master"
    //        run manager for multi-threaded mode.
    const auto generatorAction = static_cast<const source*>(G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
    std::string runCondition;
    if (generatorAction) {
        const G4ParticleGun* particleGun = generatorAction->GetParticleGun();
        runCondition += particleGun->GetParticleDefinition()->GetParticleName();
        runCondition += " of ";
        double particleEnergy = particleGun->GetParticleEnergy();
        runCondition += G4BestUnit(particleEnergy,"Energy");
    }

    // Print
    if (IsMaster()) {
        G4cout << G4endl
        << "--------------------End of Global Run-----------------------";
    } else {
        G4cout << G4endl << "--------------------End of Local Run------------------------";
    }

    G4cout << G4endl
        << " The run consists of " << nofEvents << " "<< runCondition
        << G4endl
        << " Cumulated dose per run, in scoring volume : "
        << G4BestUnit(dose,"Dose") << " rms = " << G4BestUnit(rmsDose,"Dose")
        << G4endl
        << "------------------------------------------------------------"
        << G4endl
        << G4endl;
}

void running::AddEdep(const double edep) {
    _edep  += edep;
    _edep2 += edep*edep;
}

}
