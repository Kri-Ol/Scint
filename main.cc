#include "detector.hh"
#include "init.hh"

#include "G4RunManagerFactory.hh"
#include "G4SteppingVerbose.hh"
#include "G4UImanager.hh"
#include "QBBC.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "Randomize.hh"

#define func auto

using namespace B1;

func main(int argc,char* argv[]) -> int {
    // Detect interactive mode (if no arguments) and define UI session
    G4UIExecutive* ui = ( argc == 1 ) ? new G4UIExecutive(argc, argv) : nullptr;

    // Optionally: choose a different Random engine...
    // G4Random::setTheEngine(new CLHEP::MTwistEngine);

    //use G4SteppingVerboseWithUnits
    int precision = 4;
    G4SteppingVerbose::UseBestUnit(precision);

    // Construct the default run manager
    auto* runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);

    // Set mandatory initialization classes
    //
    // Detector construction
    runManager->SetUserInitialization(new detector());

    // Physics list
    auto physicsList = new QBBC;
    physicsList->SetVerboseLevel(1);
    runManager->SetUserInitialization(physicsList);

    // User action initialization
    runManager->SetUserInitialization(new init());

    // Initialize visualization with the default graphics system
    auto* visManager = new G4VisExecutive(argc, argv);
    // Constructors can also take optional arguments:
    // - a graphics system of choice, eg. "OGL"
    // - and a verbosity argument - see /vis/verbose guidance.
    // auto visManager = new G4VisExecutive(argc, argv, "OGL", "Quiet");
    // auto visManager = new G4VisExecutive("Quiet");
    visManager->Initialize();

    // Get the pointer to the User Interface manager
    auto* UImanager = G4UImanager::GetUIpointer();

    // Process macro or start UI session
    if ( ! ui ) {
        // batch mode
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command+fileName);
    } else {
        // interactive mode
        UImanager->ApplyCommand("/control/execute init_vis.mac");
        ui->SessionStart();
        delete ui;
    }

    // Job termination
    // Free the store: user actions, physics_list and detector_description are
    // owned and deleted by the run manager, so they should not be deleted
    // in the main() program !

    delete visManager;
    delete runManager;
    
    return 0;
}
