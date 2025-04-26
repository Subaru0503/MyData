#ifndef __BISCUIT_H__
#define __BISCUIT_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class Biscuit : public Object
{
public:
	Biscuit(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ, float height);
	~Biscuit();	// デストラクタ
private:
};

#endif // __BISCUIT_H__