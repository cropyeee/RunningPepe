#ifndef FUNKCJE_H
#define FUNKCJE_H

#include "Scena.h"
#include "cCharacter.h"
#include "cClouds.h"
#include "LTexture.h"
//Starts up SDL and creates window
bool init(Scena &scena);

//Loads media
bool loadMedia(Scena &scena, LTexture &background, LTexture &police, cCharacter &character, cClouds &cloud);

//Frees media and shuts down SDL
void close(Scena &scena, LTexture &background, LTexture &police, cCharacter &character, cClouds &cloud);

static Uint32 gamelogic(Uint32 interval, void* param);

#endif