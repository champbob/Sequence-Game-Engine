SpriteObject.o: SpriteObject.h SpriteObject.cpp
		g++ SpriteObject.cpp -c `pkg-config --libs allegro-5.0 allegro_image-5.0` 2> ErrOut/SpriteObjCompile.out

GraphicObject.o: GraphicObject.h GraphicObject.cpp
		g++ GraphicObject.cpp -c `pkg-config --libs allegro-5.0 allegro_image-5.0` 2> ErrOut/GraphicObjCompile.out
	
LevelObject.o: LevelObject.h LevelObject.cpp GraphicObject.o SpriteObject.o SPRITES.h
	g++ LevelObject.cpp -c -std=c++11 `pkg-config --libs allegro-5.0 allegro_image-5.0` 2> ErrOut/LevelObjCompile.out
	
Globals.o: Globals.h Globals.cpp
	g++ Globals.cpp -c 2> ErrOut/GlobalsCompile.out
	
ControllerObject.o: ControllerObject.h ControllerObject.cpp
	g++ ControllerObject.cpp -c 2> ErrOut/ControllerObjCompile.out `pkg-config --libs allegro-5.0 allegro_image-5.0` 2> ErrOut/ControllerObjCompile.out
	
PhysController.o: ControllerObject.h PhysController.h PhysController.cpp
	g++ PhysController.cpp -c 2> ErrOut/PhysControllerCompile.out `pkg-config --libs allegro-5.0 allegro_image-5.0` 2> ErrOut/PhysControllerCompile.out
	
SimpleController.o: ControllerObject.h SimpleController.h SimpleController.cpp
	g++ SimpleController.cpp -c 2> ErrOut/SimpleControllerCompile.out `pkg-config --libs allegro-5.0 allegro_image-5.0` 2> ErrOut/SimpleControllerCompile.out

AnimateMeQuick: SpriteObject.o GraphicObject.o LevelObject.o Globals.o GAMELIBS.h Main.cpp
	g++ Main.cpp SpriteObject.o GraphicObject.o LevelObject.o Globals.o -o AnimateMeQuick -std=c++11 -pthread -Wl,--no-as-needed `pkg-config --libs allegro-5.0 allegro_image-5.0` 2> ErrOut/Game.out
	
ControlMeQuick: SpriteObject.o GraphicObject.o LevelObject.o Globals.o ControllerObject.o SimpleController.o PhysController.o GAMELIBS.h Main.cpp
	g++ Main.cpp SpriteObject.o GraphicObject.o LevelObject.o Globals.o ControllerObject.o SimpleController.o PhysController.o -o AnimateMeQuick -std=c++11 -pthread -Wl,--no-as-needed `pkg-config --libs allegro-5.0 allegro_image-5.0` 2> ErrOut/Game.out
