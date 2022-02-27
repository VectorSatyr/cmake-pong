#include "msdll/msdll.hpp"

clsEvents::clsEvents() : quit(false), this_event(), mouse() {
}

void clsEvents::update() {
	// update mouse codes
	for (unsigned button = 0; button < total_mouse_buttons; button++) {
		mouse_buttons[button].previous = mouse_buttons[button].current;
	}

	// update obtained scancodes
	if (!scancodes.empty()) {
		auto iterator = scancodes.begin();
		while (iterator != scancodes.end()) {
			iterator->second.previous = iterator->second.current; // update input data
			if (!(iterator->second.current && iterator->second.previous)) {
				iterator = scancodes.erase(iterator); // remove idle inputs
			}
			else {
				iterator++;
			}
		}
	}

	// poll events
	SDL_Scancode code;
	uint8_t button;
	while (SDL_PollEvent(&this_event)) {
		switch (this_event.type) {
		case SDL_QUIT: // close button
			quit = true;
			break;

		case SDL_KEYDOWN:
		case SDL_KEYUP: // keyboard input
			code = this_event.key.keysym.scancode;
			if (scancodes.count(code) < 1) {
				// add scancode
				clsInput input;
				scancodes[code] = input;
			}
			scancodes[code].current = (this_event.type == SDL_KEYDOWN);
			if (scancodes[code].current && !scancodes[code].previous) scancodes[code].duration.start();
			if (!scancodes[code].current && scancodes[code].previous) scancodes[code].duration.stop();
			break;

		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP: // mouse input
			button = this_event.button.button;
			mouse_buttons[button].current = (this_event.type == SDL_MOUSEBUTTONDOWN);
			if (mouse_buttons[button].current && !mouse_buttons[button].previous) mouse_buttons[button].duration.start();
			if (!mouse_buttons[button].current && mouse_buttons[button].previous) mouse_buttons[button].duration.stop();
			mouse.x = this_event.button.x;
			mouse.y = this_event.button.y;
			break;

		case SDL_MOUSEMOTION: // mouse movement
			mouse.x = this_event.motion.x;
			mouse.y = this_event.motion.y;
			break;
		}
	}
}

bool clsEvents::close_button() const {
	return quit;
}

bool clsEvents::key_down(SDL_Scancode const code) {
	if (scancodes.count(code) < 1) return false;
	return scancodes[code].current;
}

bool clsEvents::key_pressed(SDL_Scancode const code) {
	if (scancodes.count(code) < 1) return false;
	return (scancodes[code].current && !scancodes[code].previous);
}

bool clsEvents::key_released(SDL_Scancode const code) {
	if (scancodes.count(code) < 1) return false;
	return (!scancodes[code].current && scancodes[code].previous);
}

bool clsEvents::key_repeat(SDL_Scancode const code, unsigned int const delay) {
	if (scancodes.count(code) < 1) return false;
	return (scancodes[code].duration.time() >= delay);
}

bool clsEvents::mouse_down(unsigned int const button) {
	return mouse_buttons[button].current;
}

bool clsEvents::mouse_pressed(unsigned int const button) {
	return (mouse_buttons[button].current && !mouse_buttons[button].previous);
}

bool clsEvents::mouse_released(unsigned int const button) {
	return (!mouse_buttons[button].current && mouse_buttons[button].previous);
}

bool clsEvents::mouse_repeat(unsigned int const button, unsigned int const delay) {
	return mouse_down(button) && (mouse_buttons[button].duration.time() >= delay);
}

int clsEvents::mouse_x() const {
	return mouse.x;
}

int clsEvents::mouse_y() const {
	return mouse.y;
}