#ifndef CrystalSD_h
#define CrystalSD_h 1

#include "G4VSensitiveDetector.hh"
#include "CrystalHit.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class CrystalSD : public G4VSensitiveDetector
{
  public:
    CrystalSD(const G4String& name, 
                  const G4String& hitsCollectionName);
    virtual ~CrystalSD();

    virtual void   Initialize(G4HCofThisEvent* hce);
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
    virtual void   EndOfEvent(G4HCofThisEvent* hce);

  private:
    CrystalHitsCollection* fHitsCollection;
};

#endif