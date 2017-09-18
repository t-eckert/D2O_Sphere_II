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

// extern G4double data[8][5000];
// G4int i = 0;

SteppingAction::SteppingAction(EventAction* eventAction):
G4UserSteppingAction(),
fEventAction(eventAction),
fScoringVolume(0)
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

    
    // Point to the track
    G4Track* track = step->GetTrack();

    // Get the name of the particle
    G4String particle_name = track->GetDefinition()->GetParticleName();

    if(particle_name == "neutron"){
        // Get volume of the current step and check if we are in the scoring volume
        G4LogicalVolume* volume
        = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

        if(volume==fScoringVolume){
            G4String tag = "null";
            //G4String process_name = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
            G4int trackID = track->GetTrackID();
            G4int n_secondaries = step->GetNumberOfSecondariesInCurrentStep();
            G4double kinetic_energy = track->GetKineticEnergy();
            G4ThreeVector position = track->GetPosition();
            G4double x_pos = position.x();
            G4double y_pos = position.y();
            G4double z_pos = position.z();

            if(trackID==1){tag="no interaction";}
            if(n_secondaries==3){tag="breakup neutron";}
            // if(n_secondaries==)

            G4cout  << kinetic_energy << ", "
                    << x_pos << ", "
                    << y_pos << ", "
                    << z_pos << ", "
                    << tag << G4endl;
        };
    }
}
