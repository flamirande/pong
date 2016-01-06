#ifndef PONG_GAME_H
#define PONG_GAME_H

#include "InputHandler.h"
#include "Paddle.h"
#include "Ball.h"
#include "GameState.h"
#include "ScoreSystem.h"
#include "Observer.h"
#include "Texture.h"
#include <stack>
#include <list>

class Window;
class SDL_Renderer;
class SoundCue;

class PongGame : public GameState, public Observer
{
	static SDL_Color text_color;

	//Amount of time to wait at start of game, in milliseconds
	static const int START_DELAY;

	public:
		PongGame( Window* p_window, StateMachine* p_state_machine );
		~PongGame();

		void handle_input();
		void update( long deltaTime );
		void draw();

		Window* window() { return p_window_; }
		Paddle& left_paddle() { return leftPaddle_; }
		Paddle& right_paddle() { return rightPaddle_; }
		Ball& ball() { return ball_; }

		void onNotify( GameEvent event );

	private:
		InputHandler inputHandler_;
		std::list<SoundCue*> soundCues_;
	
		ScoreSystem score_system_;
		Texture left_score_texture_, right_score_texture_;
		TTF_Font* text_font;

		long game_time_;

		Window* p_window_;

		Paddle leftPaddle_, rightPaddle_;
		Ball ball_;

		void init_input();
		void set_ball();
};

#endif
