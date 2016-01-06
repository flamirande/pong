#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Texture
{
	typedef unsigned int size_type;

	public:
		Texture( SDL_Renderer* p_renderer ): p_renderer_( p_renderer ), p_texture_( NULL ), width_( 0 ), height_( 0 ) { }
		~Texture();

		void load_from_file( const char* file );

		void load_from_text( TTF_Font* font, const char* text, SDL_Color text_color );
		void load_from_text( const char* font_file, int font_size, const char* text, SDL_Color text_color );

		void free();

		void render( int x, int y );

		size_type width() { return width_; }
		size_type height() { return height_; }

	private:
		SDL_Renderer* p_renderer_;
		SDL_Texture* p_texture_;
		size_type width_, height_;
};

#endif
