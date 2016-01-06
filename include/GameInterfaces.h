#ifndef GAME_INTERFACES_H
#define GAME_INTERFACES_H

#include <SDL2/SDL.h>

class Drawable
{
	public:
		~Drawable() { }
		void draw( SDL_Renderer* renderer ) = 0;
}

class Inputable
{
	public:
		~Inputable() { }
		void handle_input( SDL_Event& event );
}

class Updateable
{
	public:
		~Updateable() { }
		void update();
}

#endif
