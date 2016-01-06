#include "Texture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <stdexcept>

Texture::~Texture()
{
	free();
}

void Texture::load_from_file( const char* file )
{
	//Get rid of existing texture
	free();

	SDL_Surface* loaded_surface = IMG_Load( file );
	if ( loaded_surface == NULL )
	{
		throw std::runtime_error( strcat( strcat( "Unable to load file ", file ), strcat( ". SDL_image Error: ", IMG_GetError() ) ) );
	}
		
	p_texture_ = SDL_CreateTextureFromSurface( p_renderer_, loaded_surface );
	if ( p_texture_ == NULL )
	{
		throw std::runtime_error( strcat( strcat( "Unable to load create texture from ", file ), strcat( ". SDL Error: ", SDL_GetError() ) ) );
	}

	width_ = loaded_surface->w;
	height_ = loaded_surface->h;

	SDL_FreeSurface( loaded_surface );
}

void Texture::load_from_text( TTF_Font* font, const char* text, SDL_Color text_color )
{
	//Get rid of existing texture
	free();

	SDL_Surface* loaded_surface = TTF_RenderText_Solid( font, text, text_color );
	if ( loaded_surface == NULL )
	{
		throw std::runtime_error( strcat( "Unable to render text surface. SDL_ttf Error: ", TTF_GetError() ) );
	}

	p_texture_ = SDL_CreateTextureFromSurface( p_renderer_, loaded_surface );
	if ( p_texture_ == NULL )
	{
		throw std::runtime_error( strcat( "Unable to load create texture from text. SDL Error: ", SDL_GetError() ) );
	}

	width_ = loaded_surface->w;
	height_ = loaded_surface->h;

	SDL_FreeSurface( loaded_surface );
}

void Texture::load_from_text( const char* font_file, int font_size, const char* text, SDL_Color text_color )
{
	TTF_Font* font = TTF_OpenFont( font_file, font_size );
	if ( font == NULL )
	{
		throw std::runtime_error( strcat( strcat( "Unable to load font ", font_file ), strcat( ". SDL_ttf Error: ", TTF_GetError() ) ) );
	}

	load_from_text( font, text, text_color );

	TTF_CloseFont( font );
	font = NULL;
}

void Texture::free()
{
	if ( p_texture_ != NULL )
	{
		SDL_DestroyTexture( p_texture_ );
		p_texture_ = NULL;
		width_ = 0;
		height_ = 0;
	}
}

void Texture::render( int x, int y )
{
	SDL_Rect render_rect = { x, y, width_, height_ };
	SDL_RenderCopy( p_renderer_, p_texture_, NULL, &render_rect );
}
