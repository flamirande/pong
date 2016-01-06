#ifndef PONG_MENU_H
#define PONG_MENU_H

#include "GameState.h"
#include "InputHandler.h"
#include "Texture.h"

class Window;

class PongMenu : public GameState
{
	public:
		PongMenu( Window* p_window, StateMachine* p_state_machine );
		~PongMenu() { }

		void handle_input();
		void update( long deltaTime );
		void draw();
	private:
		Window* p_window_;
		InputHandler input_handler_;

		Texture title_, credits_, instructions_;
};

#endif
