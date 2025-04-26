#ifndef __CHOCOLATEPIECEROYAL_H__
#define __CHOCOLATEPIECEROYAL_H__


//----インクルード部----
#include "Object.h"

//----クラス定義----
class ChocolatePieceRoyal : public Object
{
public:
	ChocolatePieceRoyal(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ,
		DirectX::XMVECTOR dropDirection = DirectX::XMVectorZero(), ModelManager* pModelManager = nullptr,
		int strawberry = false);
	~ChocolatePieceRoyal();	// デストラクタ
private:
};

#endif // __CHOCOLATEPIECEROYAL_H__

