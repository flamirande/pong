#include <SDL2/SDL.h>
#include "Window.h"
#include <stdexcept>
#include <cstring>

Window::Window( int width, int height )
{
	p_window_ = SDL_CreateWindow( NULL, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0 );
	if ( p_window_ == NULL )
	{
		throw std::runtime_error( strcat( "Could not create SDL window. SDL Error: ", SDL_GetError() ) );
	}

	width_ = width;
	height_ = height;
	
	p_renderer_ = SDL_CreateRenderer( p_window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	if ( p_renderer_ == NULL )
	{
		throw std::runtime_error( strcat( "Could not create SDL renderer. SDL Error: ", SDL_GetError() ) );
	}
}

void Window::free()
{
	SDL_DestroyRenderer( p_renderer_ );
	p_renderer_ = NULL;

	SDL_DestroyWindow( p_window_ );
	p_window_ = NULL;
}

void Window::fullscreen( bool fs )
{
	if ( fs && !fullscreen_ )
	{
		SDL_SetWindowFullscreen( p_window_, SDL_WINDOW_FULLSCREEN );
		SDL_ShowCursor( SDL_DISABLE );
		fullscreen_ = true;

		//Update width and height values
		SDL_DisplayMode mode;
		SDL_GetWindowDisplayMode( p_window_, &mode );
		width_ = mode.w;
		height_ = mode.h;
	}
	else if ( !fs && fullscreen_ )
	{
		SDL_SetWindowFullscreen( p_window_, 0 );
		SDL_ShowCursor( SDL_ENABLE );
		fullscreen_ = false;

		//Update width and height
		SDL_GetWindowSize( p_window_, &width_, &height_ );
	}
}

