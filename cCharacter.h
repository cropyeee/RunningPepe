#ifndef CCHARACTER_H
#define CCHARACTER_H

#include "LTexture.h"

class cCharacter :public LTexture{
public:
	cCharacter();
	~cCharacter();
	cCharacter::cCharacter(int _posX, int _posY);
	void jump();
	void moveY(int dy);
	
};
#endif
