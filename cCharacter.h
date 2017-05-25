#ifndef CCHARACTER_H
#define CCHARACTER_H

#include "LTexture.h"


class cCharacter :public LTexture{
public:
	cCharacter();
	~cCharacter();
	cCharacter::cCharacter(double _posX, double _posY);
	void fall();
	void handleEvent(SDL_Event& e);//lazyfoo
	void jump();//lazyfoo
	bool returnUp();
	bool returnDown();
	void changeUp();
	void changeDown();

private:
	bool up=false;
	bool down=false;
	
};
#endif
