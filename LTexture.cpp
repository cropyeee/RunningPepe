#include "LTexture.h"

LTexture::LTexture()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}



void LTexture::setX(int _posX)
{
	posX = _posX;
}

void LTexture::moveX(int dx)
{
	posX = posX + dx;
}

LTexture::LTexture(int _posX, int _posY)
{
	posX = _posX;
	posY = _posY;
}


LTexture::~LTexture()
{
	free();
}

int LTexture::getX()
{
	return posX;
}

int LTexture::getY()
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

void LTexture::render(int x, int y, Scena &scena)
{
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
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

void LTexture::movePolice(int time)
{
	posX = posX - 1;
	if (posX < (-mWidth))
		posX = 1200;
}