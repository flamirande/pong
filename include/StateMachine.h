//Pushdown automaton state machine to be used with
//GameStates.

#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <utility>
#include <stack>

class GameState;

class StateMachine
{
	public:
		GameState* changeState( bool pop, GameState* state );
		GameState* changeState( std::pair< bool, Gamestate* > state_change )
		{
			return changeState( state_change.first, state_change.second );
		}

		GameState* currentState()
		{
			return states_.top();
		}

	private:
		std::stack<GameState*> states_;
};

#endif		
