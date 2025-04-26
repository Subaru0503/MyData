#ifndef __CANDYROCKMEDIUM_H__
#define __CANDYROCKMEDIUM_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class CandyRockMedium : public Object
{
public:
	CandyRockMedium(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ);
	~CandyRockMedium();	// デストラクタ
private:
};

#endif // __CANDYROCKMEDIUM_H__
