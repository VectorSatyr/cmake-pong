#include "msdll/msdll.hpp"

clsTimer::clsTimer() : start_time(0), paused_time(0), paused(true) {};

void clsTimer::start() {
	start_time = SDL_GetTicks();
	if (paused) {
		start_time -= paused_time;
		paused_time = 0;
		paused = false;
	}
}

void clsTimer::stop() {
	paused_time = 0;
	paused = true;
}

void clsTimer::pause() {
	if (!paused) {
		paused_time = SDL_GetTicks() - start_time;
		paused = true;
	}
}

unsigned int clsTimer::time() {
	return (paused == true) ? paused_time : (SDL_GetTicks() - start_time);
}

bool clsTimer::is_stopped() {
	return paused;
}