#include "msdll/msdll.hpp"

clsRenderer::clsRenderer() : _renderer(NULL) {
}

clsRenderer::clsRenderer(SDL_Renderer* renderer) {
	_renderer = renderer;
}

clsRenderer::~clsRenderer() {
	if (_renderer != NULL) SDL_DestroyRenderer(_renderer);
}

clsRenderer& clsRenderer::operator=(SDL_Renderer* renderer) {
	if (_renderer == renderer) return *this;
	if (_renderer != NULL) SDL_DestroyRenderer(_renderer);
	_renderer = renderer;
	return *this;
}

clsRenderer::operator SDL_Renderer*() {
	return _renderer;
}

clsRenderer::operator SDL_Renderer const*() const {
	return _renderer;
}

bool clsRenderer::is_valid() const {
	return (_renderer != NULL);
}