#ifndef __DONUTS_H__
#define __DONUTS_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class Donuts : public Object
{
public:
	Donuts(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ);
	~Donuts();	// デストラクタ
private:
};

#endif // __DONUTS_H__
