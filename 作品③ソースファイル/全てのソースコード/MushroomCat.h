#ifndef __MUSHROOMCAT_H__
#define __MUSHROOMCAT_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class MushroomCat : public Object
{
public:
	MushroomCat(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ);
	~MushroomCat();	// デストラクタ
private:
};

#endif // __MUSHROOMCAT_H__