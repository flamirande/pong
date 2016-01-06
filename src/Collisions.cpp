#include <SDL2/SDL.h>

bool checkCollision( const SDL_Rect& a, const SDL_Rect& b )
{
	int leftA = a.x;
	int rightA = a.x + a.w;
	int topA = a.y;
	int bottomA = a.y + a.h;

	int leftB = b.x;
	int rightB = b.x + b.w;
	int topB = b.y;
	int bottomB = b.y + b.h;

	if ( leftA > rightB || rightA < leftB || topA > bottomB || bottomA < topB )
	{
		return false;
	}
	else
	{
		return true;
	}
}
