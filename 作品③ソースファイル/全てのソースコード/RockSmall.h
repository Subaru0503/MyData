#ifndef __ROCK_SMALL_H__
#define __ROCK_SMALL_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class CRockSmall : public Object
{
public:
	CRockSmall(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ, CSoundMng* sound);
	~CRockSmall();

private:
};

#endif // __ROCK_SMALL_H__

