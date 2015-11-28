//Class name and description.
#ifndef _LEVELCLASS
#define _LEVELCLASS
#include <vector>
#include <map>
#include "GAMELIBS.h"
  using namespace std;

class LevelContainer
{
private:
  map<string, vector<ALLEGRO_BITMAP*>> allBitMaps;
  vector<SpriteClass*> allObjects;
  vector<HumanSprite*> allHumans;
  vector<GraphicSprite*> allGraphics;
  vector<buttonSprite*> allButtons;
  vector<string> bitmapKeys;
  
  LevelContainer();
public:
  vector<string> layerKeys;
  map<string, vector<SpriteClass*>> layers;
  string interactiveLayer;
  
  ~LevelContainer();
};

#endif