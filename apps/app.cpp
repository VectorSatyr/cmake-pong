#include "game.hpp"

int SDL_main(int argc, char** args)
{
	try
	{
		clsPong game;
		if (!game.init()) return -1;
		while (1) if (!game.update()) break;
	}
	catch (std::exception const& error) { SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Exception: ", error.what(), NULL); }
	return 0;
}