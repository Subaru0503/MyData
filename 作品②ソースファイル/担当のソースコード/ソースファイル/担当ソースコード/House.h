#ifndef __HOUSE_H__
#define __HOUSE_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class CHouse : public Object
{
public:
	CHouse(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ, int level);
	~CHouse();

private:
};

#endif // __HOUSE_H__



