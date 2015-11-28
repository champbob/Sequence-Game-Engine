#include "LevelObject.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include "Globals.h"

LevelObject::LevelObject(): loaded(false), currentLevel(""), interactiveLayer(0)
{}

LevelObject::LevelObject(string level): interactiveLayer(0)
{
  loaded = LoadNewLevel(level);
  if (loaded)
    currentLevel = level;
  else
    currentLevel = "";
}

LevelObject::~LevelObject()
{ CleanLevel();}

bool const LevelObject::IsLevelLoaded()
{ return loaded; }

bool LevelObject::LoadNewLevel(string level, string directory)
{
  //Preparation:
  string fileName = directory + level;
  if (loaded)
  {
    CleanLevel();
    loaded = false;
  }
  ifstream newLevel;
  newLevel.open(fileName.c_str());
  if (!newLevel){
    newLevel.close();
    return 0;	//return 0 if level file not found
  }
  
  //Begin:
  fileName = "";	//Will be used again here
  directory = ""; 	//Will be used again here
  bool isDone = false;
  char inputType;
  string label;
  string layerDestination;
  string spriteType;
  string name;
  
  //below variables only used for declaring sprites.
  int x(0);
  int y(0);
  string objNum("");
  int fps(0);
  float scale(1.0);
  vector<vector<ALLEGRO_BITMAP*> > bitmapsIncluded;
  
  while (!isDone && newLevel)
  {
    inputType = newLevel.get();
    switch (inputType)
    {
      case '%': //BITMAP
	getline(newLevel, label, ':');
	getline(newLevel, fileName, ':');
	getline(newLevel, directory, ':');
	  cout << "LEVELOBJECT::LoadNewLevel: BITMAP LOADING: " << label << fileName << directory << endl;
	bitmapsIncluded.push_back(GetImgSequence(fileName, directory));
	allBitmaps.insert(pair<string, vector<ALLEGRO_BITMAP*> >(label, bitmapsIncluded[0]));
	break;
      case '!': //LAYER DECLARATION (pre-sorted)
	getline(newLevel, label, ':');
	  cout << "LEVELOBJECT::LoadNewLevel: LAYER DECLARATION: " << label << endl;
	layerKeys.push_back(label);
	break;
      case '&': //SPRITE OBJECT DECLARATION
	getline(newLevel, layerDestination, ':');
	getline(newLevel, spriteType, ':');
	getline(newLevel, name, ':');
	inputType = newLevel.get();	//repurposed here only to maintain the first character of the label during the while loop
	while (inputType != ':')
	{
	  getline(newLevel, label, ' ');
	  bitmapsIncluded.push_back(allBitmaps[label]);
	  inputType = newLevel.get();
	}
	newLevel >> x;
	newLevel.ignore(255,':');
	newLevel >> y;
	newLevel.ignore(255,':');
	newLevel >> scale;
	cout << "SCALE INPUT: " << scale << endl;
	newLevel.ignore(255,':');
	getline(newLevel, objNum, ':');
	newLevel >> fps;
	AddSprite(spriteType, name, x, y, scale, objNum, fps, bitmapsIncluded, layerDestination);
	break;
      case '>': //CONTROLLER DECLARATION
	
	break;
      case 'E':
	isDone = true;
	break;
      default:	//COMMENT OR FAILSAFE	
	break;
    }
    bitmapsIncluded.clear();
    newLevel.ignore(255,'\n');
  }
  
  newLevel.close();
  return 1;
}

void const LevelObject::DrawALL()
{
  for (int x = 0; x < layerKeys.size(); x++)
    for (int y = 0; y < layers[layerKeys[x]].size(); y++)
      layers[layerKeys[x]][y] -> DrawMe();
}

void const LevelObject::DrawArea(int x1, int y1, int x2, int y2)
{
  int SpriteX;
  int SpriteY;
  for (int x = 0; x < layerKeys.size(); x++)
    for (int y = 0; y < layers[layerKeys[x]].size(); y++)
    {
      SpriteX = layers[layerKeys[x]][y] -> GetXPos();
      SpriteY = layers[layerKeys[x]][y] -> GetYPos();
      if (SpriteX > x1 && SpriteX < x2
	  && SpriteY < y1 && SpriteY > y2)
	layers[layerKeys[x]][y] -> DrawMe();
    }
}

void LevelObject::AddTime(float time)
{
  int size = allObjects.size();
   for (int x = 0; x < size; x++){
     allObjects.at(x)->AddFrameTime(time);
   }
}

void LevelObject::CleanLevel()
{
  for (int x = 0; x < bitmapKeys.size(); x++) 				//For every key...
  {
    for (int y = 0; y < allBitmaps[ bitmapKeys[x] ].size(); y++)	//For every vector size related to that key...
      al_destroy_bitmap(allBitmaps[ bitmapKeys[x] ][y]);		//Destroy every bitmap in that vector.
    allBitmaps[ bitmapKeys[x] ].clear();				//Then clear the bitmap vector
  }
  allBitmaps.clear();				//clears bitmap map
  bitmapKeys.clear();				//clears list of keys for allBitmaps
  
  allObjects.clear();				//delete all sprite classes. Delete handled by unique_ptr
  allGraphics.clear();				//clears list of all graphics
  //when new types are added, clear here

  for (int x = 0; x < layerKeys.size(); x++)
    layers[ layerKeys[x] ].clear();		//clears every list of sprites inside every layer
  layers.clear();				//clears layer map
  layerKeys.clear();				//clear list of layer keys
  interactiveLayer.clear();			//no interactive layer anymore!
  loaded = false;
}


//PROTECTED
vector<ALLEGRO_BITMAP*> LevelObject::GetImgSequence(string sequence, string subFolders)
{
  int filecount = 1;
  string number;
  string filename;
  stringstream ss;
  vector<ALLEGRO_BITMAP*> images;
  ALLEGRO_BITMAP* loaded;
  
  ss << filecount;
  number = ss.str();
  while(true){
    filename = subFolders + sequence + number + ".png";
    cout << "LEVELOBJECT::GetImgSequence: Attempting to load file: " << filename << endl;
    loaded = al_load_bitmap(filename.c_str());
    ss.str("");
    filecount++;
    ss << filecount;
    number = ss.str();
    if (loaded)
      images.push_back(loaded);
    else{
      cout << "\tERROR LOADING FILE: " << filename << endl;
      break;
    }
  }
  if (images.size() == 0)
    cout << "\nERROR LOADING " << sequence << " IMAGE SEQUENCE\n";
  return images;
}

void LevelObject::AddSprite(string type, string name, int x, int y, float scale, string obNum,
			    int fps, vector<vector<ALLEGRO_BITMAP*> > bitmaps, string layer)
{  
  if (type == "GRAPHIC")
  {
    GraphicObject* NewSprite;
    allObjects.push_back(unique_ptr<GraphicObject>(new GraphicObject(name, bitmaps[0], x, y, scale, obNum, float(1.0/fps))));
    NewSprite = dynamic_cast<GraphicObject*>(allObjects.at(allObjects.size() - 1).get());
    allGraphics.push_back(NewSprite);
    layers[layer].push_back(NewSprite);
  }
  else if (type == "HUMAN") //NO HUMANSPRITE YET
  {}
  else if (type == "BUTTON") //NO BUTTONSPRITE YET
  {}
}

void LevelObject::AddController(string type, string controlled)
{
  
}