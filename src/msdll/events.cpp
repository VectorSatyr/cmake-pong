#include "msdll/msdll.hpp"

clsEvents::clsEvents() : quit(false), this_event() {
}

void clsEvents::update() {
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