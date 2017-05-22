#include "cCharacter.h"

cCharacter::~cCharacter()
{
	free();
}

cCharacter::cCharacter()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

cCharacter::cCharacter(int _posX, int _posY)
{
	posX = _posX;
	posY = _posY;
}

void cCharacter::moveY(int dy)
{
	posY = posY + dy;
}


void cCharacter::jump()
{
	//SDL_TimerID timerIDChar = SDL_AddTimer(20,callbackChar, " 20 ms waited");
}