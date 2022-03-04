#ifndef SDLCPP_LIBRARY_H
#define SDLCPP_LIBRARY_H
#include <unordered_map>
#include <memory>
#include <SDL.h>

SDL_Texture* _cdecl SDL_CreateTextureFromFile(SDL_Renderer*, char const*);

int _cdecl SDL_RenderCopy(SDL_Renderer*, SDL_Texture*, int const, int const);

namespace sdl2
{
	class window_delete
	{
	public:
		void operator()(SDL_Window* window) const
		{
			SDL_DestroyWindow(window);
		}
	};

	class renderer_delete
	{
	public:
		void operator()(SDL_Renderer* renderer) const
		{
			SDL_DestroyRenderer(renderer);
		}
	};

	class texture_delete
	{
	public:
		void operator()(SDL_Texture* texture) const
		{
			SDL_DestroyTexture(texture);
		}
	};

	using unique_window = std::unique_ptr<SDL_Window, window_delete>;
	using unique_renderer = std::unique_ptr<SDL_Renderer, renderer_delete>;
	using unique_texture = std::unique_ptr<SDL_Texture, texture_delete>;
}

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