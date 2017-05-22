#include "cClouds.h"

cClouds::cClouds()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}
cClouds::cClouds(int _posX, int _posY)
{
	posX = _posX;
	posY = _posY;
}

cClouds::~cClouds()
{
	free();
}
Uint32 cClouds::movingClouds(Uint32 interval, void* param)
{
	/*if (cloud.getX() < (-cloud.getWidth()))
	{
		cloud.setX((cloud.getWidth() + 1280 + 600));
	}
	//cloud.moveX(-3);*/
	/*if (posX < -mWidth)
		posX = mWidth + 1280 + 600;
	posX = posX - 3;
	SDL_TimerID timerID = SDL_AddTimer(20, movingClouds);*/
	cClouds *self = reinterpret_cast<cClouds *>(param);
	self->MoveClouds();
	SDL_TimerID timerID = SDL_AddTimer(20, movingClouds,self);
	return 0;
}

void cClouds::MoveClouds()
{
	posX = posX - 3;
	if (posX < -(1280))
		posX = 1280;
	
}

cClouds::cClouds(int _posX, int _posY, SDL_Texture& _texture, int _width, int _height)
{
	posX = _posX;
	posY = _posY;
	mTexture = &_texture;
	mWidth = _width;
	mHeight = _height;

}