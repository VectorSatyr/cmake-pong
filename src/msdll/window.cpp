#include "msdll/msdll.hpp"

clsWindow::clsWindow() : _window(NULL) {
}

clsWindow::clsWindow(SDL_Window* window) : _window(window) {
}

clsWindow::~clsWindow() {
	if (_window != NULL) SDL_DestroyWindow(_window);
}

clsWindow& clsWindow::operator=(SDL_Window* window) {
	if (_window == window) return *this;
	if (_window != NULL) SDL_DestroyWindow(_window);
	_window = window;
	return *this;
}

clsWindow::operator SDL_Window*() {
	return _window;
}

clsWindow::operator SDL_Window const*() const {
	return _window;
}

bool clsWindow::is_valid() const {
	return (_window != NULL);
}