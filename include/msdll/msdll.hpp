#ifndef SDLCPP_LIBRARY_H
#define SDLCPP_LIBRARY_H
#include <exception>
#include <unordered_map>
#include <SDL.h>

SDL_Texture* _cdecl SDL_CreateTextureFromFile(SDL_Renderer*, char const*);

int _cdecl SDL_RenderCopy(SDL_Renderer*, SDL_Texture*, int const, int const);

class clsException : public std::exception {
private:
	const char* message;

public:
	clsException();
	clsException(char const*);
	clsException& operator=(char const*);
	virtual ~clsException() noexcept;
	virtual char const* what() const throw();
};

class clsWindow {
private:
	SDL_Window* _window;
	clsWindow(clsWindow const&);

public:
	clsWindow();
	clsWindow(SDL_Window*);
	~clsWindow();
	clsWindow& operator=(SDL_Window*);
	operator SDL_Window*();
	operator SDL_Window const*() const;
	bool is_valid() const;
};

class clsRenderer {
private:
	SDL_Renderer* _renderer;
	clsRenderer(clsRenderer const&);

public:
	clsRenderer();
	clsRenderer(SDL_Renderer*);
	~clsRenderer();
	clsRenderer& operator=(SDL_Renderer*);
	operator SDL_Renderer*();
	operator SDL_Renderer const*() const;
	bool is_valid() const;
};

class clsTexture {
private:
	SDL_Texture* _texture;
	clsTexture(clsTexture const&);

public:
	clsTexture();
	clsTexture(SDL_Texture*);
	~clsTexture();
	clsTexture& operator=(SDL_Texture*);
	operator SDL_Texture*();
	operator SDL_Texture*() const;
	bool is_valid() const;
};

class clsTimer {
private:
	unsigned int start_time, paused_time;
	bool paused;

public:
	clsTimer();
	void start();
	void stop();
	void pause();
	unsigned int time();
	bool is_stopped();
};

class clsEvents {
private:
	static const unsigned total_mouse_buttons = 5;
	struct clsInput { bool current = false, previous = false; clsTimer duration; };
	std::unordered_map <SDL_Scancode, clsInput> scancodes;
	clsInput mouse_buttons[total_mouse_buttons];
	SDL_Event this_event;
	SDL_Point mouse;
	bool quit;

public:
	clsEvents();
	void update();
	bool close_button() const;
	bool key_down(SDL_Scancode const);
	bool key_pressed(SDL_Scancode const);
	bool key_released(SDL_Scancode const);
	bool key_repeat(SDL_Scancode const, unsigned int const);
	bool mouse_down(unsigned int const);
	bool mouse_pressed(unsigned int const);
	bool mouse_released(unsigned int const);
	bool mouse_repeat(unsigned int const, unsigned int const);
	int mouse_x() const;
	int mouse_y() const;
};

#endif