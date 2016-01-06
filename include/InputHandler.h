#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <list>
#include <utility>
#include <SDL2/SDL.h>
#include <stack>
#include <memory>

class Command;

class InputHandler
{
	public:
		//Create empty input map
		InputHandler() { }
		~InputHandler();

		InputHandler( std::list< std::pair< SDL_Event, Command* > > input_map ): input_map_( input_map ) { }

		void add_input( SDL_Event event, Command* p_command )
		{
			input_map_.push_back( std::make_pair( event, p_command ) );
		}

		void handle_input();

	private:
		std::list< std::pair< SDL_Event, Command* > > input_map_;
};

#endif
