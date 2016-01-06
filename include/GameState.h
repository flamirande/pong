//Game state to be used with state stack.

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <stack>
#include <memory>

class SDL_Renderer;
class GameState;

typedef std::stack< std::shared_ptr<GameState> > StateMachine;

class GameState
{
	public:
		GameState( StateMachine* p_state_machine ): p_state_machine_( p_state_machine ) { }
		virtual ~GameState() { }		

		virtual void handle_input() = 0;
		virtual void update( long deltaTime ) = 0;
		virtual void draw() = 0;
	protected:
		//Pointer to the state machine, in order to be able to change the game state
		StateMachine* p_state_machine_;

};

#endif
