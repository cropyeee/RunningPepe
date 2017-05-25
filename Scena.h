#ifndef SCENA_H
#define SCENA_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "LTexture.h"
#include "cClouds.h"
#include "cCharacter.h"



class Scena{
public:
	Scena();
	~Scena();
	SDL_Renderer* returnRenderer();
	SDL_Window* returnWindow();
	void createWindow();
	void createRenderer();
	void destroyWindow();
	void gamelogic();
	void destroyRenderer();
	int returnScreenWidth();
	int returnScreenHeight();
protected:
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;
	SDL_Renderer* gRenderer;
	SDL_Window* gWindow;
};
#endif

