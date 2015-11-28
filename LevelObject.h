//LevelObject
//Each LevelObject contains all required bitmaps for a level and has methods to draw either a section of the level or the entire level (regardless of where camera is)
#ifndef _LEVELCLASS
#define _LEVELCLASS
#include <map>
#include <memory>
#include "SPRITES.h"
#include "CONTROLLERS.h"
//#include "GAMELIBS.h"
  using namespace std;

class LevelObject
{
private:
  bool loaded;						//1 if level is loaded. 0 otherwise.
  string currentLevel;					//Contains filename of the current level. Used for copy constructor and assignment operator
  map<string, vector<ALLEGRO_BITMAP*> > allBitmaps;	//Library of ALL bitmaps to be cleaned up when the level is cleaned.
  vector<string> bitmapKeys;				//Contains all keys to allBitMaps map.
  vector< unique_ptr<SpriteObject> > allObjects;	//All Objects. 
  vector<GraphicObject*> allGraphics;			//All GraphicObjects.
  vector<ControllerObject*> allControllers;		//All ControllerObjects.
  vector<SimpleController*> allSimpleControllers;	//All SimpleControllers.
  //vector<PhysController*> allPhysControllers;
  
  vector<ALLEGRO_BITMAP*> GetImgSequence(string sequence, string subFolders);
  //Images are loaded by name in sequence (ex: name01, name02, name03, etc)
  //Pre: 
  //Post: vector is returned with the results of opening the files. (if none found, vector will be empty)
  
  void AddSprite(string type, string name, int x, int y, float scale, string obNum, int fps, vector<vector<ALLEGRO_BITMAP*> > bitmaps, string layer);
  //A SpriteObject is declared and added to the proper containers. This is only meant for use during level loadtime.
  //Pre: bitmaps IS NOT NULL
  //	 bitmaps has SPECIFIC SIZES dependent on type.
  //	 layer has been declared and stored in the layers map already.
  //Post: bitmap is declared and added to the proper sprite containers depending on type.
  
public:
  vector<string> layerKeys;				//SORTED List of keys for layer directories. Public for ease.
  map<string, vector<SpriteObject*> > layers;		//Map of layers. Each layer contains all object within layer.
  vector<string> interactiveLayer; 			//Keys that represent the interactive layers
  
  //CONSTRUCTORS
  LevelObject();	//creates object without loading a level
  LevelObject(string level); //creates object and attempts to load a level
  ~LevelObject();

  bool const IsLevelLoaded();
  //Checks if the level is ready to be used and a level has been loaded.
  //Pre: 
  //Post: returns 1 if a level has been loaded and ready to use
  
  bool LoadNewLevel(string level, string directory = "");
  //Loads a new level into the current object. WILL CALL CleanLevel()
  //Pre:
  //Post: Returns 1 if load was successful. 0 if not.
  
  void const DrawALL();
  //
  //Pre: All allObjects pointers are VALID
  //Post: EVERY OBJECT is drawn, regardless if onscreen or not.
  
  void const DrawArea(int x1, int y1, int x2, int y2);
  //To be used until hitboxes are implemented
  //Pre: All allObjects pointers are VALID
  //Post: Objects within defined area are drawn.
  
  void AddTime(float time);
  //Adds time to all sprites
  //Pre: All pointers in allObjects are VALID
  //Post: AddFrameTime(float time) is called on every object.
  
  void CleanLevel();
  //CLEANS ENTIRE LEVEL FROM MEMORY without destroying the object
  //Pre:
  //Post: All vectors cleaned, map cleared, bitmaps destroyed.
};

#endif