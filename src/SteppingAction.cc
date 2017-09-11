#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"
#include "Analysis.hh"

#include "G4UIcommand.hh"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4VProcess.hh"
#include "G4Track.hh"

SteppingAction::SteppingAction(EventAction* eventAction):
G4UserSteppingAction(),
fEventAction(eventAction),
fScoringVolume(0),
particle_name(0),
process_name(0),
in_det(0),
track_ID(0),
kinetic_energy(0),
x_pos(0),
y_pos(0),
z_pos(0)
{}

SteppingAction::~SteppingAction()
{}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
    // Get the scoring volume
    if(!fScoringVolume)
    {
        const DetectorConstruction* detectorConstruction
        = static_cast<const DetectorConstruction*> 
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
        fScoringVolume = detectorConstruction->GetScoringVolume();
    }

    // Get volume of the current step
    G4LogicalVolume* volume
    = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

    // Check if we are in the scoring volume
    G4bool in_det = false;
    if(volume==fScoringVolume) in_det = true;

    // Get the name of the process in the step
    G4String process_name = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();

    // Point to the track
    G4Track* track = step->GetTrack();

    // Get the name of the particle
    G4String particle_name = track->GetDefinition()->GetParticleName();

    // Get the ID of the track and convert type to G4double
    G4int trackID = track->GetTrackID();

    // Get the kinetic energy
    G4double kinetic_energy = track->GetKineticEnergy();

    // Get the position of the particle and separate it into x,y,z
    G4ThreeVector position = track->GetPosition();
    G4double x_pos = position.x();
    G4double y_pos = position.y();
    G4double z_pos = position.z();
}