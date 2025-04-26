#ifndef __WOODROYAL_H__
#define __WOODROYAL_H__


//----インクルード部----
#include "Object.h"

//----クラス定義----
class CWoodRoyal : public Object
{
public:
	CWoodRoyal(float posX, float posY, float posZ);
	CWoodRoyal(float posX, float posY, float posZ, DirectX::XMVECTOR dropDirection, ModelManager* pModelManager);
	~CWoodRoyal();	// デストラクタ
private:
};

#endif // __WOODROYAL_H__