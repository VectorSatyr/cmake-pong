#include "game.hpp"

clsRect::clsRect() :
	x(0.0), y(0.0), w(0.0), h(0.0)
{
}

clsRect::clsRect(SDL_Rect const& other) {
	copy(other);
}

clsRect::~clsRect()
{
}

clsRect& clsRect::operator=(SDL_Rect const& other) {
	if (!SDL_RectEquals(&rect(), &other)) copy(other);
	return *this;
}

void clsRect::copy(SDL_Rect const& other) {
	x = other.x;
	y = other.y;
	w = other.w;
	h = other.h;
}

bool clsRect::collision(clsRect const& other) const {
	return (SDL_HasIntersection(&rect(), &other.rect()) == SDL_TRUE);
}

void clsRect::render(SDL_Renderer* renderer, SDL_Color const& color) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &rect());
}