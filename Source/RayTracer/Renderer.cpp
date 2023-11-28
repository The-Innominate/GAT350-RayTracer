#include "Renderer.h"
#include <iostream>


bool Renderer::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

void Renderer::Shutdown()
{
		//<if SDL window is not null, destroy SDL window>
		//<if SDL renderer is not null, destroy SDL renderer>
	if (m_window != nullptr) {
		SDL_DestroyWindow(m_window);
	}
	if (m_renderer != nullptr) {
		SDL_DestroyRenderer(m_renderer);
	}

		SDL_Quit();
}

bool Renderer::CreateWindow(const std::string& title, int width, int height)
{
	//m_window = <create SDL window(https://wiki.libsdl.org/SDL2/SDL_CreateWindow//Links to an external site.) >
	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
		if (!m_window)
		{
			std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
			SDL_Quit();
			return false;
		}

	//m_renderer = <create SDL renderer(https://wiki.libsdl.org/SDL2/SDL_CreateRenderer
	//Links to an external site.) use flags SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC>
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (!m_renderer)
		{
			std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
			return false;
		}

	return true;
}