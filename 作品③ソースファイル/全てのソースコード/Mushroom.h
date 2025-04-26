#ifndef __MUSHROOM_H__
#define __MUSHROOM_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class Mushroom : public Object
{
public:
	Mushroom(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ, int level);
	~Mushroom();	// デストラクタ
private:
};

#endif // __Mushroom_H__