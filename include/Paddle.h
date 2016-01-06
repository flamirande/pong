#ifndef PADDLE_H
#define PADDLE_H

#include <SDL2/SDL.h>

class PongGame;

class Paddle
{
	public:
		//The dimensions of the paddle
		static const int PADDLE_WIDTH = 20;

		Paddle( int size = 10, int max_speed = 10, int grip = 10, int power = 10 );

		void update( PongGame& game, long deltaTime );

		void draw( SDL_Renderer* renderer );

		void move_up() { velocity_ = - max_speed_; }
		void move_down() { velocity_ = max_speed_; }
		void stop() { velocity_ = 0; }
		int velocity() { return velocity_; }

		void setX( int x ) { posX_ = x; updateCollider(); }
		void setY( int y ) { posY_ = y; updateCollider(); }

		int x() { return posX_; }
		int y() { return posY_; }
		int height() { return size_; }
		int width() { return PADDLE_WIDTH; }
		int max_speed() { return max_speed_; }
		int power() { return power_; }
		int grip() { return grip_; }

		SDL_Rect collider() { return collider_; }
		
	private:
		//Paddle characteristics
		int size_;
		int max_speed_;
		int grip_;
		int power_;		
		
		//The X and Y offsets of the paddle
		int posX_, posY_;

		//Yt velocity
		int velocity_;

		//The paddle's collision box
		SDL_Rect collider_;

		//Update collider coordinates
		void updateCollider();
};

#endif
