#include "CrystalHit.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

G4ThreadLocal G4Allocator<CrystalHit>* CrystalHitAllocator = 0;

CrystalHit::CrystalHit()
  : G4VHit(),
    fTime(0.),
    fPosition(),
    fEdep(0.),
    fTotalEdep(0.),
    fParticleID(0),
    fPostPosition()
{}

CrystalHit::~CrystalHit()
{}

CrystalHit::CrystalHit(const CrystalHit& /*right*/)
  : G4VHit() 
{}

const CrystalHit& CrystalHit::operator=(const CrystalHit& /*right*/)
{
  return *this;
}

int CrystalHit::operator==(const CrystalHit& /*right*/) const
{
  return 0;
}

void CrystalHit::Print()
{
  // if ( fEdep > 0. ) {
  //   G4cout << "Edep: " << std::setw(7) << G4BestUnit(fEdep, "Energy") << G4endl
  //          << "   time [s]: " << fTime / s 
  //          << "   position [mm]: " << fPosition / mm << G4endl;
  // }          
}

