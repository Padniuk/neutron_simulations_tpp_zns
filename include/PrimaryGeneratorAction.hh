#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"

class G4GeneralParticleSource;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
 public:
   explicit PrimaryGeneratorAction();
   ~PrimaryGeneratorAction();

 public:
  void GeneratePrimaries(G4Event* anEvent) override;

 private:
  G4GeneralParticleSource* fGun;
};
#endif

