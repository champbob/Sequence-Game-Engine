#include "GAMELIBS.h"
#include <iostream>
#include <iomanip>
#include <thread>
    using namespace std;

bool AllegroInit();
//Initializes allegro drivers
//Pre:
//Post: returns 1 if error

void LoadScreen(ALLEGRO_DISPLAY* display, LevelObject* LoadAnimation, bool* loading);

float const MIN_FRAME_TIME = 1.0/100.0; //creates a maximum fps. SECOND NUMBER IS THE DESIRED FPS
int const MAX_FRAMERATE = 30;

int main(int argc, char **argv)
{ //argument list: 1. name of LEVEL file -- 2. name of directory if any -- 3. unique sprite FPS **NOT IMPLEMENTED
  GameGlobals::InitializeGlobals();
  if (argc < 2)
  {
    cout << "YOU DIDN'T INCLUDE A LEVEL FILENAME\n";
    return 0;
  }
  string filename = argv[1];
  string filepath;
  int spriteFPS;
  int TEMPCOUNT = 0;
  if (argc == 3)
    filepath = argv[2];
//   if (argc == 4)
//     spriteFPS = argv[3];
//   else
    spriteFPS = GameGlobals::GetFPS();
  double timestep = 1.0 / spriteFPS;
  int currentFPS = 1.0 / timestep;
  bool contAnimation = true;
  ALLEGRO_TIMER* frameTimer;
  
  if (AllegroInit()) //if drivers fail to initialize, stop
    return 1;
  
  ALLEGRO_DISPLAY *display = NULL;
  ALLEGRO_EVENT_QUEUE *events = NULL;
    
  if (GameGlobals::IsFullScreen())
    al_set_new_display_flags(ALLEGRO_FULLSCREEN);
  else if (GameGlobals::IsBorderless())
    al_set_new_display_flags(ALLEGRO_FRAMELESS);
  display = al_create_display(GameGlobals::GetScreenResX(), GameGlobals::GetScreenResY()); //creates display with given paramaters
  if (!display) 
  {
    cout << "failed to create display!\n";
    return 1;
  }
  
  events = al_create_event_queue();
  if (!events)
  {
    cout << "failed to create event queue\n";
    al_destroy_display(display);
    return 1;
  }
  
  frameTimer = al_create_timer(timestep);
  if (!frameTimer)
  {
    al_destroy_display(display);
    al_destroy_event_queue(events);
    cout << "Dam timers...\n";
    return 1;
  }
  
  al_register_event_source(events, al_get_keyboard_event_source());
  al_register_event_source(events, al_get_mouse_event_source());
  al_register_event_source(events, al_get_display_event_source(display));
  al_register_event_source(events, al_get_timer_event_source(frameTimer));
  cout << "Events registered\n";
  
  bool loading = true;
  LevelObject LoadingScreen("LevelLoading.dat");
  al_set_target_bitmap(NULL);
  thread LoadingScreenThread(LoadScreen, display, &LoadingScreen, &loading);
  LevelObject MyLevel(filepath + filename);
  loading = false;
  LoadingScreenThread.join();
  al_set_target_bitmap(al_get_backbuffer(display));
  
//   while (true) //MEMLEAK TEST
//   {
//     MyLevel.CleanLevel();
//     MyLevel.LoadNewLevel(filepath + filename);
//   }
  
  al_start_timer(frameTimer);
  while (contAnimation)
  {
      ALLEGRO_EVENT event;
      al_wait_for_event(events,&event);
      
      switch (event.type)
      if (event.type == ALLEGRO_EVENT_TIMER){
	MyLevel.AddTime(timestep);
	MyLevel.DrawALL();
	al_flip_display();
	al_clear_to_color(al_map_rgb(0,0,0));
      }
      else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
	break;
      else if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
      {
	switch (event.keyboard.keycode)
	{
	  case ALLEGRO_KEY_ESCAPE: contAnimation = false; break;
	  case ALLEGRO_KEY_UP: MoveSprite(,event); break;
	  case ALLEGRO_KEY_DOWN: MoveSprite(,event); break;
	  case ALLEGRO_KEY_RIGHT: MoveSprite(,event); break;
	  case ALLEGRO_KEY_LEFT: MoveSprite(,event); break;
	}
      }
      else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event.mouse.button == 1)
	break;
  }
  
  al_destroy_event_queue(events);
  al_destroy_display(display);
  cout << "PROGRAM DONE\n";
  
  return 0;
}

void LoadScreen(ALLEGRO_DISPLAY* display, LevelObject* loadAnimation, bool* loading)
{
  al_set_target_bitmap(al_get_backbuffer(display));
  float timestep = 1.0/GameGlobals::GetFPS();
  ALLEGRO_EVENT_QUEUE *events = al_create_event_queue();
  if (!events)
  {
    cout << "LOADSCREEN::failed to create event queue\n";
    al_destroy_display(display);
    throw;
  }
  
  ALLEGRO_TIMER* frameTimer = al_create_timer(timestep);
  if (!frameTimer)
  {
    cout << "LOADSCREEN::Dam timers...\n";
    throw;
  }
  al_register_event_source(events, al_get_timer_event_source(frameTimer));
  
  al_start_timer(frameTimer);
  while (*loading && loadAnimation)
  {
      ALLEGRO_EVENT event;
      al_wait_for_event(events,&event);
      if (event.type == ALLEGRO_EVENT_TIMER)
      {
	loadAnimation -> AddTime(timestep);
	loadAnimation -> DrawALL();
	al_flip_display();
	al_clear_to_color(al_map_rgb(0,0,0));
      }
      else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event.mouse.button == 1)
	break; //DEBUG PURPOSE ONLY. DELETE ELSEIF AFTER DEBUGGING
  }
  al_set_target_bitmap(NULL);
  al_destroy_event_queue(events);
  al_destroy_timer(frameTimer);
}


void MoveSprite(SimpleController* moveMe, ALLEGRO_EVENT direction)
{
  if (direction.keyboard.keycode == ALLEGRO_KEY_UP)
    moveMe -> Up();
  else if (direction.keyboard.keycode == ALLEGRO_KEY_DOWN)
    moveMe -> Down();
  else if (direction.keyboard.keycode == ALLEGRO_KEY_LEFT)
    moveMe -> Left();
  else if (direction.keyboard.keycode == ALLEGRO_KEY_RIGHT)
    moveMe -> Right();
}

bool AllegroInit()
{
  if (!al_init()){ //initialize allegro. If failure, exit program
    cout << "failed to initialize allegro.\n";
    return true;
  }
  
  if (!al_install_mouse())
  {
    cout << "failed to initialize the mouse\n";
    return true;
  }
  
  if (!al_install_keyboard()){
    cout << "failed to install keyboard\n";
    return true;
  }

  if(!al_init_image_addon()) {
      cout << "failed to initialize the image addon!\n";
      return true;
  }
  return false;
}