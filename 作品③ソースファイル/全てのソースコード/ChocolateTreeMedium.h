#ifndef __CHOCOLATETREEMEDIUM_H__
#define __CHOCOLATETREEMEDIUM_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class ChocolateTreeMedium : public Object
{
public:
	ChocolateTreeMedium(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ);
	~ChocolateTreeMedium();	// デストラクタ
private:
};

#endif // __CHOCOLATETREEMEDIUM_H__
