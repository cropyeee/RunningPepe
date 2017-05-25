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

cCharacter::cCharacter(double _posX, double _posY)
{
	posX = _posX;
	posY = _posY;
}




/*Uint32 cCharacter::charJump(Uint32 interval, void* param)
{
	cCharacter*self = reinterpret_cast<cCharacter *>(param);
	if (self->returnUp() == true)
		self->jump();
	else
		self->fall();
	if (self->returnDown() == false && self->returnUp() == false)
		return 0;
	self->jump();
	//SDL_TimerID timerID = SDL_AddTimer(5, charJump,self);
	return interval;
}*/

bool cCharacter::returnUp()
{
	return up;
}
bool cCharacter::returnDown()
{
	return down;
}
void cCharacter::changeUp()
{
	if (up == true)
		up = false;
	else
		up = true;
}
void cCharacter::changeDown()
{
	if (down == true)
		down = false;
	else down = true;
}

void cCharacter::handleEvent(SDL_Event& e)
{
	
	/*if (e.type == SDL_KEYDOWN&&e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_SPACE: VelY += -5; break;
		}
	}*/
	if (e.type == SDL_KEYDOWN&&e.key.repeat==0)
	{
			if (e.key.keysym.sym == SDLK_SPACE)
			{
				VelY = -5;
			}
	}
}

void cCharacter::jump()
{		
	if (down == false)
	{
		posY += VelY;
		if (posY < 130)
		{
			posY = 130;
			down = true;
		}
	}
	if (down == true)
	{
		posY += -VelY;
		if (posY > 470)
		{
			posY = 470;
			VelY = 0;
			down == false;
		}
	}
}

void cCharacter::fall()
{
	if (posY > 470)
	{
		posY = posY;
		up = false;
		down = false;
		VelY = 0;
	}
	else posY += -VelY;
}