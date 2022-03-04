#include "game.hpp"
#include <cmath>
#include <stdexcept>

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

clsPong::clsPong() : 
	player1(PLAYER1_RECT), player2(PLAYER2_RECT), 
	wins(0), losses(0), started(false)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		throw std::runtime_error(SDL_GetError());
	}
	if (std::atexit(SDL_Quit) != 0) {
		SDL_Quit();
		throw std::runtime_error("Unable to register SDL_Quit!");
	}
}

bool clsPong::init()
{
	// create rendering context
	window.reset(SDL_CreateWindow(
		WINDOW_TITLE, WINDOW_RECT.x, WINDOW_RECT.y, 
		WINDOW_RECT.w, WINDOW_RECT.h, WINDOW_FLAGS
	));
	if (!window) {
		return false;
	}
	renderer.reset(SDL_CreateRenderer(window.get(), -1, RENDERER_FLAGS));
	if (!renderer) {
		return false;
	}

	// load images
	background.reset(
		SDL_CreateTextureFromFile(renderer.get(), "images/background.bmp")
	);
	if (!background) {
		return false;
	}
	numbers.reset(
		SDL_CreateTextureFromFile(renderer.get(), "images/numbers.bmp")
	);
	if (!numbers) {
		return false;
	}
	return true;
}

bool clsPong::update()
{
	// game events
	events.update();
	if (events.close_button() || events.key_pressed(SDL_SCANCODE_ESCAPE)) {
		return false;
	}
	update_paddles();
	if (started) {
		update_ball();
	}

	// rendering
	auto target = renderer.get();
	SDL_RenderCopy(target, background.get(), 0, 0);
	render_value(wins, 3, TEXT_RECT_WINS);
	render_value(losses, 3, TEXT_RECT_LOSSES);
	player1.render(target, PLAYER1_COLOR);
	player2.render(target, PLAYER2_COLOR);
	if (started) {
		ball.render(target, BALL_COLOR);
	}
	SDL_RenderPresent(target);
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

void clsPong::render_value(
	unsigned int const value, unsigned int const total_digits, 
	SDL_Rect const& rect, unsigned int const x_separation
) 
{
	SDL_Rect source = { 0, 0, rect.w, rect.h };
	SDL_Rect dest = rect;
	auto target = renderer.get();
	auto image = numbers.get();
	int place;
	for (
		unsigned int digit = 0; 
		digit < total_digits; 
		digit++, dest.x += dest.w
		) {
		place = static_cast<int>(pow(10, total_digits - (digit + 1)));
		source.x = ((value / place) % 10) * (source.w + x_separation);
		SDL_RenderCopy(target, image, &source, &dest);
	}
}