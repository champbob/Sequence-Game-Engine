#ifndef HUMANOBJECT
#define HUMANOBJECT

#include "SpriteObject.h"

/*CLASS AND DESCRIPTION
* This will be an object that has actual controls. Meant to switch between multiple modes of animation as input is said.
*/

class HumanSprite : public SpriteObject
{
  public:
    enum AnimationType {IDLE, WALK, JUMP, CLIMB, HURT};
    
    HumanSprite(string Name, string imgSequence, int Xinit, int Yinit, char ObChar, int ObNum, string subFolders = "", int timer = -1);
    ~HumanSprite();
    
    bool const GetFrameTimer();
    //Will get the frame timer (used for fps on the animations)
    //Pre: 
    //Post: frameTimer returned
    
    int const GetCurrentFrameCount();
    //Will get the current frame number
    //Pre: 
    //Post: currentFrameCount returned    
    
    bool ChangeGraphic(AnimationType type);
    //This will change the type of animation currently being displayed if specified type exists.
    //Pre: type is a valid type (valid types shown in AnimationType type)
    //Post: Animation is reset and animation shown is changed to the new one, starting at the first frame
    
    bool NextFrame();
    //Will proceed the animation to the next frame
    //Pre: 
    //Post: frame shown (and to be rendered) is changed to the next frame in accordance to the current type of animation notes.

  private:
    vector<ALLEGRO_BITMAP*> animation[5];		//contains all animations for the animation types needed. SOME CAN BE EMPTY IF WANTED
    AnimationType currentAnimation;			//contains current type of animation
    int frameTimer;					//fps
    int currentFrameCount;				//number of the current frame of the current animation
    
    HumanSprite();					//default constructor is not to be called. Refer to public constructor
    
  protected:
    
};

#endif