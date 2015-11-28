#ifndef _CONTROLLEROBJECT
#define _CONTROLLEROBJECT
#include <vector> //for children

class SpriteObject; //TO SEE DETAILS, SEE SpriteObject.h

class ControllerObject
{
private:
  ControllerObject();
  
protected:
  SpriteObject* controlledSprite; //contains x and y position as well
  float xSpeed;		//current speed in X direction
  float ySpeed;		//current speed in Y direction
  
  bool enabled;		//Is this controller active? If not, only setting position will work
  bool flippedControls; 
  
  ControllerObject(SpriteObject* targetSprite); //constructor for child classes
  
public:
  SpriteObject* const GetControlledSprite();
  //Returns the target sprite that this class is controlling
  //Pre: 
  //Post: Returns ControlledSprite. NULL if error.
  
  int const GetXPos();
  //Gets and returns X position from ControlledSprite
  //Pre: ControlledSprite != NULL
  //Post: returns sprite's X position. If NULL, returns 0
  
  int const GetYPos();
  //Gets and returns Y position from ControlledSprite
  //Pre: ControlledSprite != NULL
  //Post: returns sprite's Y position. If NULL, returns 0
  
  bool const IsEnabled();
  //Returns wether or not this controller is active
  //Pre:
  //Post: returns enabled
  
  void Enable();
  //Enables the controller
  //Pre:
  //Post:
  
  void Disable();
  //Disables the controller
  //Pre:
  //Post: 
  
  void SetPosition(int x, int y);
  //Forcibly sets X and Y position of the spriteObject.
  //BYPASSES CONTROLS AND DOES NOT CHECK IF ACTIVE. DIRECT MANIPULATION.
  //Pre:
  //Post: x and y are set as the sprite's new position regardless.
  
  float const GetXSpeed();
  //Returns current speed in x direction
  //Pre: 
  //Post: 
  
  float const GetYSpeed();
  //Returns current speed in y direction
  //Pre: 
  //Post: 
  
  void Move(float scale = 1.0);
  //Moves according to currentspeed and current fps value.
  //Pre: 
  //Post: sprite (if there is any) is moved.
};
#endif