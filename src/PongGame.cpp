#include "PongGame.h"
#include "InputHandler.h"
#include <stack>
#include <list>
#include "Paddle.h"
#include "Ball.h"
#include "GameState.h"
#include "Window.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "GameEvent.h"
#include "SoundCue.h"
#include "PongCommands.h"
#include "ScoreSystem.h"
#include "Texture.h"
#include "WinnerScreen.h"
#include <iostream>
#include <exception>
#include <cstdlib>
#include <string>
#include <memory>

const int PongGame::START_DELAY = 250;
SDL_Color PongGame::text_color = { 0xFF, 0xFF, 0xFF, 0xFF };

enum { LEFT_PADDLE = 0, RIGHT_PADDLE = 1 };

void PongGame::init_input() 
{
	SDL_Event quit;
	quit.type = SDL_QUIT;
	inputHandler_.add_input( quit, new QuitCommand( p_state_machine_ ) );

	SDL_Event key_A_down, key_Z_down, key_K_down, key_M_down;
	SDL_Event key_A_up, key_Z_up, key_K_up, key_M_up;

	key_A_down.type = SDL_KEYDOWN;
	key_A_down.key.keysym.scancode = SDL_SCANCODE_A;
	inputHandler_.add_input( key_A_down, new UpCommand( &leftPaddle_ ) );

	key_A_up.type = SDL_KEYUP;
	key_A_up.key.keysym.scancode = SDL_SCANCODE_A;
	inputHandler_.add_input( key_A_up, new StopCommand( &leftPaddle_ ) );

	key_Z_down.type = SDL_KEYDOWN;
	key_Z_down.key.keysym.scancode = SDL_SCANCODE_Z;
	inputHandler_.add_input( key_Z_down, new DownCommand( &leftPaddle_ ) );

	key_Z_up.type = SDL_KEYUP;
	key_Z_up.key.keysym.scancode = SDL_SCANCODE_Z;
	inputHandler_.add_input( key_Z_up, new StopCommand( &leftPaddle_ ) );

	key_K_down.type = SDL_KEYDOWN;
	key_K_down.key.keysym.scancode = SDL_SCANCODE_K;
	inputHandler_.add_input( key_K_down, new UpCommand( &rightPaddle_ ) );

	key_K_up.type = SDL_KEYUP;
	key_K_up.key.keysym.scancode = SDL_SCANCODE_K;
	inputHandler_.add_input( key_K_up, new StopCommand( &rightPaddle_ ) );

	key_M_down.type = SDL_KEYDOWN;
	key_M_down.key.keysym.scancode = SDL_SCANCODE_M;
	inputHandler_.add_input( key_M_down, new DownCommand( &rightPaddle_ ) );

	key_M_up.type = SDL_KEYUP;
	key_M_up.key.keysym.scancode = SDL_SCANCODE_M;
	inputHandler_.add_input( key_M_up, new StopCommand( &rightPaddle_ ) );
}

void PongGame::set_ball()
{
	//Reset game clock
	game_time_ = 0;

	//Initialize ball position
	ball_.setX( ( p_window_->width() - ball_.width() ) / 2 );
	ball_.setY( ( p_window_->height() - ball_.height() ) / 2 );

	//Initialize ball direction between -60 and 60 degrees on each side
	ball_.direction( ( rand() % 2 ) * 180 + ( 30 - rand() % 60 ) );

	ball_.speed( 10 );
}

PongGame::PongGame( Window* p_window, StateMachine* p_state_machine ): p_window_( p_window ), GameState( p_state_machine ), game_time_( 0 )
       , score_system_( 11 ), left_score_texture_( p_window->renderer() ), right_score_texture_( p_window->renderer() )
       , leftPaddle_( 10, 10, 15, 5 ), rightPaddle_( 10, 10, 5, 15 )
{
	//Initialize input handler
	init_input();

	//Initialize score system
	score_system_.add_player( GameEvent::LeftScore );
	score_system_.add_player( GameEvent::RightScore );
	text_font = TTF_OpenFont( "font/arcade_classic.ttf", 60 );
	left_score_texture_.load_from_text( text_font, std::to_string( score_system_.score( 0 ) ).c_str(), text_color );
	right_score_texture_.load_from_text( text_font, std::to_string( score_system_.score( 1 ) ).c_str(), text_color );
	ball_.addObserver( &score_system_ );
	ball_.addObserver( this );
	score_system_.addObserver( this );

	//Initialize paddle position
	const int SIDE_BUFFER = 40;

	set_ball();

	leftPaddle_.setX( SIDE_BUFFER );
	leftPaddle_.setY( ( p_window_->height() - leftPaddle_.height() ) / 2 );

	rightPaddle_.setX( p_window_->width() - SIDE_BUFFER - rightPaddle_.width() );
	rightPaddle_.setY( ( p_window_->height() - leftPaddle_.height() ) / 2 );

	//Initialize sound cues
	try
	{
		soundCues_.push_back( new SoundCue( ball_, GameEvent::WallCollision, { "sound/pongblipa3.wav", "sound/pongblipa-3.wav", "sound/pongblipb3.wav", "sound/pongblipc-3.wav",
											"sound/pongblipd3.wav", "sound/pongblipd-3.wav", "sound/pongblipe3.wav", "sound/pongblipf3.wav",
											"sound/pongblipf-3.wav"} ) );
		soundCues_.push_back( new SoundCue( ball_, GameEvent::PaddleCollision, { "sound/pongblipa5.wav","sound/pongblipc5.wav", "sound/pongblipc-5.wav", "sound/pongblipd5.wav", 
											"sound/pongblipd-5.wav", "sound/pongblipe5.wav", "sound/pongblipf5.wav", "sound/pongblipf-5.wav"} ) );
	}
	catch ( std::exception& e )
	{
		std::cerr << e.what() << std::endl;
	}
}

PongGame::~PongGame()
{
	TTF_CloseFont( text_font );

	for ( std::list<SoundCue*>::iterator it = soundCues_.begin(); it != soundCues_.end(); ++it )
	{
		delete *it;
	}
}

void PongGame::handle_input()
{
	inputHandler_.handle_input();
}

void PongGame::update( long deltaTime )
{
	game_time_ += deltaTime;
	leftPaddle_.update( *this, deltaTime );
	rightPaddle_.update( *this, deltaTime );

	//Only move ball if START_DELAY has elapsed
	if ( game_time_ > START_DELAY )
	{
		ball_.update( *this, deltaTime );
	}
}

void PongGame::draw()
{
	SDL_Renderer* renderer = p_window_->renderer();

	//Clear screen
	SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );
	SDL_RenderClear( renderer );

	//Draw elemeents
	leftPaddle_.draw( renderer );
	rightPaddle_.draw( renderer );
	ball_.draw( renderer );
	
	//Draw vertical line
	for ( int i = 0; i != p_window_->height(); i += 4 )
	{
		SDL_RenderDrawPoint( renderer, p_window_->width() / 2, i );
	}

	//Draw scores
	left_score_texture_.render( 3 * p_window_->width() / 8 - left_score_texture_.width() / 2,  p_window_->height() / 20 );
	right_score_texture_.render( 5 * p_window_->width() / 8 - right_score_texture_.width() / 2,  p_window_->height() / 20 );

	//Render
	SDL_RenderPresent( renderer );
}

void PongGame::onNotify( GameEvent event )
{
	switch ( event )
	{
		case GameEvent::LeftScore:
			left_score_texture_.load_from_text( text_font, std::to_string( score_system_.score( 0 ) ).c_str(), text_color );
			set_ball();
			break;
		case GameEvent::RightScore:
			right_score_texture_.load_from_text( text_font, std::to_string( score_system_.score( 1 ) ).c_str(), text_color );
			set_ball();
			break;
		case GameEvent::WeHaveAWinner:
			std::string winner;
			if ( score_system_.score( LEFT_PADDLE ) == 11 )
			{
				winner = "Left player";
			}
			else
			{ 
				winner = "Right player";
			}
			p_state_machine_->pop();
			p_state_machine_->push( std::shared_ptr< GameState >( new WinnerScreen( p_window_, p_state_machine_, winner ) ) );
			break;
	}
}
