#include "LTexture.h"

LTexture::LTexture()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}



void LTexture::setX(double _posX)
{
	posX = _posX;
}

void LTexture::moveX(int dx)
{
	posX = posX + dx;
}

LTexture::LTexture(double _posX, double _posY)
{
	posX = _posX;
	posY = _posY;
}


LTexture::~LTexture()
{
	free();
}

double LTexture::getX()
{
	return posX;
}

double LTexture::getY()
{
	return posY;
}
bool LTexture::loadFromFile(std::string path, Scena &scena)
{
	free();

	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		std::cout << "Unable to load image " << IMG_GetError() << std::endl;
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 255, 255));

		newTexture = SDL_CreateTextureFromSurface(scena.returnRenderer(), loadedSurface);
		if (newTexture == NULL)
		{
			std::cout << "Unable to create texture" << SDL_GetError() << std::endl;
		}
		else
		{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
		posX = 0;
		posY = 0;
	}
}

void LTexture::render(Scena &scena)
{
	SDL_Rect renderQuad = { posX, posY, mWidth, mHeight };
	Collider = renderQuad;
	SDL_RenderCopy(scena.returnRenderer(), mTexture, NULL, &renderQuad);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

SDL_Texture* LTexture::getTexture()
{
	return mTexture;
}

Uint32 LTexture::PoliceMove(Uint32 interval, void*param)
{
	LTexture*self = reinterpret_cast<LTexture *>(param);
	self->movePolice();
	SDL_TimerID timerID = SDL_AddTimer(60, PoliceMove, self);
	return interval;
}

void LTexture::movePolice()
{
	
		if (posX < (-mWidth))
		posX = 1200;
		if (SDL_GetTicks()<8000)
			posX = posX - 0.2;
		if (SDL_GetTicks() < 11000&&SDL_GetTicks()>=8000)
			posX = posX - 0.3;
		if (SDL_GetTicks() < 14000&&SDL_GetTicks()>=11000)
			posX = posX - 0.4;
		if(SDL_GetTicks()>=14000)
			posX = posX - 0.0001*SDL_GetTicks();
		
}

SDL_Rect* LTexture::getCollider()
{
	return &Collider;
}

void LTexture::moveBackground()
{
	posX -= 0.1;
	if (posX < -mWidth)
		posX = 1280;
}