#include "EventAction.hh"
#include "RunAction.hh"
#include "Analysis.hh"
#include "SteppingAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
    
EventAction::EventAction(RunAction* runAction):
G4UserEventAction(),
fRunAction(runAction)
{}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event*)
{}

void EventAction::EndOfEventAction(const G4Event*)
{
    //G4cout << particle_name << G4endl;
}    