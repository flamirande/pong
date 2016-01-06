#ifndef WINNER_SCREEN_H
#define WINNER_SCREEN_H

#include "GameState.h"
#include "InputHandler.h"
#include "Texture.h"
#include <vector>

class Window;

class WinnerScreen : public GameState
{
	public:
		WinnerScreen( Window* p_window, StateMachine* p_state_machine, std::string winning_player );
		~WinnerScreen() { }

		void handle_input();
		void update( long deltaTime );
		void draw();
	private:
		Window* p_window_;
		InputHandler input_handler_;

		std::string winning_player_;
		Texture winner_;
		std::vector< Texture > instructions_;
};

#endif
