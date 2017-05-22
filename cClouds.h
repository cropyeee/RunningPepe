#ifndef CCLOUDS_H
#define CCLOUDS_H

#include "LTexture.h"

class cClouds :public LTexture{
public:
	cClouds();
	cClouds(int _posX, int _posY);
	cClouds(int _posX, int _posY, SDL_Texture& _texture,int _width, int _height);
	static Uint32 movingClouds(Uint32 interval, void* param); //clouds callback
	~cClouds();
	void MoveClouds();
};
extern cClouds;

#endif