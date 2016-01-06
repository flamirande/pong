#include "Paddle.h"
#include "PongGame.h"
#include "Window.h"

//Time the paddle takes to move from the bottom of the screen to the top
const int CROSSING_TIME = 1000;

Paddle::Paddle( int size, int max_speed, int grip, int power ): size_( 10 * size ), max_speed_( max_speed ), grip_( grip ), power_( power ), posX_( 0 ), posY_( 0 ), velocity_( 0 )
{
	collider_.w = PADDLE_WIDTH;
	collider_.h = size_;
	updateCollider();
}

void Paddle::update( PongGame& game, long deltaTime )
{
	//If the paddle velocity is 10, we want to move across
	// the screen in CROSSING_TIME milliseconds.
	int displacement_ = game.window()->height() * ( velocity_ / 10 ) * deltaTime / CROSSING_TIME;
	
	posY_ += displacement_;
	
	//Check bounds
	if ( posY_ < 0 )
	{
		posY_ = 0;
	}
	if ( posY_ + size_ > game.window()->height() )
	{
		posY_ = game.window()->height() - size_;
	}

	updateCollider();
}

void Paddle::draw( SDL_Renderer* renderer )
{
	SDL_Rect paddle_rect = { posX_, posY_, PADDLE_WIDTH, size_ };
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderFillRect( renderer, &paddle_rect );
};

void Paddle::updateCollider()
{
	collider_.x = posX_;
	collider_.y = posY_;
}
