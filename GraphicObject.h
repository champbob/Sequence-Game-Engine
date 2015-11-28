#ifndef GRAPHICOBJECT
#define GRAPHICOBJECT

#include "SpriteObject.h"

class GraphicObject : public SpriteObject
{
  private: 
    GraphicObject();				//default constructor is not to be called. refer to the public constructor
    vector<ALLEGRO_BITMAP*> animation;		//contains the frames for this object
    int numFrames;				//Contains number of frames. ONLY HERE SO AS NOT TO ALWAYS CALL [animation.size() - 1;] ALL THE TIME
    int currentFrameNum;			//Frame # of the animation.
    
    bool NextFrame();
    //Goes to and sets next frame as current frame
    //Pre:
    //Post: 1 = successful. 0 = unsuccessful
  public:
    GraphicObject(string Name, vector<ALLEGRO_BITMAP*> imgSequence, int Xinit, int Yinit, float scaledValue, string objNum, float fpsTimer);
    //Pre: imgSequence is NOT NULL
    //Post: imgSequence copied over to Animation. All other variables initialized
    
    ~GraphicObject();
    //Only to clear the vector before releasing memory (DOES NOT DESTROY BITMAPS)
    
    int const GetCurrentFrameCount();
    //returns current frame count (for use in nextframe())
    //Pre:
    //Post: returns current frame number for animation.
    
    bool AddFrameTime(float time);
    //Adds time to the current frame being displayed. Will also change to the next sprite frame if
    //the time is >= spriteFrameTime
    //Pre: time is NOT negative
    //Post: Frametime added. If it becomes time to change to the next sprite frame, this function will do that as well.
    //      Returns 1 if frame is changed. 0 if not.

    
};

#endif