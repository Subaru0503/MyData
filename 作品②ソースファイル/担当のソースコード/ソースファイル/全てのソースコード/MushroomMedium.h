#ifndef __MUSHROOM_MEDIUM_H__
#define __MUSHROOM_MEDIUM_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class MushroomMedium : public Object
{
public:
	MushroomMedium(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ);
	~MushroomMedium();	// デストラクタ
private:
};

#endif // __MUSHROOM_MEDIUM_H__