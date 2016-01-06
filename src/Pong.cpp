#include "Window.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdexcept>
#include <cstring>
#include "GameState.h"
#include "PongMenu.h"
#include <stack>
#include <memory>

using std::runtime_error;
using std::pair;
using std::string;

//CONSTANTS
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int FRAMES_PER_SECOND = 60;

//GLOBAL VARIABLES
Window* gWindow;

void init() 
{
	//Initialize SDL
	if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
	{
		throw runtime_error( strcat( "SDL could not initialize! SDL error: ", SDL_GetError() ) );
	}

	//Initialize SDL_mixer
	if ( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
	{
		throw runtime_error( strcat( "SDL_mixer could not initialize! SDL_mixer error: ", Mix_GetError() ) );
	}

	//Initialize SDL_ttf
	if ( TTF_Init() == -1 )
	{
		throw runtime_error( strcat( "SDL_ttf could not initialize! SDL_ttf error: ", TTF_GetError() ) );
	}

	//Create window
	gWindow = new Window( WINDOW_WIDTH, WINDOW_HEIGHT );

	//Set window to fullscreen;
	//gWindow.fullscreen(true);	
}	
			
void close()
{
	delete gWindow;
	gWindow = NULL;

        //Quit SDL_mixer 
        Mix_Quit(); 
	TTF_Quit();
	SDL_Quit();
}

int main( int argc, char* argv[] )
{
	init();

	StateMachine state_machine;
	state_machine.push( std::shared_ptr<GameState>( new PongMenu( gWindow, &state_machine ) ) );
	long currentTime = SDL_GetTicks();

	while( !state_machine.empty() )
	{
		std::shared_ptr<GameState> currentState = state_machine.top();

		long deltaTime = SDL_GetTicks() - currentTime;
		currentTime += deltaTime;

		currentState->handle_input();
		currentState->update( deltaTime );
		currentState->draw();

		//cap frame rate
		if ( deltaTime < 1000 / FRAMES_PER_SECOND )
		{
			SDL_Delay( 1000 / FRAMES_PER_SECOND - deltaTime );
		}
	}

	close();

	return 0;
}
