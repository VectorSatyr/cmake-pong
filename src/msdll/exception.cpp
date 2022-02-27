#include "msdll/msdll.hpp"

clsException::clsException() : exception(), message(SDL_GetError()) {
}

clsException::clsException(char const* text) : exception(), message(text) {
}

clsException& clsException::operator=(char const* text) {
	message = text;
	return *this;
}

clsException::~clsException() noexcept {
}

char const* clsException::what() const throw() {
	return message;
}