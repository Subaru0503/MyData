#ifndef __CANDYROCKLARGE_H__
#define __CANDYROCKLARGE_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class CandyRockLarge : public Object
{
public:
	CandyRockLarge(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ);
	~CandyRockLarge();	// デストラクタ
private:
};

#endif // __CANDYROCKLARGE_H__
