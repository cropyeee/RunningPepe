#ifndef LTEXTURE_H
#define LTEXTURE_H


#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "Scena.h"

class Scena; // forward declaration???


class LTexture{
public:
	LTexture();
	LTexture(double _posX, double _posY);
	~LTexture();

	bool loadFromFile(std::string path, Scena &scena);

	void free();
	void moveX(int dx);
	void setX(double _posX);
	static Uint32 PoliceMove(Uint32 interval, void*param);
	void movePolice();
	void moveBackground();

	void render(Scena &scena);

	int getWidth();
	int getHeight();
	double getX();
	double getY();
	SDL_Rect* getCollider();
	SDL_Texture* getTexture();
protected:
	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;
	double posX;
	double posY;
	double VelY=0;
	SDL_Rect Collider;
	double posPoliceX;
};

#endif