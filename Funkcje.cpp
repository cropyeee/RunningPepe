#include "Funkcje.h"

bool init(Scena &scena)
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)//
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window

		scena.createWindow();
		if (scena.returnWindow() == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			scena.createRenderer();
			if (scena.returnRenderer() == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(scena.returnRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize JPG loading
				int imgFlags = IMG_INIT_JPG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}


bool loadMedia(Scena &scena, LTexture &background, LTexture &police, cCharacter &character, cClouds &cloud, LTexture &background2)
{
	//Loading success flag
	bool success = true;

	//Load bacground
	if (!background.loadFromFile("droga1_modified_asd21.png", scena))
	{
		std::cout << "Failed to load background" << std::endl;
		success = false;
	}
	if (!background2.loadFromFile("droga1_modified_asd2_odbicie1.png",scena))
	{
		std::cout << "Failet to load background" << std::endl;
		success = false;
	}

	if (!character.loadFromFile("pepe_biegnaca_final1_alpha.png", scena))
	{
		std::cout << "Failed to load character" << std::endl;
		success = false;
	}
	if (!police.loadFromFile("police_modified1.png", scena))
	{
		std::cout << "Failed to load police car" << std::endl;
		success = false;
	}
	if (!cloud.loadFromFile("cloud_modified1.png", scena))
	{
		std::cout << "Failed to load cloud" << std::endl;
		success = false;
	}



	return success;
}



void close(Scena &scena, LTexture &background, LTexture &police, cCharacter &character, cClouds &cloud, LTexture &background2)
{
	//Free loaded image
	background.free();
	character.free();
	police.free();
	cloud.free();
	background2.free();


	//Destroy Window
	scena.destroyRenderer();
	scena.destroyWindow();

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

