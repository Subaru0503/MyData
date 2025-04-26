#ifndef __STONE_H__
#define __STONE_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class CStone : public Object
{
public:
	CStone(float posX, float posY, float posZ);
	CStone(float posX, float posY, float posZ, DirectX::XMVECTOR dropDirection, ModelManager* pModelManager);
	~CStone();	// デストラクタ
private:
};

#endif // __STONE_H__
