#ifndef __CANDYROCK_H__
#define __CANDYROCK_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class CandyRock : public Object
{
public:
	CandyRock(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ, int level);
	~CandyRock();	// デストラクタ
private:
};

#endif // __CANDYROCK_H__
