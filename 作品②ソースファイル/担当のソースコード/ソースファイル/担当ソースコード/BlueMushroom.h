#ifndef __BLUE_MUSHROOM_H__
#define __BLUE_MUSHROOM_H__

// ========== インクルード部 ==========
#include "Object.h"

// ========== クラス ==========
class BlueMushroom : public Object
{
public:
	BlueMushroom(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ);
	~BlueMushroom();

private:
};

#endif // !__BLUE_MUSHROOM_H__
