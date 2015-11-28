//SPECIFICATION FILE
#include "HumanObject.h"

//CONSTRUCTOR AND DESTRUCTORS///////////////////////////////////////
    HumanSprite::HumanSprite(string Name, string imgSequence, int Xinit, int Yinit, char ObChar, int ObNum, string subFolders, int timer):
				SpriteObject(Name, Xinit, Yinit, ObChar, ObNum), frameTimer(timer)
    {
      animation[IDLE] = GetImgSequence(imgSequence + "_IDLE", subFolders);
      animation[WALK] = GetImgSequence(imgSequence + "_WALK", subFolders);
      animation[JUMP] = GetImgSequence(imgSequence + "_JUMP", subFolders);
      animation[CLIMB] = GetImgSequence(imgSequence + "_CLIMB", subFolders);
      animation[HURT] = GetImgSequence(imgSequence + "_HURT", subFolders);
    }
    
    HumanSprite::~HumanSprite(){
      for (int x = 0; x < 5; x++)
	for (int y = 0; y < animation[x].size(); y++)
	  al_destroy_bitmap(animation[x][y]);
    }
    
    
//GETTER FUNCTIONS////////////////////////////////////////////////////
    bool const HumanSprite::GetFrameTimer()
    { return frameTimer;}
    
    int const HumanSprite::GetCurrentFrameCount()
    { return currentFrameCount;}
    
    
//TRANSFORMER FUNCTIONS/////////////////////////////////////////////////////
    bool HumanSprite::ChangeGraphic(AnimationType type)
    {
      if (animation[type].size() > 0){ 
	currentAnimation = type;
	currentFrameCount = 0;
	NewFrame(animation[currentAnimation][0]);
	return true;
      }
      return false;
    }
    
    bool HumanSprite::NextFrame(){
      if (currentFrameCount == animation[currentAnimation].size() - 1){
	currentFrameCount = 0;
	NewFrame(animation[currentAnimation][0]);
	return true;
      }
      else {
	currentFrameCount++;
	NewFrame(animation[currentAnimation][currentFrameCount]);
	return true;
      }
    }