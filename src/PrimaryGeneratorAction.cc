#include "globals.hh"

#include "PrimaryGeneratorAction.hh"
#include "Randomize.hh"  
#include "G4AnalysisManager.hh"
#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
 fGun = new G4GeneralParticleSource();
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
delete fGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
 fGun -> GeneratePrimaryVertex(anEvent);

 if (fGun -> GetParticleDefinition()-> GetParticleName()== "neutron")
 { 
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  G4double energy = fGun -> GetParticleEnergy();
  analysisManager -> FillH1(0, energy/MeV);
  analysisManager->FillNtupleDColumn(1,0, energy/MeV);
  analysisManager->FillNtupleIColumn(1,1, anEvent->GetEventID());
  analysisManager->AddNtupleRow(1);
 }
}