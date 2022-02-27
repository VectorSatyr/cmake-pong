// credit to http://noobtuts.com/cpp/2d-pong-game
#include "game.hpp"

SDL_Rect const clsBall::starting_rect = { 152, 112, 8, 8 };

clsBall::clsBall() {
	reset();
}

void clsBall::reset() {
	copy(starting_rect);
	speed = starting_speed;
	xfactor = -1.0;
	yfactor = 0;
}

void clsBall::reverse() {
	xfactor = -xfactor;
}

void clsBall::move(SDL_Rect const& bounds) {
	// normalize speed
	double length = sqrt((xfactor * xfactor) + (yfactor * yfactor));
	if (length != 0.0) {
		length = 1.0 / length;
		xfactor *= length;
		yfactor *= length;
	}

	// apply speed
	x += speed * xfactor;
	y += speed * yfactor;

	// bounce from walls
	if (y < bounds.y) { // top wall
		y = bounds.y;
		yfactor = abs(yfactor);
	}
	double bottom = static_cast<double>(bounds.y) + bounds.h;
	if (y + h > bottom) { // bottom wall
		y = bottom - h;
		yfactor = -abs(yfactor);
	}
}

int clsBall::passed_goal(SDL_Rect const& bounds) const {
	double hw = w / 2.0;
	double bounds_hw = bounds.w / 2.0;
	return (collision(bounds)) ? 0 : ((x + hw) - (bounds.x + bounds_hw));
}

void clsBall::bounce_from_paddle(clsPaddle const& paddle) {
	SDL_Rect p = paddle.rect();
	xfactor = -xfactor;
	yfactor = ((y - p.y) / p.h) - 0.5;
	if (speed < speed_limit) {
		speed += 0.08f;
		if (speed > speed_limit) speed = speed_limit;
	}
}