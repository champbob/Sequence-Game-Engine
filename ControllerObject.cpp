#include "ControllerObject.h"
#include "SpriteObject.h"
#include "Globals.h"

ControllerObject::ControllerObject(SpriteObject* targetSprite):
    controlledSprite(NULL), xSpeed(0), ySpeed(0), enabled(true), flippedControls(false)
{
  if (targetSprite)
    controlledSprite = targetSprite;
}

SpriteObject* const ControllerObject::GetControlledSprite()
{
  return controlledSprite;
}

int const ControllerObject::GetXPos()
{
  if (controlledSprite)
    return controlledSprite -> GetXPos();
  return 0;
}

int const ControllerObject::GetYPos()
{
  if (controlledSprite)
    return controlledSprite -> GetYPos();
  return 0;
}

bool const ControllerObject::IsEnabled()
{ return enabled; }

void ControllerObject::Enable()
{ enabled = true; }

void ControllerObject::Disable()
{ enabled = false; }

void ControllerObject::SetPosition(int x, int y)
{
  if (controlledSprite)
    controlledSprite -> ChangePos(x,y);
}

float const ControllerObject::GetXSpeed()
{ return xSpeed; }

float const ControllerObject::GetYSpeed()
{ return ySpeed; }

void ControllerObject::Move(float scale)
{
  if (controlledSprite)
  {
    float timestep = 1.0 / GameGlobals::GetFPS();
    int pixelsPerUnit = GameGlobals::GetUnitPixels();
    //Timestep * xSpeed * pixelsPerUnit * scale = new position X (same for Y)
    //Euler integration to change position. Hitboxes handled elsewhere.
    controlledSprite -> ChangePos(timestep * xSpeed * pixelsPerUnit * scale + controlledSprite -> GetXPos(),
				  timestep * ySpeed * pixelsPerUnit * scale + controlledSprite -> GetYPos());
  }
}