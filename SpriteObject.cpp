//SPECIFICATION FILE

#include "SpriteObject.h"
#include <iostream> //debug only
  using namespace std;
//CONSTRUCTOR AND DESTRUCTORS///////////////////////////////////////
// ObjectID::ObjectID(char ch, int num)
// {
//   objChar = ch;
//   objNum = num;
// }
  
SpriteObject::SpriteObject(string Name, int Xinit, int Yinit,  float scaleValue, string ObNum, float fpsTimer) : 
			name(Name), xPos(Xinit), yPos(Yinit), ID(ObNum), scaleX(scaleValue), scaleY(scaleValue), spriteFrameTime(fpsTimer)
{
  if (scaleValue <= 0 || scaleValue == 1.0)
    scaled = false;
  else
    scaled = true;
  active = false;
  visible = false;
  currentFrameTime = 0.0;
  //CREATE PARAMATERS FOR THESE LATER
}
//GETTER FUNCTIONS////////////////////////////////////////////////////

int const SpriteObject::GetXPos(){
  return xPos;
}

int const SpriteObject::GetYPos(){
  return yPos;
}

// int const SpriteObject::GetObjNum(){
//   return ID.objNum;
// }
// 
// int const SpriteObject::GetObjChar(){
//   return ID.objChar;
// }

// int const SpriteObject::GetCurrentFrameCount(){
//   return currentFrameCount;
// }

string const SpriteObject::GetObjID(){
  return ID;
}

bool const SpriteObject::IsVisible(){
  return visible;
}

bool const SpriteObject::IsActive(){
  return active;
}

float const SpriteObject::GetCurrentFrameTime(){
  return currentFrameTime;
}

float const SpriteObject::GetSpriteFrameTime(){
  return spriteFrameTime;
}

//TRANSFORMER FUNCTIONS/////////////////////////////////////////////////////
void SpriteObject::ChangePos(int x, int y){
  xPos = x;
  yPos = y;
}

void SpriteObject::Activate(){
  active = true;
}

void SpriteObject::DeActivate(){
  active = false;
}

bool SpriteObject::DrawMe(){
  if (currentFrame){
    if (!scaled)
      al_draw_bitmap(currentFrame, xPos, yPos, 0); //the 0 will need to be replaced to flipping verticly/horizontally eventually to see both directions. paramater may need to be added
    else
      al_draw_scaled_bitmap(currentFrame, 0 , 0, al_get_bitmap_width(currentFrame), al_get_bitmap_height(currentFrame), 
			    xPos, yPos, al_get_bitmap_width(currentFrame) * scaleX, al_get_bitmap_height(currentFrame) * scaleY, 0);
  }
  else
    return 0;
  return 1;
}

// bool SpriteObject::AddFrameTime(float time)
// { /*VIRTUAL -- NOT TO BE IMPLEMENTED HERE -- VIRTUAL*/
//   return false;
// }

bool const SpriteObject::operator==(const SpriteObject &s)
{  return (ID == s.ID); }
bool const SpriteObject::operator!=(const SpriteObject &s)
{  return (ID != s.ID); }
bool const SpriteObject::operator>=(const SpriteObject &s)
{  return (ID >= s.ID); }
bool const SpriteObject::operator<=(const SpriteObject &s)
{  return (ID <= s.ID); }
bool const SpriteObject::operator> (const SpriteObject &s)
{  return (ID >  s.ID); }
bool const SpriteObject::operator< (const SpriteObject &s)
{  return (ID <  s.ID); }

//BELOW ARE ALL PROTECTED FUNCTIONS////////////////////////////////////////////////////

bool SpriteObject::NewFrame(ALLEGRO_BITMAP* frame){
  if (frame)
  {
    currentFrame = frame;
  }
  else
    return 0;
  return 1;
}

void SpriteObject::AddTime(float time)
{
  currentFrameTime += time;
}