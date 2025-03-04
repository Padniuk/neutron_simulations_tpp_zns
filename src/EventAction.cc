#include "EventAction.hh"

#include "G4Event.hh"
#include "G4GenericMessenger.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction()
 : G4UserEventAction(),
   fVerbose(false)
{
  // Generic messenger
  // Define /ED/event commands using generic messenger class
  fMessenger 
    = new G4GenericMessenger(this, "/ED/event/", "Primary generator control");

  // Define /ED/event/setVerbose command
  fMessenger
    ->DeclareProperty("setVerbose", 
                      fVerbose, 
                      "Activate/Inactivate verbose option");
  
}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event* event)
{
  if ( fVerbose ) {
    G4cout << ">>> Start event: " << event->GetEventID() << G4endl;
  }  
}

void EventAction::EndOfEventAction(const G4Event* event)
{
  if ( fVerbose ) {
    G4cout << ">>> End event: " << event->GetEventID() << G4endl;
  }  
}    
