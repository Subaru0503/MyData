#ifndef __CHOCOLATETREELARGE_H__
#define __CHOCOLATETREELARGE_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class ChocolateTreeLarge : public Object
{
public:
	ChocolateTreeLarge(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ);
	~ChocolateTreeLarge();	// デストラクタ
private:
};

#endif // __CHOCOLATETREELARGE_H__
