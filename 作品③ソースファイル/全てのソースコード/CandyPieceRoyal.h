#ifndef __CANDYPIECEROYAL_H__
#define __CANDYPIECEROYAL_H__


//----インクルード部----
#include "Object.h"

//----クラス定義----
class CandyPieceRoyal : public Object
{
public:
	CandyPieceRoyal(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ,
		DirectX::XMVECTOR dropDirection = DirectX::XMVectorZero(), ModelManager* pModelManager = nullptr);
	~CandyPieceRoyal();	// デストラクタ
private:
};

#endif // __CANDYPIECEROYAL_H__
