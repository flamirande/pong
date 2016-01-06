#ifndef SCORE_SYSTEM_H
#define SCORE_SYSTEM_H

#include <vector>
#include <list>
#include <stdexcept>
#include "GameEvent.h"

class ScoreSystem: public Observer, public Subject
{
	public:
		ScoreSystem( int score_limit = 0 ): score_limit_( score_limit ) { }

		//Tie a player to an event so that the player's score increases
		//by 1 every time the event happens.
		void tie_player_to_event( int player_index, GameEvent event )
		{
			if ( player_index >= events_.size() )
			{
				throw std::domain_error( "Player index out of range." );
			}
			else
			{
				events_[ player_index ].push_back( event );
			}
		}

		//Returns index of added player
		int add_player() { 
			scores_.push_back( 0 );
			events_.push_back( std::list< GameEvent >() );
			return scores_.size() - 1;
		}

		int add_player( GameEvent event ) {
			int index = add_player();
			tie_player_to_event( index, event );
			return index;
		}

		int score( int player ) { return scores_[ player ]; }

		void onNotify( GameEvent event )
		{
			for ( int i = 0; i != events_.size(); ++i )
			{
				for ( std::list< GameEvent >::iterator j = events_[ i ].begin(); j != events_[ i ].end(); ++j )
				{
					if ( event == *j )
					{
						if ( ++scores_[ i ] == score_limit_ )
						{
							notify( GameEvent::WeHaveAWinner );
						}	
					}
				}
			}
		}

	private:
		std::vector< int > scores_;
		std::vector< std::list< GameEvent > > events_;
		int score_limit_;
};

#endif
