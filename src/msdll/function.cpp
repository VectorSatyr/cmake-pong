#include "msdll/msdll.hpp"

SDL_Texture* _cdecl SDL_CreateTextureFromFile(SDL_Renderer* renderer, char const* filename) {
	SDL_Surface* bitmap = SDL_LoadBMP(filename);
	if (bitmap == NULL) return NULL;
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, bitmap);
	SDL_FreeSurface(bitmap);
	return texture;
}

int _cdecl SDL_RenderCopy(SDL_Renderer* renderer, SDL_Texture* texture, int const x, int const y) {
	SDL_Rect dest = { x, y, 1, 1 };
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	return SDL_RenderCopy(renderer, texture, NULL, &dest);
}