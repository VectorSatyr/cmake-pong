#include "msdll/msdll.hpp"

clsTexture::clsTexture() : _texture(NULL) {
}

clsTexture::clsTexture(SDL_Texture* texture) {
	_texture = texture;
}

clsTexture::~clsTexture() {
	if (_texture != NULL) SDL_DestroyTexture(_texture);
}

clsTexture& clsTexture::operator=(SDL_Texture* texture) {
	if (_texture == texture) return *this;
	if (_texture != NULL) SDL_DestroyTexture(_texture);
	_texture = texture;
	return *this;
}

clsTexture::operator SDL_Texture*() {
	return _texture;
}

clsTexture::operator SDL_Texture*() const {
	return _texture;
}

bool clsTexture::is_valid() const {
	return (_texture != NULL);
}