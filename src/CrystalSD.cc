#include "CrystalSD.hh"
#include "G4SDManager.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

CrystalSD::CrystalSD(const G4String &name,
                     const G4String &hitsCollectionName)
    : G4VSensitiveDetector(name),
      fHitsCollection(0)
{
  collectionName.insert(hitsCollectionName);
}

CrystalSD::~CrystalSD()
{

}

void CrystalSD::Initialize(G4HCofThisEvent *hce)
{
  fHitsCollection = new CrystalHitsCollection(SensitiveDetectorName, collectionName[0]);

  G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection(hcID, fHitsCollection);
}

G4bool CrystalSD::ProcessHits(G4Step *step,
                              G4TouchableHistory * /*history*/)
{
  G4double edep = step->GetTotalEnergyDeposit();

  G4int trackID = step->GetTrack()->GetTrackID();
  G4int particleID = step->GetTrack()->GetParticleDefinition()->GetPDGEncoding();
  G4int parentID = step->GetTrack()->GetParentID();

  G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

  if(particleID == 2112 && parentID == 0) {
    analysisManager->FillNtupleDColumn(1, 2, 1);
  }
  
  if (edep == 0.)
    return false;

  CrystalHit *newHit = new CrystalHit();

  G4StepPoint *preStepPoint = step->GetPreStepPoint();

  G4double time = preStepPoint->GetGlobalTime();
  newHit->SetTime(time);

   G4ThreeVector position = preStepPoint->GetPosition();
  newHit->SetPosition(position);
  newHit->AddEdep(edep);
  newHit->SetParticleID(particleID);
  newHit->SetEdep(edep);
  newHit->SetPostPosition(step->GetPostStepPoint()->GetPosition());
  fHitsCollection->insert(newHit);
  
  const G4Event* event = G4RunManager::GetRunManager()->GetCurrentEvent();
  const G4PrimaryVertex* primaryVertex = event->GetPrimaryVertex();
  const G4PrimaryParticle* primaryParticle = primaryVertex->GetPrimary();
  G4double primaryEnergy = primaryParticle->GetKineticEnergy();

  G4int eventId = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
  
  // G4cout<<eventId<<"  "<<edep<<"  "<<primaryEnergy<<G4endl;
  analysisManager->FillNtupleDColumn(0, 0, edep / MeV);
  analysisManager->FillNtupleDColumn(0, 1, position.x()/um);
  analysisManager->FillNtupleDColumn(0, 2, position.y()/um);
  analysisManager->FillNtupleDColumn(0, 3, position.z()/um);
  analysisManager->FillNtupleDColumn(0, 4, time);
  analysisManager->FillNtupleDColumn(0, 5, eventId);
  analysisManager->FillNtupleIColumn(0, 6, particleID);
  analysisManager->FillNtupleIColumn(0, 7, trackID);
  analysisManager->FillNtupleIColumn(0, 8, parentID);
  analysisManager->FillNtupleDColumn(0, 9, primaryEnergy / MeV);
  analysisManager->AddNtupleRow(0);

  return true;
}

void CrystalSD::EndOfEvent(G4HCofThisEvent * /*hce*/)
{
  G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
  G4int nofHits = fHitsCollection->entries();
  for (G4int i = 0; i < nofHits; i++) {
      CrystalHit* hit = (*fHitsCollection)[i];

      if (hit->GetParticleID() == 2212) {
        G4ThreeVector position = hit->GetPosition();
        G4ThreeVector postPosition = hit->GetPostPosition();

        G4double zmax = -2500*um;
        G4double z1 = position.z();
        G4double z2 = postPosition.z();
        G4double edep = hit->GetEdep();
        G4double zPosition = G4UniformRand()*(z2-z1) + z1 - zmax;
        analysisManager->FillH1(1, zPosition/um, edep / MeV); 
      }   
  }  
}
