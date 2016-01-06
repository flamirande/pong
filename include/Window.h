#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

class Window
{
	public:
		Window( int width, int height );

		//Deallocate internals
		void free();

		//Toggle fullscreen
		void fullscreen( bool fs );

		int width() { return width_; }
		int height() { return height_; }
		bool isFullscreen() { return fullscreen_; }
		SDL_Renderer* renderer() { return p_renderer_; }

	private:
		SDL_Window* p_window_;
		SDL_Renderer* p_renderer_;
		int width_, height_;
		bool fullscreen_;
};

#endif
