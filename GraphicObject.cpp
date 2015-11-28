//SPECIFICATION FILE
#include "GraphicObject.h"

//CONSTRUCTOR AND DESTRUCTORS///////////////////////////////////////
GraphicObject::GraphicObject(string Name, vector<ALLEGRO_BITMAP*> imgSequence, int Xinit, int Yinit, float scaledValue, string objNum, float fpsTimer) :
			      SpriteObject(Name, Xinit, Yinit, scaledValue, objNum, fpsTimer), currentFrameNum(0)
{
  //animation = GetImgSequence(imgSequence, subFolders);
  animation = imgSequence;
  NewFrame(animation[0]);
  numFrames = animation.size() - 1;
}

GraphicObject::~GraphicObject(){
  //BITMAP DESTRUCTION HANDLED BY LEVELOBJECT
  animation.clear();
}


//GETTER FUNCTIONS////////////////////////////////////////////////////
int const GraphicObject::GetCurrentFrameCount(){
  return currentFrameNum;
}


//TRANSFORMER FUNCTIONS/////////////////////////////////////////////////////
bool GraphicObject::NextFrame(){
  currentFrameNum++;
  if (animation.empty())
    return 0;
  if (currentFrameNum < numFrames)
    NewFrame(animation.at(currentFrameNum));
  else{
    NewFrame(animation[0]);
    currentFrameNum = 0;
  }
  return 1;
}

bool GraphicObject::AddFrameTime(float time){
  bool framechanged = false;
  AddTime(time);
  while (GetSpriteFrameTime() < GetCurrentFrameTime()){
    AddTime(-GetSpriteFrameTime());
    NextFrame();
    framechanged = true;
  }
  return framechanged;
}