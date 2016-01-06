#include "Ball.h"
#include "Collisions.h"
#include "PongGame.h"
#include "GameEvent.h"
#include "Window.h"
#include <cmath>

//number of degrees that the normal vector moves per unit of spin
static const int SPIN_BOUNCE_INFLUENCE = 10;
//erosion factors
static const double SPIN_EROSION = 0.005;
static const double SPEED_EROSION = 0.01;

const int Ball::MAX_SPEED = 20;
const int Ball::MIN_SPEED = 5;
const double Ball::MAX_SPIN = 2.5;

//Time for the ball to cross the screen from left to right
//if going straight and speed is 10.
const int CROSSING_TIME = 1000;

Ball::Ball(): posX_(0), posY_(0), direction_(0), speed_( 10 )
{
	collider_.w = BALL_WIDTH;
	collider_.h = BALL_HEIGHT;
	updateCollider();
}

void Ball::bounce_about( int normal_vector_direction )
{
	//Change normal vector according to spin
	int spin_normal = normal_vector_direction + spin_ * SPIN_BOUNCE_INFLUENCE;

	//Bounce about this normal
	direction( 2 * spin_normal - ( direction_ + 180 ) );
}

void Ball::increase_speed( double factor )
{
	speed_ += factor;
	if ( speed_ > MAX_SPEED )
	{
		speed_ = MAX_SPEED;
	}
	else if ( speed_ < MIN_SPEED )
	{
		speed_ = MIN_SPEED;
	}
}

void Ball::increase_spin( double factor )
{
	spin_ += factor;
	if ( spin_ > MAX_SPIN )
	{
		spin_ = MAX_SPIN;
	}
	else if ( spin_ < -MAX_SPIN )
	{
		spin_ = - MAX_SPIN;
	}
}

void Ball::erode_spin( double factor )
{
	if ( spin_ > 0 )
	{
		if ( spin_ > factor )
		{
			spin_ -= factor;
		}
		else
		{
			spin_ = 0;
		}
	}
	else
	{
		if ( spin_ < - factor )
		{
			spin_ += factor;
		}
		else
		{
			spin_ = 0;
		}
	}
}

void Ball::update( PongGame& game, long deltaTime )
{
	//Factor in spin
	direction( direction_ + spin_);

	increase_speed( - SPEED_EROSION );
	erode_spin( SPIN_EROSION );

	int displacement_ = game.window()->height() * ( speed_ / 10 ) * deltaTime / CROSSING_TIME;

	int velX = displacement_ * cos( direction_ * 2 * M_PI / 360 ) ;
	posX_ += velX;

	updateCollider();
	
	//Check X bounces
	if ( posX_ < 0 )
	{
		bounce_about( 0 );
		erode_spin( 0.5 );

		//Replace ball on other side of collision
		posX_ += 2 * ( 0 - posX_ );


		notify( GameEvent::RightScore );
	}
	else if ( posX_ + BALL_WIDTH > game.window()->width() )
	{
		bounce_about( 180 );
		erode_spin( 0.5 );

		//Replace ball on other side of collision
		posX_ += 2 * ( game.window()->width() - ( posX_ + BALL_WIDTH ) );

		notify( GameEvent::LeftScore );
	}
	//Left paddle collision
	else if ( direction_ > 90 && direction_ < 270 && checkCollision( collider_, game.left_paddle().collider() ) )
	{
		bounce_about( 0 );

		//Give forward inpetus
		if ( direction_ < 180 )
		{
			direction( direction_ / 2) ;
		}
		else
		{
			direction( direction_ + ( 360 - direction_ ) / 2 );
		}
		increase_speed( 0.15 * game.left_paddle().power() );

		erode_spin( 0.5 );

		//Add spin if paddle is moving
		increase_spin( game.left_paddle().velocity() == 0 ? 0 : ( game.left_paddle().velocity() > 0 ? - game.left_paddle().grip() : game.left_paddle().grip() ) / 10 );

		//Replace ball on other side of collision
		posX_ += 2 * ( game.left_paddle().x() + game.left_paddle().width() - posX_ );

		notify( GameEvent::PaddleCollision );
	}
	//Right paddle collision
	else if ( ( direction_ < 90 || direction_ > 270 ) && checkCollision( collider_, game.right_paddle().collider() ) )
	{
		bounce_about( 180 );

		//Give forward inpetus
		direction_ += ( 180 - direction_ ) / 2;
		increase_speed( 0.15 * game.right_paddle().power() );

		erode_spin( 0.5 );

		//Add spin if paddle is moving
		increase_spin( game.right_paddle().velocity() == 0 ? 0 : ( game.right_paddle().velocity() > 0 ? game.right_paddle().grip() : - game.right_paddle().grip() ) / 10 );

		//Bounce erodes spin
		spin_ = spin_ / 2;
		
		//Replace ball on other side of collision
		posX_ += 2 * ( game.right_paddle().x() - ( posX_ + BALL_WIDTH ) );

		notify( GameEvent::PaddleCollision );
	}

	int velY = displacement_ * sin( direction_ * 2 * M_PI / 360 );
	posY_ += velY;

	updateCollider();

	//Check Y bounces
	if ( posY_ < 0 )
	{
		bounce_about( 90 );
		erode_spin( 0.5 );

		//Replace ball on other side of collision
		posY_ += 2 * ( 0 - posY_ );

		notify( GameEvent::WallCollision );
	}
	else if ( posY_ + BALL_HEIGHT > game.window()->height() )
	{
		bounce_about( 270 );
		erode_spin( 0.5 );

		//Replace ball on other side of collision
		posY_ += 2 * ( game.window()->height() - ( posY_ + BALL_HEIGHT ) );

		notify( GameEvent::WallCollision );
	}

	updateCollider();
}

void Ball::draw( SDL_Renderer* renderer )
{
	SDL_Rect ball_rect = { posX_, posY_, BALL_WIDTH, BALL_HEIGHT };
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderFillRect( renderer, &ball_rect );
};

void Ball::updateCollider()
{
	collider_.x = posX_;
	collider_.y = posY_;
}
