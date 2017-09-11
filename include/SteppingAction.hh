#ifndef Steppingaction_h
#define Steppingaction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class EventAction;

class G4LogicalVolume;

class SteppingAction : public G4UserSteppingAction
{
public:
    SteppingAction(EventAction* eventAction);
    virtual ~SteppingAction();

    // method from user base class
    virtual void UserSteppingAction(const G4Step*);

private: 
    EventAction* fEventAction;
    G4LogicalVolume* fScoringVolume;
    G4String* particle_name;
    G4String* process_name;
    G4bool*   in_det;
    G4int*    track_ID;
    G4double* kinetic_energy;
    G4double* x_pos;
    G4double* y_pos;
    G4double* z_pos;
};

#endif