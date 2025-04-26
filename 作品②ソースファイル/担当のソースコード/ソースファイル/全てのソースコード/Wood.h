#ifndef __WOOD_H__
#define __WOOD_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class CWood : public Object
{
public:
	CWood(float posX, float posY, float posZ);
	CWood(float posX, float posY, float posZ, DirectX::XMVECTOR dropDirection, ModelManager* pModelManager);
	~CWood();	// デストラクタ
private:
};

#endif // __WOOD_H__
