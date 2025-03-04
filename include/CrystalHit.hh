#ifndef CrystalHit_h
#define CrystalHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class CrystalHit : public G4VHit
{
    public:
        CrystalHit();
        virtual ~CrystalHit();
        CrystalHit(const CrystalHit& right);
        const CrystalHit& operator=(const CrystalHit& right);
        int operator==(const CrystalHit &right) const;

        inline void* operator new(size_t);
        inline void  operator delete(void* hit);

        virtual void Print();

        void SetTime(G4double time)       { fTime = time; }
        void SetPosition(G4ThreeVector position) { fPosition = position; }
        void AddEdep(G4double edep)       { fTotalEdep += edep; }
        void SetEdep(G4double edep)       { fEdep = edep; }
        void SetParticleID(G4int particleID) { fParticleID = particleID; }
        void SetPostPosition(G4ThreeVector postPosition) { fPostPosition = postPosition; }

        G4double       GetTime() const        { return fTime; }
        G4ThreeVector  GetPosition() const    { return fPosition; }
        G4double       GetEdep() const        { return fEdep; }
        G4double       GetTotalEdep() const   { return fTotalEdep; }
        G4int          GetParticleID() const  { return fParticleID; }
        G4ThreeVector  GetPostPosition() const    { return fPostPosition; }
    

    private:
        G4double       fTime;
        G4ThreeVector  fPosition;
        G4double       fTotalEdep;
        G4double       fEdep;
        G4int          fParticleID;
        G4ThreeVector  fPostPosition;
};

typedef G4THitsCollection<CrystalHit> CrystalHitsCollection;

extern G4ThreadLocal G4Allocator<CrystalHit>* CrystalHitAllocator;

inline void* CrystalHit::operator new(size_t)
{
  if (! CrystalHitAllocator)
        CrystalHitAllocator = new G4Allocator<CrystalHit>;
  return (void*)CrystalHitAllocator->MallocSingle();
}

inline void CrystalHit::operator delete(void* hit)
{
  CrystalHitAllocator->FreeSingle((CrystalHit*) hit);
}

#endif