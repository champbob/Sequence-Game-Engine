#ifndef _PHYSCONTROLLER
#define _PHYSCONTROLLER
#include "ControllerObject.h"

class PhysController: public ControllerObject
{
public:
  struct PhysControlState
  {
    float drag;
    float mass;
    float gravityScale;
  };
  
private:
  PhysController();
  
  vector<PhysControlState> controlStates;
  short int currentState;
  
public:
  PhysController(SpriteObject* targetSprite);
  //"default" constructor. This will initialize the controller with two states containing all 0's.

  PhysController(SpriteObject* targetSprite, PhysControlState state);
  //This constructor will initialize the controller with the current state being set as the given state.
  //The temp state will be initialized to all 0's.
  
  const PhysControlState GetActiveState();
  //Returns currently used control state.
  //Pre: 
  //Post:
  
  const int GetActiveStateNum();
  //Returns currently used control state's internal index number. 
  //Pre: 
  //Post: Returns currentState. Returns -1 if currentState is invalid.
  
  void AddState(PhysControlState newState);
  //Adds a state to the controlStates. Intended to be used while
  //setting up the controller.
  //Pre: 
  //Post: newState is added at the end of controlStates
  
  void TempState(PhysControlState newState);
  //Sets new tempstate
  //Pre: 
  //Post: newState is set into controlStates[0]
  
  bool ReplaceState(int stateNumToReplace, PhysControlState newState);
  //Replaces a state with the new provided state.
  //Pre: stateNumToReplace exists and is within bounds of controlStates
  //Post: Specified state is replaced with new state. Returns true if success.
  
  bool DeleteState(int stateNum);
  //Deletes specified state in stateNum. All states after the specified number get moved
  //down one number (eg, if I delete 3, 4 becomes 3)
  //Pre: stateNum exists in controlStates
  //Post: State is deleted. Returns true on success, false otherwise.
  
  bool SetState(short int stateNum);
  //Sets current active state
  //Pre: 
  //Post: returns true if stateNum was a valid state, else returns false
  
  virtual void ApplyXForce(float force);
  virtual void ApplyYForce(float force);
  virtual void NoInput(float force);
  //All three functions above represent movement controls. Scale represents intensity of controls.
  //Scale will not effect SpeedMod effects, but will change maxSpeed and accelleration effects.
  //Pre: 
  //Post: Position changed accordingly. 
};

#endif