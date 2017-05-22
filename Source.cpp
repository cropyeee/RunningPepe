//"Running Pepe" Created by Arkadiusz Mula
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "Scena.h"
#include "LTexture.h"
#include "cClouds.h"
#include "cCharacter.h"
#include "Funkcje.h"

/*SDL_Texture* loadTexture(std::string path)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}*/


int main(int argc, char* args[])
{
	//Creating models;
	Scena scena;
	cCharacter character(0, 470);
	LTexture background;
	LTexture police(1120, 530);
	cClouds cloud(1000, 100);
	

	if (!init(scena)) //Start up SDL and create window
	{
		std::cout << "Failed to initialize!" << std::endl;
	}
	else
	{
		
		if (!loadMedia(scena,background,police,character,cloud)) //Load media
		{
			std::cout << "Failed to load media!" << std::endl;
		}
		else
		{
			cClouds cloud1(600, 120,*cloud.getTexture(),cloud.getWidth(),cloud.getHeight());
			cClouds cloud2(205, 49, *cloud.getTexture(),cloud.getWidth(),cloud.getHeight());
			/*std::vector<cClouds> vecClouds;
			vecClouds.push_back(cloud);
			vecClouds.push_back(cloud1);
			vecClouds.push_back(cloud2);*/
			bool quit = false; //Main loop flag
			SDL_Event e; //Event handler
			/*SDL_TimerID timerID = SDL_AddTimer(5, cClouds::movingClouds, &cloud);
			SDL_TimerID timerID1 = SDL_AddTimer(5, cClouds::movingClouds, &cloud1);
			SDL_TimerID timerID2 = SDL_AddTimer(5, cClouds::movingClouds, &cloud2);*/
			while (!quit) // while application is running
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					else if (e.type == SDL_KEYDOWN)
					{
						switch (e.key.keysym.sym)
						{
						case SDLK_SPACE:
						{
							character.jump();
							std::cout << SDL_GetTicks() << std::endl;
							break;
						}
						}
					}
				}


				police.movePolice(SDL_GetTicks());
				//Clear screen
				SDL_SetRenderDrawColor(scena.returnRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(scena.returnRenderer());

				background.render(0, 0,scena);
				cloud.render(cloud.getX(), cloud.getY(),scena);
				cloud1.render(cloud1.getX(), cloud1.getY(),scena);
				cloud2.render(cloud2.getX(), cloud2.getY(),scena);
				//renderowanie z wektora [!]
				/*for (std::vector<cClouds>::iterator it = vecClouds.begin(); it != vecClouds.end(); it++)
				{
					it->render(it->getX(), it->getY(), scena);
				}*/ 

				
				character.render(character.getX(), character.getY(),scena);
				police.render(police.getX(), police.getY(),scena);
				SDL_RenderPresent(scena.returnRenderer());

			}
			/*SDL_RemoveTimer(timerID);
			SDL_RemoveTimer(timerID1);*/
		}
	}
	close(scena,background,police,character,cloud);
	return 0;
}