#include "RunAction.hh"
#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4SystemOfUnits.hh"

RunAction::RunAction()
: G4UserRunAction()
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetVerboseLevel(1);
  G4cout << "Using " << analysisManager->GetType() 
         << " analysis manager" << G4endl;
  analysisManager->SetNtupleMerging(true);

  analysisManager->CreateH1("Spectrum", "Initial Spectrum", 100, 0., 20);
  analysisManager->CreateH1("Bragg peak", "Bragg peaks", 1000, 0., 200);
  analysisManager->CreateNtuple("Crystal", "Crystal hits");
  analysisManager->CreateNtupleDColumn("Edep"); // column id = 0 
  analysisManager->CreateNtupleDColumn("Xpos");    // column id = 1 
  analysisManager->CreateNtupleDColumn("Ypos");    // column id = 2
  analysisManager->CreateNtupleDColumn("Zpos");    // column id = 3
  analysisManager->CreateNtupleDColumn("Time");    // column id = 4
  analysisManager->CreateNtupleDColumn("EventID");    // column id = 5
  analysisManager->CreateNtupleIColumn("ParticleID"); // column id = 6
  analysisManager->CreateNtupleIColumn("TrackID"); // column id = 7
  analysisManager->CreateNtupleIColumn("ParentID");   // column id = 8
  analysisManager->CreateNtupleDColumn("PrimaryEnergy");    // column id = 9
  
  analysisManager->FinishNtuple();

  analysisManager->CreateNtuple("Beam", "Beam data");
  analysisManager->CreateNtupleDColumn("Energy"); // column id = 0  
  analysisManager->CreateNtupleIColumn("EventID"); // column id = 1 
  analysisManager->CreateNtupleDColumn("Interucted"); // column id = 2  
  analysisManager->FinishNtuple();
}

RunAction::~RunAction()
{
  delete G4AnalysisManager::Instance();  
}

void RunAction::BeginOfRunAction(const G4Run* /*run*/)
{ 
  G4String fileName = "Output.root";
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->OpenFile(fileName);
}

void RunAction::EndOfRunAction(const G4Run* /*run*/)
{  
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
}