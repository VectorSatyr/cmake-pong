#ifndef PONG_GAME_H
#define PONG_GAME_H
#include "msdll/msdll.hpp"

class clsRect {
protected:
	double x, y, w, h;
	void copy(SDL_Rect const&);

public:
	clsRect();
	clsRect(SDL_Rect const&);
	virtual	~clsRect();
	clsRect& operator=(SDL_Rect const&);
	void render(SDL_Renderer*, SDL_Color const&);
	bool collision(clsRect const&) const;
	inline SDL_Rect const rect() const {
		return { (int)x, (int)y, (int)w, (int)h };
	};

};

class clsPaddle : public clsRect {
private:
	static double const speed;
	void stay_in_bounds(SDL_Rect const&);

public:
	clsPaddle();
	clsPaddle(SDL_Rect const&);
	void move_up(SDL_Rect const&);
	void move_down(SDL_Rect const&);
};

class clsBall : public clsRect {
private:
	static SDL_Rect const starting_rect;
	static unsigned int const starting_speed = 2;
	static unsigned int const speed_limit = 8;
	double speed, xfactor, yfactor;

public:
	clsBall();
	void reset();
	void reverse();
	void move(SDL_Rect const&);
	int passed_goal(SDL_Rect const&) const;
	void bounce_from_paddle(clsPaddle const&);
};

class clsPong {
private:
	static SDL_Rect const WINDOW_RECT, BOARD_RECT, PLAYER1_RECT, PLAYER2_RECT, TEXT_RECT_WINS, TEXT_RECT_LOSSES;
	static SDL_Color const PLAYER1_COLOR, PLAYER2_COLOR, BALL_COLOR;
	static char const * const WINDOW_TITLE;
	unsigned int const WINDOW_FLAGS = SDL_WINDOW_SHOWN;
	unsigned int const RENDERER_FLAGS = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	unsigned int const SCORE_LIMIT = 999;
	unsigned char const TOTAL_SCORE_DIGITS = 3;
	clsWindow window;
	clsRenderer renderer;
	clsTexture background, numbers;
	clsEvents events;
	clsPaddle player1, player2;
	clsBall ball;
	unsigned short wins, losses;
	bool started;
	clsPong(clsPong const&);
	void update_paddles();
	void update_ball();
	void render_value(unsigned int const, unsigned int const, SDL_Rect const&, unsigned int const = 1);

public:
	clsPong();
	bool init();
	bool update();
};

#endif