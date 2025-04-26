#ifndef __STONEROYAL_H__
#define __STONEROYAL_H__


//----インクルード部----
#include "Object.h"

//----クラス定義----
class CStoneRoyal : public Object
{
public:
	CStoneRoyal(float posX, float posY, float posZ);
	CStoneRoyal(float posX, float posY, float posZ, DirectX::XMVECTOR dropDirection, ModelManager* pModelManager);
	~CStoneRoyal();	// デストラクタ
private:
};

#endif // __STONEROYAL_H__
