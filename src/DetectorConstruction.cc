#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4VisAttributes.hh"

DetectorConstruction::DetectorConstruction():G4VUserDetectorConstruction(),
fScoringVolume(0)
{}

DetectorConstruction::~DetectorConstruction()
{}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Materials ----------------------------------------------------------------
  G4NistManager* NIST_Manager = G4NistManager::Instance();

  // Def Hydrogen, low-density gas as vacuum
  G4Material* vacuum = new G4Material(
    "Vacuum",                           // name
    1.,                                 // z
    1.01*g/mole,                        // a
    universe_mean_density,              // density
    kStateGas,                          // state
    0.1*kelvin,                         // temperature
    1.e-19*pascal                       // pressure
  );

  // Def Deuterium Isotope as Element
  G4Isotope* isoD = new G4Isotope(
    "Deuterium (Isotope)",              // name
    1,                                  // n protons
    2,                                  // z
    2.014*g/mole                        // a
  );
  G4Element* elD = new G4Element(
    "Deuterium",                        // name
    "D",                                // symbol
    1                                   // parts
  );
  elD->AddIsotope(isoD, 1*perCent);     // (isotope, ratio)

  // Def Oxygen
  G4Element* elO = new G4Element(
    "Oxygen",                           // name
    "O",                                // symbol
    8.,                                 // z
    16.00*g/mole                        // a
  );

  // Def Heavy Water
  G4Material* D2O = new G4Material(
    "Heavy Water",                      // name
    1.11*g/cm3,                         // density
    2                                   // parts
  );
  D2O->AddElement(elD,2);               // (element, n atoms)
  D2O->AddElement(elO,1);               // (element, n atoms)

  // World --------------------------------------------------------------------
  G4double world_size_XY = 10*cm;
  G4double world_size_Z = 200*cm;

  G4Material* world_material = vacuum;

  // Def size of Chamber
  G4Box* solid_world = new G4Box(
    "Chamber",                          // name
    0.5*world_size_XY,                  // x length
    0.5*world_size_XY,                  // y length
    0.5*world_size_Z,                   // z length
  );

  // Def logic for Chamber
  G4LogicalVolume* logic_world = new G4LogicalVolume(
    solid_world,                        // solid instance
    world_material,
    "Chamber"
  );
}
