#ifndef __FENCE_H__
#define __FENCE_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class CFence : public Object
{
public:
	CFence(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ, float rot, int level);
	~CFence();	// デストラクタ
private:
};

#endif // __FENCE_H__
