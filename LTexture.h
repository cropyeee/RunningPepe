#ifndef LTEXTURE_H
#define LTEXTURE_H


#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "Scena.h"


class LTexture{
public:
	LTexture();
	LTexture(int _posX, int _posY);
	~LTexture();

	bool loadFromFile(std::string path, Scena &scena);

	void free();
	void moveX(int dx);
	void setX(int _posX);
	void movePolice(int time);

	void render(int x, int y, Scena &scena);

	int getWidth();
	int getHeight();
	int getX();
	int getY();
	SDL_Texture* getTexture();
protected:
	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;
	int posX;
	int posY;
	double posPoliceX;
};

#endif