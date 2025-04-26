#ifndef __CHOCOLATEFENCEMEDIUM_H__
#define __CHOCOLATEFENCEMEDIUM_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class ChocolateFenceMedium : public Object
{
public:
	ChocolateFenceMedium(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ);
	~ChocolateFenceMedium();	// デストラクタ
private:
};

#endif // __CHOCOLATEFENCEMEDIUM_H__
