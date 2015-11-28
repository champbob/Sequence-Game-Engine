/* SPRITEOBJECT CLASS HEIGHARCHY HEADER
 * Any currently unneeded variables will be commented out for the purpose of the small program "animatemequick"
 */

#ifndef SPRITEOBJECT
#define SPRITEOBJECT

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <vector>
#include <string>
  using namespace std;
  
// struct ObjectID
// {
//   char objChar;
//   int objNum;
//   
//   ObjectID(char ch, int num);
// };
  
class SpriteObject {
  private:

    const string ID;		//ex: a1, b1, b2, ...
    string name;
    int xPos;			//bitmap x pos
    int yPos;			//bitmap y pos
    bool visible;		//do we see this object?
    bool active;		//Is this object activated?
    bool scaled;		//Is this object being scaled at all?
    ALLEGRO_BITMAP* currentFrame; //Current frame to be rendered
    float const spriteFrameTime;		//amount of time each frame should be shown (fps)
    float currentFrameTime;			//How long the current frame has been displayed
    float scaleX;		//How much this object has been scaled in the X direction
    float scaleY;		//How much this object has been scaled in the Y direction

    //allegro audio variables
    
    SpriteObject();
    //this object is not to be declared by itself. Refer to children.
    
    //UpdateHitBox();
  public: 
    virtual ~SpriteObject() {}
    //This class does not need a destructor, as the only pointer in this class is deleted by the childclass (if needed)

//GETTER FUNCTIONS////////////////////////////////////////////////////
    int const GetXPos();
    //Returns current x position of the SpriteObject
    //Pre: 
    //Post: X position returned
    
    int const GetYPos();
    //Returns current Y position of the SpriteObject
    //Pre: 
    //Post: Y position returned
    
//    int const GetObjNum();
    //Returns number part of the object number
    //Pre:
    //Post: ObjNum integer returned
    
//    int const GetObjChar();
    //Returns character part of the object number
    //Pre: 
    //Post: Returns ObjectID struct containing this objects ID

    string const GetObjID();
    //Returns Object Number
    //Pre: 
    //Post: Returns ID
    
    bool const IsVisible();
    //Returns wether or not this object is meant to be visible
    //Pre:
    //Post: 1 = visible ----- 0 = invisible
    
    bool const IsActive();
    //Describes if this object should interact with anything at all
    //Pre:
    //Post: 1 = active ----- 0 = inactive
    
    float const GetCurrentFrameTime();
    //Gets the amount of time that has passed for the current frame.
    //**FRAME TIME ONLY UPDATED ONCE EVERY GLOBAL FRAME
    //Pre:
    //Post: returns CurrentFrameCount
    
    float const GetSpriteFrameTime();
    //returns current frame's time (for use in nextframe())
    //Pre:
    //Post: returns time that the current frame has been displayed for    
//TRANSFORMER FUNCTIONS/////////////////////////////////////////////////////
    void ChangePos(int x, int y);
    //Changes position of the object. 
    //Pre: 
    //Post: Position changed accordingly
    
    void Activate();
    //Activates object
    //Pre: 
    //Post: IsActive() = 1
    
    void DeActivate();
    //Deactivates object
    //Pre: 
    //Post: IsActive() = 0
    
    bool DrawMe();
    //Renders this object to frame
    //Pre: Object is active, visible, currentFrame exists and is not NULL.
    //Post: 1 = Item was drawn. 0 = Item was not drawn.
    
    virtual bool AddFrameTime(float time) = 0;
    //Adds time to the current frame being displayed. Will also change to the next sprite frame if
    //the time is >= spriteFrameTime
    //Pre: time is NOT negative
    //Post: Frametime added. If it becomes time to change to the next sprite frame, this function will do that as well.
    //      Returns 1 if frame is changed. 0 if not.
    
    bool const operator==(const SpriteObject &s);
    bool const operator!=(const SpriteObject &s);
    bool const operator>=(const SpriteObject &s);
    bool const operator<=(const SpriteObject &s);
    bool const operator>(const SpriteObject &s);
    bool const operator<(const SpriteObject &s);
    //operators above compare only the objectID
    
  protected:
    SpriteObject(string Name, int Xinit, int Yinit, float scaledValue, string ObNum, float fpsTimer);
    //CONSTRUCTOR -- will be called by children.
    //Pre: scaleValue > 0
    //Post: variables initialized correctly
    
    bool NewFrame(ALLEGRO_BITMAP* frame);
    //Will set the current image of the sprite to the new frame
    //Pre: frame is not null
    //Post: 1 for success; 0 otherwise
    
    void AddTime(float time);
    //Adds time to the current frame time.
    //Pre: time not negative
    //Post: time added to currentFrameTime
  };

#endif