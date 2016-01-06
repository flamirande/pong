#include <list>
#include <utility>
#include <SDL2/SDL.h>
#include "InputHandler.h"
#include "Command.h"

InputHandler::~InputHandler()
{
	for ( std::list< std::pair< SDL_Event, Command* > >::iterator it = input_map_.begin(); it != input_map_.end(); ++it )
	{
		delete it->second;
	}
}

void InputHandler::handle_input()
{
	SDL_Event input_event;

	while ( SDL_PollEvent( &input_event ) != 0 )
	{
		for ( std::list< std::pair< SDL_Event, Command* > >::iterator it = input_map_.begin(); it != input_map_.end(); ++it )
		{
			SDL_Event map_event = it->first;
			Command* map_command = it->second ;

			if ( input_event.type == map_event.type )
			{
				switch ( input_event.type )
				{
					case SDL_QUIT:
						map_command->execute();
						break;

					case SDL_KEYDOWN:
					case SDL_KEYUP:
						if ( input_event.key.keysym.scancode == map_event.key.keysym.scancode )
						{
							map_command->execute();
						}
						break;
				}
			}
		}
	}
}
