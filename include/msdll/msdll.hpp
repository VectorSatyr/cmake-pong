#ifndef SDLCPP_LIBRARY_H
#define SDLCPP_LIBRARY_H
#include <unordered_map>
#include <SDL.h>

SDL_Texture* _cdecl SDL_CreateTextureFromFile(SDL_Renderer*, char const*);

int _cdecl SDL_RenderCopy(SDL_Renderer*, SDL_Texture*, int const, int const);

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

class clsEvents {
private:
	struct clsInput { bool current = false, previous = false; };
	std::unordered_map <SDL_Scancode, clsInput> scancodes;
	SDL_Event this_event;
	bool quit;

public:
	clsEvents();
	void update();
	bool close_button() const;
	bool key_down(SDL_Scancode const);
	bool key_pressed(SDL_Scancode const);
};

#endif