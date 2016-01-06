#include "PongMenu.h"
#include "Window.h"
#include "GameState.h"
#include "Texture.h"
#include "MenuCommands.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

const int TITLE_SIZE = 96;
const int TEXT_SIZE = 24;

PongMenu::PongMenu( Window* p_window, StateMachine* p_state_machine ): p_window_( p_window ), GameState( p_state_machine ), title_( p_window->renderer() ), credits_( p_window->renderer() ), instructions_( p_window->renderer() )
{
	//Initialize titles
	SDL_Color text_color = { 0xFF, 0xFF, 0xFF, 0xFF };
	
	TTF_Font* title_font = TTF_OpenFont( "font/arcade_classic.ttf", TITLE_SIZE );
	title_.load_from_text( title_font, "Pong", text_color );
	TTF_CloseFont( title_font );
	title_font = NULL;
	
	TTF_Font* text_font = TTF_OpenFont( "font/arcade_classic.ttf", TEXT_SIZE );
	credits_.load_from_text( text_font, "par Francois Lamirande", text_color );
	instructions_.load_from_text( text_font, "Press space to start.", text_color );
	TTF_CloseFont( text_font );
	title_font = NULL;

	//Initialize input handler
	SDL_Event quit;
	quit.type = SDL_QUIT;
	input_handler_.add_input( quit, new QuitCommand( p_state_machine_ ) );

	SDL_Event space;
	space.type = SDL_KEYDOWN;
	space.key.keysym.scancode = SDL_SCANCODE_SPACE;
	input_handler_.add_input( space, new NewGameCommand( p_state_machine_, p_window_ ) );
}

void PongMenu::handle_input()
{
	input_handler_.handle_input();
}

void PongMenu::update( long deltaTime )
{

}

void PongMenu::draw()
{
	SDL_Renderer* renderer = p_window_->renderer();

	//Clear screen
	SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );
	SDL_RenderClear( renderer );

	//Draw elements
	title_.render( ( p_window_->width() - title_.width() ) / 2, ( p_window_->height() / 4 ) - ( title_.height() / 2 ) );
	credits_.render( ( p_window_->width() - credits_.width() ) / 2, ( p_window_->height() / 4 ) + ( title_.height() / 2 ) );
	instructions_.render( ( p_window_->width() - instructions_.width() ) / 2, ( 3 * p_window_->height() / 4 ) - ( instructions_.height() / 2 ) );

	//Render
	SDL_RenderPresent( renderer );
}
