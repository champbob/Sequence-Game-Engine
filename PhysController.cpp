#include "PhysController.h"
#include "SpriteObject.h"
#include <iostream> //DEBUGGING PURPOSES ONLY

PhysController::PhysController(SpriteObject* targetSprite): ControllerObject(targetSprite)
{
  if (targetSprite)
    controlledSprite = targetSprite;
  PhysControlState def;
  def.drag = 0;
  def.mass = 1;
  def.gravityScale = 0;
  controlStates.push_back(def);
  controlStates.push_back(def);
  currentState = 1;
}

PhysController::PhysController(SpriteObject* targetSprite, PhysControlState state): ControllerObject(targetSprite)
{
  if (targetSprite)
    controlledSprite = targetSprite;
  controlStates.push_back(state);
  controlStates.push_back(state);
  currentState = 1;
}

const PhysController::PhysControlState PhysController::GetActiveState()
{
  return controlStates[currentState];
}

const int PhysController::GetActiveStateNum()
{
  if (currentState < controlStates.size())
    return currentState;
  return -1;
}

void PhysController::AddState(PhysControlState newState)
{
  controlStates.push_back(newState);
}

void PhysController::TempState(PhysControlState newState)
{
  controlStates[0]=newState;
}

bool PhysController::SetState(short int stateNum)
{
  if (stateNum < controlStates.size() && stateNum >= 0)
  {
    currentState = stateNum;
    return true;
  }
  return false;
}

//F=MA
void PhysController::ApplyXForce(float force)
{
  cout << "ballz\n";
}
void PhysController::ApplyYForce(float force)
{
  cout << "ballz\n";
}
void PhysController::NoInput(float force)
{
  cout << "ballz\n";
}
