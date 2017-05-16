/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>



const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

class LTexture{
public:
	LTexture();
	LTexture(int _posX, int _posY);
	~LTexture();

	bool loadFromFile(std::string path);

	void free();
	void moveX(int dx);
	void setX(int _posX);

	void render(int x, int y);

	int getWidth();
	int getHeight();
	int getX();
	int getY();
private:
	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;
	int posX;
	int posY;
};

//The window we'll be rendering to
SDL_Window* gWindow=NULL;

//The window renderer
SDL_Renderer* gRenderer=NULL;

/*Current displayed texture
SDL_Texture* background=NULL;*/

LTexture character;
LTexture background;
LTexture police;
LTexture cloud(1000,100);

/*Loads individual image as texture
SDL_Texture* loadTexture(std::string path);*/

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

Uint32 callback(Uint32 interval, void* param);

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
bool LTexture::loadFromFile(std::string path)
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

		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
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
	}
}

void LTexture::render(int x, int y)
{
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) < 0)//
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("Running Pepe!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize JPG loading
				int imgFlags = IMG_INIT_JPG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}


bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load bacground
	if (!background.loadFromFile("droga1_modified.jpg"))
	{
		std::cout << "Failed to load background" << std::endl;
		success = false;
	}

	if (!character.loadFromFile("pepe_biegnaca_final.bmp"))
	{
		std::cout << "Failed to load character" << std::endl;
		success = false;
	}
	if (!police.loadFromFile("police_modified.png"))
	{
		std::cout << "Failed to load police car" << std::endl;
		success = false;
	}
	if (!cloud.loadFromFile("cloud_modified.png"))
	{
		std::cout << "Failed to load cloud" << std::endl;
		success = false;
	}

	

	return success;
}

Uint32 callback(Uint32 interval, void* param)
{
	if (cloud.getX() < (-cloud.getWidth()))
	{
		cloud.setX((cloud.getWidth()+SCREEN_WIDTH+600));
	}
	cloud.moveX(-3);
	SDL_TimerID timerID = SDL_AddTimer(20, callback, " 20 ms waited");
	return 0;

}

void close()
{
	//Free loaded image
	background.free();
	character.free();
	police.free();
	cloud.free();
	

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

/*SDL_Texture* loadTexture(std::string path)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}*/


int main(int argc, char* args[])
{
	if (!init()) //Start up SDL and create window
	{
		std::cout << "Failed to initialize!" << std::endl;
	}
	else
	{
		
		if (!loadMedia()) //Load media
		{
			std::cout << "Failed to load media!" << std::endl;
		}
		else
		{
			bool quit = false; //Main loop flag
			SDL_Event e; //Event handler
			SDL_TimerID timerID = SDL_AddTimer(20, callback, " 20 ms waited");
			while (!quit) // while application is running
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
				}
				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				background.render(0, 0);
				cloud.render(cloud.getX(), cloud.getY());
				cloud.render(cloud.getX()-400, cloud.getY()+20);
				cloud.render(cloud.getX()-846, cloud.getY()-51);
				/*for (int i = 0; i < 200;i++)//????
				{
					cloud.render(0+i, 100);
					cloud.render(420+i, 137);
					cloud.render(800+i, 70);
					std::cout << "Przesunieto" << std::endl;
				}*/
				character.render(0, 420);
				police.render(1000, 500);
				SDL_RenderPresent(gRenderer);

			}
			SDL_RemoveTimer(timerID);
		}
	}
	close();
	return 0;
}