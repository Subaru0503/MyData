#ifndef __SWEETSHOUSE_H__
#define __SWEETSHOUSE_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class SweetsHouse : public Object
{
public:
	SweetsHouse(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ);
	~SweetsHouse();	// デストラクタ
private:
};

#endif // __SWEETSHOUSE_H__
