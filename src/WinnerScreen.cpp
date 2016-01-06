#include "WinnerScreen.h"
#include "Window.h"
#include "GameState.h"
#include "Texture.h"
#include "MenuCommands.h"
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

const int TITLE_SIZE = 48;
const int TEXT_SIZE = 24;

WinnerScreen::WinnerScreen( Window* p_window, StateMachine* p_state_machine, std::string winning_player ): 
	p_window_( p_window ), GameState( p_state_machine ), winner_( p_window->renderer() ), winning_player_( winning_player )
{
	//Initialize titles
	SDL_Color text_color = { 0xFF, 0xFF, 0xFF, 0xFF };
	
	TTF_Font* title_font = TTF_OpenFont( "font/arcade_classic.ttf", TITLE_SIZE );
	std::string winner = winning_player_ + "  wins!";
	winner_.load_from_text( title_font, winner.c_str(), text_color );
	TTF_CloseFont( title_font );
	title_font = NULL;
	
	TTF_Font* text_font = TTF_OpenFont( "font/arcade_classic.ttf", TEXT_SIZE );
	instructions_.push_back( Texture( p_window_->renderer() ) );
	instructions_.push_back( Texture( p_window_->renderer() ) );
	instructions_[ 0 ].load_from_text( text_font, "Press space to return to menu.", text_color );
	instructions_[ 1 ].load_from_text( text_font, "Press escape to quit.", text_color );
	TTF_CloseFont( text_font );
	text_font = NULL;

	//Initialize input handler
	SDL_Event quit;
	quit.type = SDL_QUIT;
	input_handler_.add_input( quit, new QuitCommand( p_state_machine_ ) );

	SDL_Event escape;
	escape.type = SDL_KEYDOWN;
	escape.key.keysym.scancode = SDL_SCANCODE_ESCAPE;
	input_handler_.add_input( escape, new QuitCommand( p_state_machine_ ) );
	
	SDL_Event space;
	space.type = SDL_KEYDOWN;
	space.key.keysym.scancode = SDL_SCANCODE_SPACE;
	input_handler_.add_input( space, new ReturnToMenuCommand( p_state_machine_, p_window_ ) );
}

void WinnerScreen::handle_input()
{
	input_handler_.handle_input();
}

void WinnerScreen::update( long deltaTime )
{

}

void WinnerScreen::draw()
{
	SDL_Renderer* renderer = p_window_->renderer();

	//Clear screen
	SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );
	SDL_RenderClear( renderer );

	//Draw elements
	winner_.render( ( p_window_->width() - winner_.width() ) / 2, ( p_window_->height() / 2 ) - ( winner_.height() / 2 ) );
	instructions_[ 0 ].render( ( p_window_->width() - instructions_[ 0 ].width() ) / 2, ( 3 * p_window_->height() / 4 ) - ( ( instructions_[ 0 ].height() + instructions_[ 1 ].height() ) / 2 ) );
	instructions_[ 1 ].render( ( p_window_->width() - instructions_[ 1 ].width() ) / 2, ( 3 * p_window_->height() / 4 ) +  ( instructions_[ 0 ].height() / 2 ) - ( instructions_[ 1 ].height() / 2 ) );

	//Render
	SDL_RenderPresent( renderer );
}
