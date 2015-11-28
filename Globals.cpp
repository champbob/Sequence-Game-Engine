//SPECIFICATION FILE
#include "Globals.h"
#include <fstream>
#include <iostream> //used for debugging, delete when done
using namespace std;
//CONSTRUCTOR AND DESTRUCTORS///////////////////////////////////////

GameGlobals::Resolution GameGlobals::currentScreenRes(1280,720);
int GameGlobals::fullScreen = 0;
float GameGlobals::scale = 1.0;
int GameGlobals::fps = 60;
const string GameGlobals::DEFAULTCONFIGFILECONTENTS = 
"currentScreenRes.x:1280\ncurrentScreenRes.y:720\nfullScreen:0\nscale:1.0\nfps:24\n"; //NOT USED, SEE BELOW
int GameGlobals::pixelsPerUnit = 100;
const string GameGlobals::DEFAULTCONFIGFILE = "CONFIG.cfg";
const GameGlobals::Resolution GameGlobals::nativeScreenRes(1280,720);

void GameGlobals::InitializeGlobals(string configfile)
{
  ifstream config;
  config.open(configfile.c_str());
  
  if (!config){
    cout << "GameGlobals::NO CONFIG\n";
    config.close();
    fullScreen = false;
    scale = 1.0;
    fps = 12;
    ofstream defaultconfig;
    cout << "GameGlobals::Opening New Config\n";
    defaultconfig.open("CONFIG.cfg");
    cout << "GameGlobals::Outputting...\n";
    defaultconfig << "currentScreenRes.x:1280\n\
      currentScreenRes.y:720\n\
      fullScreen:0\n\
      scale:1.0\n\
      fps:24\n"; 
		  //NEEDS FIXED. IF OUTPUTTING THE VARIABLE (defaultconfigfile), IT WILL SEGFAULT
    cout << "GameGlobals::Closing...\n";
    defaultconfig.close();
    cout << "GameGlobals::done\n";
  }
  else{
    cout << "GameGlobals::CONFIG FOUND\n";
    config.ignore(100,':');
    config >> currentScreenRes.x;
    config.ignore(100,':');
    config >> currentScreenRes.y;
    config.ignore(100,':');
    config >> fullScreen;
    config.ignore(100,':');
    config >> scale;
    config.ignore(100,':');
    config >> fps;
    config.close();
  }
}

//GETTER FUNCTIONS////////////////////////////////////////////////////
int const GameGlobals::GetScreenResX(){
  return currentScreenRes.x;
}

int const GameGlobals::GetScreenResY(){
  return currentScreenRes.y;
}

int const GameGlobals::GetNativeScreenResX(){
  return nativeScreenRes.x;
}

int const GameGlobals::GetNativeScreenResY(){
  return nativeScreenRes.y;
}

bool const GameGlobals::IsFullScreen(){
  if (fullScreen == 2)
    return true;
  else
    return false;
}

bool const GameGlobals::IsBorderless(){
  if (fullScreen == 1)
    return true;
  else
    return false;
}

bool const GameGlobals::IsWindowed(){
  if (fullScreen == 0)
    return true;
  else
    return false;
}

float const GameGlobals::GetScaleRatio(){
  return scale;
}

int const GameGlobals::GetFPS(){
  return fps;
}

float const GameGlobals::GetCurrentTimestep(){
  return 1.0/fps;
}
//TRANSFORMER FUNCTIONS/////////////////////////////////////////////////////
void GameGlobals::NewFPS(int newFPS){
  if (newFPS >= 0)
    fps = newFPS;
}

int const GameGlobals::GetUnitPixels()
{
  return pixelsPerUnit;
}

void GameGlobals::SetUnitPixels(unsigned int pixels)
{
  if (pixels > 0)
    pixelsPerUnit = pixels;
}

//NEED TRANSFORMER FUNCTIONS