//"Running Pepe" Created by Arkadiusz Mula
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <ctime>
#include "Scena.h"
#include "Funkcje.h"
//#include "LTexture.h"
//#include "cClouds.h"
//#include "cCharacter.h"



int main(int argc, char* args[])
{
	//Creating models;
	Scena scena;
	cCharacter character(0, 470);
	LTexture background(0,0);
	LTexture background2(1280,0);
	LTexture police(1120, 530);
	cClouds cloud(1000, 100);
	

	if (!init(scena)) //Start up SDL and create window
	{
		std::cout << "Failed to initialize!" << std::endl;
	}
	else
	{
		
		if (!loadMedia(scena,background,police,character,cloud,background2)) //Load media
		{
			std::cout << "Failed to load media!" << std::endl;
		}
		else
		{
			
			cClouds *cloud1 = new cClouds(600, 120,cloud.getTexture(),cloud.getWidth(),cloud.getHeight());
			cClouds *cloud2=new cClouds(205, 49, cloud.getTexture(),cloud.getWidth(),cloud.getHeight());
			cClouds *cloud3=new cClouds(1301, 30, cloud.getTexture(), cloud.getWidth(), cloud.getHeight());
			cClouds *cloud4 = new cClouds(1000, 100, cloud.getTexture(), cloud.getWidth(), cloud.getHeight());
			std::vector<cClouds*> vecClouds;
			vecClouds.push_back(cloud1);
			vecClouds.push_back(cloud2);
			vecClouds.push_back(cloud3);
			vecClouds.push_back(cloud4);
			bool quit = false; //Main loop flag
			scena.gamelogic();//game logic
			SDL_Event e; //Event handler
			while (!quit) // while application is running
			{
				
				while (SDL_PollEvent(&e) != 0)
				{
				if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					character.handleEvent(e); //klikniecie spacji
				}

				//Moving objects//
				character.jump();

				background.moveBackground();
				background2.moveBackground();
				police.movePolice();
				for (auto c : vecClouds)
					c->MoveClouds();
				//Collision detection//
				if (SDL_HasIntersection(character.getCollider(), police.getCollider()))
					std::cout << "Kolizja" << std::endl;
				//Start renderning//
				SDL_SetRenderDrawColor(scena.returnRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(scena.returnRenderer());
				background.render(scena);
				background2.render(scena);
				for (auto c:vecClouds)
				{
					c->render(scena);
				} 
				character.render(scena);
				police.render(scena);
				SDL_RenderPresent(scena.returnRenderer());
			}
			
			for (int i = 0; i < vecClouds.size(); i++)
				delete vecClouds[i];
		}
	}
	close(scena,background,police,character,cloud,background2);
	return 0;
}



// 1)Po dodaniu do wektora nie dzialaja funkcje
// 2)Przekazanie dodatkowych parametrów do callbacka (ogólnie gamelogic w SDL)
// 3)Problem ze skokiem(dziala tylko raz, stworzenie chwilowego zawisniecia)
// 4)Dlaczego samochod dziwnie przyspiesza