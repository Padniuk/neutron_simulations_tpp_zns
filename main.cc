#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "G4PhysListFactory.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

namespace {
  void PrintUsage() {
    G4cerr << " Usage: " << G4endl;
    G4cerr << " neutrons [-m macro ] [-p physList ] [-u UIsession]  [-t nThreads]" << G4endl;
    G4cerr << "   note: -t option is available only for multi-threaded mode." << G4endl;
    G4cerr << G4endl;
  }
}

int main(int argc,char** argv)
{
  if ( argc > 9 ) {
    PrintUsage();
    return 1;
  }
  
  G4String macro;
  G4String session;
  G4String physicsListName;
  G4int nofThreads = 0;
  for ( G4int i=1; i<argc; i=i+2 ) {
    if      ( G4String(argv[i]) == "-m" ) macro = argv[i+1];
    else if ( G4String(argv[i]) == "-u" ) session = argv[i+1];
    else if ( G4String(argv[i]) == "-p" ) physicsListName = argv[i+1];
#ifdef G4MULTITHREADED
    else if ( G4String(argv[i]) == "-t" ) {
      nofThreads = G4UIcommand::ConvertToInt(argv[i+1]);
    }
#endif
    else {
      PrintUsage();
      return 1;
    }
  }  

  G4UIExecutive* ui = 0;
  if ( ! macro.size() ) {
    ui = new G4UIExecutive(argc, argv, session);
  }

#ifdef G4MULTITHREADED
  G4MTRunManager * runManager = new G4MTRunManager;
  if ( nofThreads > 0 ) { 
    runManager->SetNumberOfThreads(nofThreads);
  }  
#else
  G4RunManager * runManager = new G4RunManager;
#endif

  runManager->SetUserInitialization(new DetectorConstruction());

  if ( physicsListName.size() == 0 ) physicsListName = "QGSP_BIC_HP";
  G4PhysListFactory physListFactory;
  if ( ! physListFactory.IsReferencePhysList(physicsListName)) {
    G4cerr << " Physics list " << physicsListName 
           << " is not defined." << G4endl;
    return 1;
  } 
  G4VModularPhysicsList* physicsList 
    = physListFactory.GetReferencePhysList(physicsListName);
  physicsList->SetVerboseLevel(1);
  runManager->SetUserInitialization(physicsList);
    
  runManager->SetUserInitialization(new ActionInitialization());

  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if ( macro.size() ) {
    G4String command = "/control/execute ";
    UImanager->ApplyCommand(command+macro);
  }
  else {
    UImanager->ApplyCommand("/control/execute init_vis.mac"); 
    ui->SessionStart();
    delete ui;
  }

  delete visManager;
  delete runManager;
}