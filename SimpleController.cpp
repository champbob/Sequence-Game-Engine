#include "SimpleController.h"
#include "SpriteObject.h"
#include <cmath>

SimpleController::SimpleController(SpriteObject* targetSprite): ControllerObject(targetSprite)
{
  SimpleControlState def;
  def.xMaxSpeed = 0;
  def.yMaxSpeed = 0;
  def.xAccel = 0;
  def.yAccel = 0;
  def.xSpeedMod = 0;
  def.ySpeedMod = 0;
  controlStates.push_back(def); //temp state
  controlStates.push_back(def); //default state
  currentState = 1; //default state
}

SimpleController::SimpleController(SpriteObject* targetSprite, SimpleControlState state): ControllerObject(targetSprite)
{
  SimpleControlState def;
  def.xMaxSpeed = 0;
  def.yMaxSpeed = 0;
  def.xAccel = 0;
  def.yAccel = 0;
  def.xSpeedMod = 0;
  def.ySpeedMod = 0;
  controlStates.push_back(def); //temp state
  controlStates.push_back(state); //default state
  currentState = 1; //default state
}

const SimpleController::SimpleControlState SimpleController::GetActiveState()
{
  if (currentState >= controlStates.size())
    return controlStates[1];
  return controlStates[currentState];
}

void SimpleController::AddState(SimpleControlState newState)
{
  controlStates.push_back(newState);
}

void SimpleController::TempState(SimpleControlState newState)
{
  controlStates[0] = newState;
}

bool SimpleController::ReplaceState(int stateNumToReplace, SimpleControlState newState)
{
  if (stateNumToReplace < controlStates.size() && stateNumToReplace >= 0)
  {
    controlStates[stateNumToReplace] = newState;
    return true;
  }
  return false;
}

bool SimpleController::DeleteState(int stateNum)
{
  if (stateNum >= 0 && stateNum < controlStates.size())
  {
    controlStates.erase(controlStates.begin()+stateNum - 1);
    return true;
  }
  return false;
}

bool SimpleController::SetState(int stateNum)
{
  if (stateNum < controlStates.size() && stateNum > -1)
  {
    currentState = stateNum;
    return true;
  }
  return false;
}


/* MOVEMENT EQUATION FOR CONTROL FUNCTIONS BELOW:
 * PixelsPerUnit * Timestep * (direction * scale * currSpeed + speedMod)
 * 
 * ACCELERATION:
 * newspeed = currSpeed + acceleration * timestep * scale
 */

void SimpleController::Up(float scale)
{ //remember: Y screen coordinates are inverted, as (0,0) is at the top left of the screen
  if (enabled)
  {
    int displacement = 0;
    displacement = GameGlobals::GetUnitPixels() * GameGlobals::GetCurrentTimestep() *
                   (-1 * scale * ySpeed - controlStates[currentState].ySpeedMod);
    ySpeed += controlStates[currentState].yAccel * GameGlobals::GetCurrentTimestep() * scale;
    if (controlledSprite)
      controlledSprite -> ChangePos(controlledSprite -> GetXPos(),
				    controlledSprite -> GetYPos() + displacement);
    if (abs(ySpeed + controlStates[currentState].ySpeedMod) > abs(controlStates[currentState].yMaxSpeed * scale))
    {
      if (ySpeed < 0)
	ySpeed = -controlStates[currentState].yMaxSpeed * scale;
      else
	ySpeed = controlStates[currentState].yMaxSpeed * scale;
    }
  }
}

void SimpleController::Down(float scale)
{ //remember: Y screen coordinates are inverted, as (0,0) is at the top left of the screen
  if (enabled)
  {
    int displacement = 0;
    displacement = GameGlobals::GetUnitPixels() * GameGlobals::GetCurrentTimestep() *
                   (1 * scale * ySpeed - controlStates[currentState].ySpeedMod);
    ySpeed += -controlStates[currentState].yAccel * GameGlobals::GetCurrentTimestep() * scale;
    if (controlledSprite)
      controlledSprite -> ChangePos(controlledSprite -> GetXPos(),
				    controlledSprite -> GetYPos() + displacement);
    if (abs(ySpeed + controlStates[currentState].ySpeedMod) > abs(controlStates[currentState].yMaxSpeed * scale))
    {
      if (ySpeed < 0)
	ySpeed = -controlStates[currentState].yMaxSpeed * scale;
      else
	ySpeed = controlStates[currentState].yMaxSpeed * scale;
    }
  }
}

void SimpleController::Left(float scale)
{
  if (enabled)
  {
    int displacement = 0;
    displacement = GameGlobals::GetUnitPixels() * GameGlobals::GetCurrentTimestep() *
                   (-1 * scale * xSpeed - controlStates[currentState].xSpeedMod);
    xSpeed += -controlStates[currentState].xAccel * GameGlobals::GetCurrentTimestep() * scale;
    if (controlledSprite)
      controlledSprite -> ChangePos(controlledSprite -> GetXPos() + displacement,
				    controlledSprite -> GetYPos());
    if (abs(xSpeed + controlStates[currentState].ySpeedMod) > abs(controlStates[currentState].xMaxSpeed * scale))
    {
      if (xSpeed < 0)
	xSpeed = -controlStates[currentState].xMaxSpeed * scale;
      else
	xSpeed = controlStates[currentState].xMaxSpeed * scale;
    }
  }
}

void SimpleController::Right(float scale)
{
  if (enabled)
  {
    int displacement = 0;
    displacement = GameGlobals::GetUnitPixels() * GameGlobals::GetCurrentTimestep() *
                   (1 * scale * xSpeed - controlStates[currentState].xSpeedMod);
    xSpeed += -controlStates[currentState].xAccel * GameGlobals::GetCurrentTimestep() * scale;
    if (controlledSprite)
      controlledSprite -> ChangePos(controlledSprite -> GetXPos() + displacement,
				    controlledSprite -> GetYPos());
    if (abs(xSpeed + controlStates[currentState].ySpeedMod) > abs(controlStates[currentState].xMaxSpeed * scale))
    {
      if (xSpeed < 0)
	xSpeed = -controlStates[currentState].xMaxSpeed * scale;
      else
	xSpeed = controlStates[currentState].xMaxSpeed * scale;
    }
  }
}

void SimpleController::NoInput(float scale)
{
  ySpeed = 0;
  xSpeed = 0;
}