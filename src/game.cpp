#include "game.hpp"
#include <cmath>

SDL_Rect const clsPong::WINDOW_RECT = { SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 320, 240 };

SDL_Rect const clsPong::BOARD_RECT = { 32, 24, 256, 192 };

SDL_Rect const clsPong::PLAYER1_RECT = { clsPong::BOARD_RECT.x, 88, 8, 64 };

SDL_Rect const clsPong::PLAYER2_RECT = { clsPong::BOARD_RECT.x + clsPong::BOARD_RECT.w - 8, 88, 8, 64 };

SDL_Rect const clsPong::TEXT_RECT_WINS = { clsPong::BOARD_RECT.x + 37, (clsPong::WINDOW_RECT.h / 2) - 11, 18, 23 };

SDL_Rect const clsPong::TEXT_RECT_LOSSES = { (clsPong::WINDOW_RECT.w / 2) + 37, (clsPong::WINDOW_RECT.h / 2) - 11, 18, 23 };

SDL_Color const clsPong::PLAYER1_COLOR = { 0, 0, 255, 255 };

SDL_Color const clsPong::PLAYER2_COLOR = { 255, 0, 0, 255 };

SDL_Color const clsPong::BALL_COLOR = { 0, 255, 0, 255 };

char const * const clsPong::WINDOW_TITLE = "PONG!";

clsPong::clsPong() : player1(PLAYER1_RECT), player2(PLAYER2_RECT), wins(0), losses(0), started(false) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) throw clsException();
	if (std::atexit(SDL_Quit) != 0) {
		SDL_Quit();
		throw clsException("Unable to register SDL_Quit!");
	}
}

bool clsPong::init() {
	// create rendering context
	window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_RECT.x, WINDOW_RECT.y, WINDOW_RECT.w, WINDOW_RECT.h, WINDOW_FLAGS);
	if (!window.is_valid()) return false;
	renderer = SDL_CreateRenderer(window, -1, RENDERER_FLAGS);
	if (!renderer.is_valid()) return false;

	// load images
	background = SDL_CreateTextureFromFile(renderer, "images/background.bmp");
	if (!background.is_valid()) return false;
	numbers = SDL_CreateTextureFromFile(renderer, "images/numbers.bmp");
	if (!numbers.is_valid()) return false;
	return true;
}

bool clsPong::update() {
	// game events
	events.update();
	if (events.close_button() || events.key_pressed(SDL_SCANCODE_ESCAPE)) return false;
	update_paddles();
	if (started) update_ball();

	// rendering
	SDL_RenderCopy(renderer, background, 0, 0);
	render_value(wins, 3, TEXT_RECT_WINS);
	render_value(losses, 3, TEXT_RECT_LOSSES);
	player1.render(renderer, PLAYER1_COLOR);
	player2.render(renderer, PLAYER2_COLOR);
	if (started) ball.render(renderer, BALL_COLOR);
	SDL_RenderPresent(renderer);
	return true;
}

void clsPong::update_paddles() {
	if (events.key_pressed(SDL_SCANCODE_RETURN) && started == false) {
		started = true;
		return;
	}
	if (events.key_down(SDL_SCANCODE_W)) player1.move_up(BOARD_RECT);
	if (events.key_down(SDL_SCANCODE_S)) player1.move_down(BOARD_RECT);
	if (events.key_down(SDL_SCANCODE_UP)) player2.move_up(BOARD_RECT);
	if (events.key_down(SDL_SCANCODE_DOWN)) player2.move_down(BOARD_RECT);
}

void clsPong::update_ball() {
	ball.move(BOARD_RECT);
	if (ball.passed_goal(BOARD_RECT) < 0) { // player 1 goal
		losses++;
		ball.reset();
		ball.reverse();
		started = false;
		return;
	}
	else if (ball.passed_goal(BOARD_RECT) > 0) { // player 2 goal
		wins++;
		ball.reset();
		started = false;
		return;
	}
	if (ball.collision(player1)) ball.bounce_from_paddle(player1);
	if (ball.collision(player2)) ball.bounce_from_paddle(player2);
}

void clsPong::render_value(unsigned int const value, unsigned int const total_digits, SDL_Rect const& rect, unsigned int const x_separation) {
	SDL_Rect source = { 0, 0, rect.w, rect.h };
	SDL_Rect dest = rect;
	for (unsigned int digit = 0; digit < total_digits; digit++, dest.x += dest.w) {
		source.x = ((value / (int)pow(10, total_digits - (digit + 1))) % 10) * (source.w + x_separation);
		SDL_RenderCopy(renderer, numbers, &source, &dest);
	}
}