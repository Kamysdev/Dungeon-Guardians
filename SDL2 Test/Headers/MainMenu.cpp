#include "MainMenu.h"

#define ESCAPE_GAME 10

enum LayerType
{
	MAIN_MENU,
	LOAD_MENU,
	SETINGS_MENU
};

SDL_Texture* PlayButton = NULL;
SDL_Texture* SetingsButton = NULL;
SDL_Texture* LoadButton = NULL;

int draw(SDL_Window* window, SDL_Surface* surface,
	LayerType layers, SetingsData setings, SDL_Renderer* ren)
{

	SDL_Rect coord{};
	coord.w = setings.width / 7.5;
	coord.h = setings.height / 8.43;

	if (layers == MAIN_MENU)
	{
		coord.x = setings.width / 6 - 128;
		coord.y = setings.height - 128 - 20;
		SDL_RenderCopy(ren, PlayButton, NULL, &coord);

		coord.x = setings.width / 3 - 128;
		coord.y = setings.height - 128 - 20;
		SDL_RenderCopy(ren, LoadButton, NULL, &coord);

		coord.x = setings.width / 2 - 128;
		coord.y = setings.height - 128 - 20;
		SDL_RenderCopy(ren, SetingsButton, NULL, &coord);

		coord.x = setings.width / 1.5 - 128;
		coord.y = setings.height - 128 - 20;
		SDL_RenderCopy(ren, SetingsButton, NULL, &coord);
	}
	else if (layers == SETINGS_MENU)
	{

	}

	SDL_RenderPresent(ren);
	SDL_RenderClear(ren);

	return EXIT_SUCCESS;
}

int menu_main(SDL_Window* window, SDL_Surface* surface, SDL_Renderer* ren)
{
	SDL_Event windowEvent;

	LayerType status = MAIN_MENU;
	SetingsData setings;

	SDL_Surface* temp_surface = SDL_LoadBMP("./Materials/GUI/PlayButton.bmp");
	PlayButton = SDL_CreateTextureFromSurface(ren, temp_surface);
	if (PlayButton == NULL)
	{
		return LOADERROR;
	}

	temp_surface = SDL_LoadBMP("./Materials/GUI/SetingsButton.bmp");
	SetingsButton = SDL_CreateTextureFromSurface(ren, temp_surface);
	if (SetingsButton == NULL)
	{
		return LOADERROR;
	}

	temp_surface = SDL_LoadBMP("./Materials/GUI/LoadButton.bmp");
	LoadButton = SDL_CreateTextureFromSurface(ren, temp_surface);
	if (LoadButton == NULL)
	{
		return LOADERROR;
	}


	while (true)
	{
		if (SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_QUIT)
			{
				return ESCAPE_GAME;
			}
			if (windowEvent.type == SDL_MOUSEBUTTONDOWN && status == MAIN_MENU)
			{
				if (windowEvent.button.x > setings.width / 6 - 128
					&& windowEvent.button.x < setings.width / 6 + 128
					&& windowEvent.button.y > setings.height - 128 - 20
					&& windowEvent.button.y < setings.height - 20)
				{
					return EXIT_SUCCESS;
				}

				if (windowEvent.button.x > setings.width / 3 - 128
					&& windowEvent.button.x < setings.width / 3 + 128
					&& windowEvent.button.y > setings.height - 128 - 20
					&& windowEvent.button.y < setings.height - 20)
				{
					status = MAIN_MENU;
				}

				if (windowEvent.button.x > setings.width / 2 - 128
					&& windowEvent.button.x < setings.width / 2 + 128
					&& windowEvent.button.y > setings.height - 128 - 20
					&& windowEvent.button.y < setings.height - 20)
				{
					status = LOAD_MENU;
				}
			}


			if (windowEvent.key.keysym.sym == SDLK_ESCAPE)
			{
				return ESCAPE_GAME;
			}
		}

		draw(window, surface, status, setings, ren);
	}

	return EXIT_SUCCESS;
}
