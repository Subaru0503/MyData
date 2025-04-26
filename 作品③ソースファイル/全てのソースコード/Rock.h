#ifndef __ROCK_H__
#define __ROCK_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class CRock : public Object
{
public:
	CRock(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ, int level);
	~CRock();

private:
};

#endif // __ROCK_H__

