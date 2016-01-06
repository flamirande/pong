#ifndef SOUND_CUE_H
#define SOUND_CUE_H

#include <SDL2/SDL_mixer.h>
#include "GameEvent.h"
#include "Observer.h"
#include "Subject.h"
#include <stdexcept>
#include <cstring>
#include <list>
#include <vector>
#include <memory>
#include <cstdlib>

class SoundCue : public Observer
{
	public:
		//Create a sound cue from an event and a WAV file
		SoundCue( Subject& subject, GameEvent event, std::list< const char* > sound_files ): event_( event )
		{
			subject.addObserver( this );

			for ( std::list< const char* >::iterator it = sound_files.begin(); it != sound_files.end(); ++it )
			{
				Mix_Chunk* sound = Mix_LoadWAV( *it );
				if ( sound == NULL )
				{
					throw std::runtime_error( strcat( strcat( "Could not load sound file ", *it ), strcat( ". SDL_mixer error: ", Mix_GetError() ) ) );
				}
				sounds_.push_back( std::unique_ptr< Mix_Chunk >( sound ) );
			}
		}


		~SoundCue()
		{
			for ( std::vector< std::unique_ptr< Mix_Chunk > >::iterator it = sounds_.begin(); it != sounds_.end(); ++it)
			{
				Mix_FreeChunk( it->release() );
			}
		}

		void onNotify( GameEvent event )
		{
			if ( event == event_ )
			{
				int random_index = std::rand() % sounds_.size();
				Mix_PlayChannel( -1, sounds_[ random_index ].get(), 0 );
			}
		}


	private:
		GameEvent event_;
		std::vector< std::unique_ptr< Mix_Chunk > > sounds_;
};

#endif
