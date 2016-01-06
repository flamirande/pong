#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL.h>
#include "Subject.h"

class PongGame;

class Ball : public Subject
{
	//The dimensions of the paddle
	static const int BALL_HEIGHT = 20;
	static const int BALL_WIDTH = 20;
	static const int MAX_SPEED;
	static const int MIN_SPEED;
	static const double MAX_SPIN;
	
	public:
		Ball();

		void update( PongGame& game, long deltaTime );

		void draw( SDL_Renderer* renderer );

		void direction( double dir ) 
		{ 
			direction_ = dir;
			while ( direction_ >= 360 )
			{
				direction_ -= 360;
			}
			while ( direction_ < 0 )
			{
				direction_ += 360;
			}
	       	}

		void spin( int s ) { spin_ = s; }
		void setX( int x ) { posX_ = x; updateCollider(); }
		void setY( int y ) { posY_ = y; updateCollider(); }
		void speed( double s ) { speed_ = s; }

		int height() { return BALL_HEIGHT; }
		int width() { return BALL_WIDTH; }

	private:
		//The X and Y offsets of the paddle
		int posX_, posY_;

		//Ball direction angle in degrees
		double direction_;

		//Bounce about the normal vector (in degrees)
		void bounce_about( int normal_vector_direction );

		double speed_;
		void increase_speed( double factor );

		//Spin force, will affect direction every frame
		double spin_;

		//Modify spin
		void increase_spin( double factor );
		void erode_spin( double factor );

		//The paddle's collision box
		SDL_Rect collider_;

		//Update collider coordinates
		void updateCollider();
};

#endif
