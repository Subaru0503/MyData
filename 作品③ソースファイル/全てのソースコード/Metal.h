#ifndef __METAL_H__
#define __METAL_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class CMetal : public Object
{
public:
	CMetal(float posX, float posY, float posZ);
	CMetal(float posX, float posY, float posZ, DirectX::XMVECTOR dropDirection, ModelManager* pModelManager);
	~CMetal();	// デストラクタ
private:
};

#endif // __METAL_H__