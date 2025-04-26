#ifndef __STRAWBERRY_H__
#define __STRAWBERRY_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class Strawberry : public Object
{
public:
	Strawberry(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ);
	~Strawberry();	// デストラクタ
private:
};

#endif // __STRAWBERRY_H__
