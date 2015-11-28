#ifndef _GAMEGLOBALS
#define _GAMEGLOBALS
// This static class contains global game engine configuration. 
// This was made with the intention of easy access to global engine config
// The class will be expanded as more engine globals are needed.
#include <string>
  using namespace std;

class GameGlobals
{
  private:
    struct Resolution{
      int x;
      int y;
      
      Resolution(int X, int Y): x(X), y(Y) {}
    };
    
    static Resolution currentScreenRes;		//current game resolution
    static int fullScreen;			//2 = fullscreen, 1 = borderless, 0 = windowed
    static float scale;				//scale in accordance to native vs current screenres. Used for the sprites.
    static int fps;				//GLOBAL fps
    static int pixelsPerUnit;			//Physics going by pixel is really slow. This combined with scale will speed things up.
    static const string DEFAULTCONFIGFILECONTENTS;
    static const string DEFAULTCONFIGFILE;
    static const Resolution nativeScreenRes;	//default game resolution (also preferred). value is 1280x720
    
    GameGlobals();
    //Static class
  public:
    static void InitializeGlobals(string configfile = DEFAULTCONFIGFILE);
    //Sets up the class. CALL THIS BEFORE ANYTHING ELSE!
    //Pre: 
    //Post: if configfile not found, creates default
    //	    if configfile found, loads in settings from file
    
    static int const GetScreenResX();
    //Gets currentscreenRes x value
    //Pre: 
    //Post: currentScreenRes x value returned
    
    static int const GetScreenResY();
    //Gets currentscreenRes y value
    //Pre: 
    //Post: currentScreenRes y value returned
    
    static int const GetNativeScreenResX();
    //Gets nativeScreenRes x value
    //Pre: 
    //Post: nativeScreenRes x value returned
    
    static int const GetNativeScreenResY();
    //Gets nativeScreenRes Y value
    //Pre: 
    //Post: nativeScreenRes Y value returned
    
    static bool const IsFullScreen();
    //Returns wether or not the game is meant to be in fullscreen.
    //Pre:
    //Post: returns 1 for fullscreen, else 0
    
    static bool const IsBorderless();
    //Returns wether or not the game is meant to be in borderless windowed mode
    //Pre:
    //Post: returns 1 for borderless, 0 for not
    
    static bool const IsWindowed();
    //Returns wether or not the game is meant to be in windowed mode
    //Pre:
    //Post: returns 1 for windowed, 0 for not
    
    static int const GetFPS();
    //Gets the game's the current FPS
    //Pre:
    //Post: returns fps
    
    static float const GetCurrentTimestep();
    //Gets current timestep
    //Pre: FPS > 0
    //Post: returns 1/fps
    
    static float const GetScaleRatio();
    //The scale according to the current screen resolution vs the native. Used mainly for scaling sprites
    //Pre: 
    //Post: Returns ratio in a float
    
    static void NewFPS(int newFPS);
    //This will change the FPS
    //Pre: newFPS >0
    //Post: fps changed to new FPS. Please remember restate anything that is linked to FPS
    
    static int const GetUnitPixels();
    //This will return the amount of pixels are in each unit (horiz/vert wise)
    //Pre: 
    //Post: 
    
    static void SetUnitPixels(unsigned int pixels);
    //This will set unit pixel size to pixels
    //Pre: pixels > 0
    //Post: 
    
  protected:
    //poot
};


#endif