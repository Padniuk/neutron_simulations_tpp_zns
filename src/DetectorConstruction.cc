#include "DetectorConstruction.hh"
#include "CrystalSD.hh"

#include "G4NistManager.hh"
#include "G4SDManager.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4ProductionCuts.hh"
#include "G4SystemOfUnits.hh"
#include "G4UserLimits.hh"

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction()
{ }

DetectorConstruction::~DetectorConstruction()
{ }

G4VPhysicalVolume* DetectorConstruction::Construct()
{  
  G4NistManager* nistManager = G4NistManager::Instance();

  G4Material* air = nistManager->FindOrBuildMaterial("G4_AIR");
  
  G4Element* H = new G4Element("Hydrogen", "H", 1., 1.008 * g / mole);
  G4Element* C = new G4Element("Carbon", "C", 6., 12.011 * g / mole);
  G4Element* N = new G4Element("Nitrogen", "N", 7., 14.007 * g / mole);
  G4Element* Pb = new G4Element("Lead", "Pb", 82., 207.2 * g / mole);
  G4Element* Br = new G4Element("Bromine", "Br", 35., 79.904 * g / mole);
  G4Element* P = new G4Element("Phosphorus", "P", 15, 30.97 * g/mole);
  G4Element* Mn = new G4Element("Manganese", "Mn", 25, 54.94 * g/mole);
  G4Element* I  = new G4Element("Iodine", "I", 53, 126.904 * g/mole);
  G4Element* Zn = new G4Element("Zinc", "Zn", 30, 65.38 * g/mole);
  G4Element* S = new G4Element("Sulfur", "S", 16, 32.06 * g/mole);
  G4Element* Cl = new G4Element("Chlorine", "Cl", 17, 35.45*g/mole);
  G4Element* Sb = new G4Element("Antimony", "Sb", 51, 121.76*g/mole);


  G4Material* PP = new G4Material("Polypropylene", 0.9 * g/cm3, 2);
  PP->AddElement(C, 3);
  PP->AddElement(H, 6);
  // G4Material* PP = nistManager->FindOrBuildMaterial("G4_POLYPROPYLENE");

  // Define ZnS
  G4Material* ZnS = new G4Material("ZnS", 4.1 * g/cm3, 2); // Approx density = 4.1 g/cm³
  ZnS->AddElement(Zn, 1);
  ZnS->AddElement(S, 1);
  
  // Define the composite material PP/ZnS:Cu (30% ZnS:Cu by weight)
  G4Material* PP_ZnS = new G4Material("PP_ZnS", 1.18 * g/cm3, 2); // Approx composite density
  PP_ZnS->AddMaterial(PP, 70 * perCent);  // 70% weight fraction
  PP_ZnS->AddMaterial(ZnS, 30 * perCent);  // 30% weight fraction

  G4double density_TPP2MnBr4 =  1.548 * g / cm3; // 1.548 for single crystal  # 1.32 for the film 
  G4Material* TPP2MnBr4 = new G4Material("TPP2MnBr4", density_TPP2MnBr4, 5);  // Adjust density
  TPP2MnBr4->AddElement(C, 48);
  TPP2MnBr4->AddElement(H, 40);
  TPP2MnBr4->AddElement(P, 2);
  TPP2MnBr4->AddElement(Mn, 1); // 1 Manganese atom
  TPP2MnBr4->AddElement(Br, 4); // 4 Bromine atoms

  G4double density_MAPbBr3 = 3.83 * g / cm3;
  G4Material* MAPbBr3 = new G4Material("MAPbBr3", density_MAPbBr3, 5);
  MAPbBr3->AddElement(C, 1);   // 1 Carbon atom
  MAPbBr3->AddElement(H, 3);   // 3 Hydrogen atoms
  MAPbBr3->AddElement(N, 1);   // 1 Nitrogen atom
  MAPbBr3->AddElement(Pb, 1);  // 1 Lead atom
  MAPbBr3->AddElement(Br, 3);  // 3 Bromine atoms

  G4double density_MAFAPbI3=  3.9 * g / cm3;
  G4Material* MA_FA_PbI3 = new G4Material("MA_0.5FA_0.5PbI3", density_MAFAPbI3, 5);  // Density is approximate

  // Methylammonium (CH3NH3) and Formamidinium (CH3NH2) are combined in a 50/50 ratio
  MA_FA_PbI3->AddElement(C, 1);  // 1 Carbon from CH3NH3 and CH3NH2
  MA_FA_PbI3->AddElement(H, 3);  // 3 Hydrogens from CH3NH3 and CH3NH2
  MA_FA_PbI3->AddElement(N, 1);  // 1 Nitrogen from CH3NH3 and CH3NH2
  MA_FA_PbI3->AddElement(Pb, 1); // 1 Lead
  MA_FA_PbI3->AddElement(I, 3);  // 3 Iodines

  G4double density_Si = 2.33 * g / cm3;
  G4Material* Si = new G4Material("Silicon", density_Si, 1);
  Si->AddElement(nistManager->FindOrBuildElement("Si"), 1);
  

  G4double density_Gua3SbCl6 = 1.468*g/cm3;
  G4Material* Gua3SbCl6 = new G4Material("Gua3SbCl6", density_Gua3SbCl6, 5);

  // Add elements with their fractional number of atoms
  Gua3SbCl6->AddElement(C, 39);
  Gua3SbCl6->AddElement(H, 42);
  Gua3SbCl6->AddElement(Cl, 6);
  Gua3SbCl6->AddElement(N, 9);
  Gua3SbCl6->AddElement(Sb, 1);

  G4bool checkOverlaps = true;

  G4double hx = 1*cm;
  G4double hy = 1*cm;
  G4double hz = 1*cm;

  G4double d = 5000*um;

  G4Material* lead = nistManager->FindOrBuildMaterial("G4_Pb");

  
  G4Material* crystal_material = PP_ZnS; //Gua3SbCl6; // PP_ZnS;// TPP2MnBr4  

  G4double density_plastic = 1.18 * g / cm3;
  G4Material* plastic = new G4Material("Plastic", density_plastic, 2);
  plastic->AddElement(C, 1);
  plastic->AddElement(H, 2);

  G4cout << *(G4Material::GetMaterialTable()) << G4endl;

  G4Box* worldS = new G4Box("World", hx, hy, hz); 
      
  G4LogicalVolume* worldLV                         
    = new G4LogicalVolume(worldS, air, "World");
                       
  G4VPhysicalVolume* worldPV
    = new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      worldLV,               //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking

  
  hz = 0.5*d;
  
  G4VSolid* crystalS = new G4Box("Crystal", hx, hy, hz);
  
  G4LogicalVolume* crystalLV
    = new G4LogicalVolume(crystalS, crystal_material, "Crystal");
 
  new G4PVPlacement(0, 
                    G4ThreeVector(),       //at (0,0,0)
                    crystalLV,             //its logical volume
                    "Tube",                //its name
                    worldLV,               //its mother  volume
                    false,                 //no boolean operation
                    0,                     //copy number
                    checkOverlaps);        //overlaps checking

  // hz=5*cm;

  // G4VSolid* shieldingS = new G4Box("Shielding", hx, hy, hz);
  
  // G4LogicalVolume* shieldingLV
  //   = new G4LogicalVolume(shieldingS, lead, "Shielding");

  // new G4PVPlacement(0, 
  //                   G4ThreeVector(0, 0, -7*cm),       //at (0,0,0)
  //                   shieldingLV,             //its logical volume
  //                   "Shielding",                //its name
  //                   worldLV,               //its mother  volume
  //                   false,                 //no boolean operation
  //                   0,                     //copy number
  //                   checkOverlaps);        //overlaps checking  

  // G4VSolid* plasticS = new G4Box("Plastic", hx, hy, hz);

  // G4LogicalVolume* plasticLV
  //   = new G4LogicalVolume(plasticS, plastic, "Plastic");
  
  // new G4PVPlacement(0, 
  //                   G4ThreeVector(0, 0, -19*cm),       //at (0,0,0)
  //                   plasticLV,             //its logical volume
  //                   "Plastic",                //its name
  //                   worldLV,               //its mother  volume
  //                   false,                 //no boolean operation
  //                   0,                     //copy number
  //                   checkOverlaps);        //overlaps checking

  G4Region* CrystalRegion = new G4Region("CrystalRegion");
  crystalLV->SetRegion(CrystalRegion);
  CrystalRegion->AddRootLogicalVolume(crystalLV);

  G4ProductionCuts* cuts = new G4ProductionCuts() ;
  cuts->SetProductionCut(1*um, "gamma");
  cuts->SetProductionCut(1*um, "e-");
  cuts->SetProductionCut(1*um, "e+");
  CrystalRegion->SetProductionCuts(cuts);

  G4double stepMax = 1 * mm;
  G4UserLimits* stepLimit = new G4UserLimits(stepMax);
  CrystalRegion->SetUserLimits(stepLimit);

  return worldPV;
}

void DetectorConstruction::ConstructSDandField()
{
  CrystalSD* crystalSD = new CrystalSD("CrystalSD", "CrystalHitsCollection");
  G4SDManager::GetSDMpointer()->AddNewDetector(crystalSD);
  SetSensitiveDetector("Crystal", crystalSD);
}  
