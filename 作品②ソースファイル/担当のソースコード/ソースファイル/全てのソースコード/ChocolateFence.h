#ifndef __CHOCOLATEFENCE_H__
#define __CHOCOLATEFENCE_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class ChocolateFence : public Object
{
public:
	ChocolateFence(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ, float rot, int level);
	~ChocolateFence();	// デストラクタ
private:
};

#endif // __CHOCOLATEFENCE_H__
