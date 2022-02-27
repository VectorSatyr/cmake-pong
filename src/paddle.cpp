#include "game.hpp"

double const clsPaddle::speed = 4;

clsPaddle::clsPaddle()
{
}

clsPaddle::clsPaddle(SDL_Rect const& other) :
	clsRect(other)
{
}

void clsPaddle::stay_in_bounds(SDL_Rect const& bounds) {
	double bottom = static_cast<double>(bounds.y) + bounds.h;
	if (y < bounds.y) y = bounds.y;
	if (y + h > bottom) y = bottom - h;
}

void clsPaddle::move_up(SDL_Rect const& bounds) {
	y += -abs(speed);
	stay_in_bounds(bounds);
}

void clsPaddle::move_down(SDL_Rect const& bounds) {
	y += abs(speed);
	stay_in_bounds(bounds);
}