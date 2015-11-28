#ifndef _SIMPLECONTROLLER
#define _SIMPLECONTROLLER
#include "ControllerObject.h"

/* This is SimpleController. This controller acts like a top-down control method. */

class SimpleController: public ControllerObject
{
public:
  struct SimpleControlState
  {
    float xMaxSpeed;		//Max absolute speed in the X axis
    float yMaxSpeed;		//Max absolute speed in the X axis
    float xAccel;		//Acceleration on X axis when moving
    float yAccel;		//Acceleration on Y axis when moving
    float xSpeedMod;		//const speed always applied. (like for wind)
    float ySpeedMod;		//const speed always applied. (like for wind)
  };
private:
  SimpleController();
  
  vector<SimpleControlState> controlStates;	//stores different control states. Two reserved indexes:
						//DEFAULT: [1] -- TEMP: [0]
  short int currentState;			//which controlstate is the current?

public:
  SimpleController(SpriteObject* targetSprite);
  //"default" constructor. This will initialize the controller with two states containing all 0's.
  
  SimpleController(SpriteObject* targetSprite, SimpleControlState state);
  //This constructor will initialize the controller with the current state being set as the given state.
  //The temp state will be initialized to all 0's.
  
  const SimpleControlState GetActiveState();
  //Returns currently used control state.
  //Pre: 
  //Post: 
  
  const int GetActiveStateNum();
  //Returns currently used control state's internal index number. 
  //Pre: 
  //Post: Returns currentState
  
  void AddState(SimpleControlState newState);
  //Adds a state to the controlStates. Intended to be used while
  //setting up the controller.
  //Pre: 
  //Post: newState is added at the end of controlStates
  
  void TempState(SimpleControlState newState);
  //Sets new tempstate
  //Pre: 
  //Post: newState is set into controlStates[0]
  
  bool ReplaceState(int stateNumToReplace, SimpleControlState newState);
  //Replaces a state with the new provided state.
  //Pre: stateNumToReplace exists and is within bounds of controlStates
  //Post: Specified state is replaced with new state. Returns true if success.
  
  bool DeleteState(int stateNum);
  //Deletes specified state in stateNum. All states after the specified number get moved
  //down one number (eg, if I delete 3, 4 becomes 3)
  //Pre: stateNum exists in controlStates
  //Post: State is deleted. Returns true on success, false otherwise.
    
  bool SetState(int stateNum);
  //Sets new active state
  //Pre: stateNum is a valid index within controlStates
  //Post: currentState is newly set to stateNum
  
  virtual void Up(float scale = 1.0);
  virtual void Down(float scale = 1.0);
  virtual void Left(float scale = 1.0);
  virtual void Right(float scale = 1.0);
  virtual void NoInput(float scale = 1.0);
  //All five functions above represent movement controls. Scale represents intensity of controls.
  //Scale will not effect SpeedMod effects, but will change maxSpeed and accelleration effects.
  //Pre: 
  //Post: Position changed accordingly. 
  
  /// It has been decided that this function will not be used and that this will be applied
  /// within the movement functions themselves. 
  //virtual void ApplyTimestep(float: time, float scale = 1.0);
  //Applies movement to controller according to time.
  //Pre: 
  //Post: Movement applied 
};

#endif