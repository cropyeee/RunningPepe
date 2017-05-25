#ifndef FUNKCJE_H
#define FUNKCJE_H

#include "Scena.h"
class Scena;//forward declaration
class LTexture;//forward declaration	
class cCharacter;//forward decalaration
class cClouds;// forward decalaration
//#include "cCharacter.h"
//#include "cClouds.h"
//#include "LTexture.h"
//Starts up SDL and creates window
bool init(Scena &scena);

//Loads media
bool loadMedia(Scena &scena, LTexture &background, LTexture &police, cCharacter &character, cClouds &cloud,LTexture &background2);

//Frees media and shuts down SDL
void close(Scena &scena, LTexture &background, LTexture &police, cCharacter &character, cClouds &cloud, LTexture &background2);



#endif