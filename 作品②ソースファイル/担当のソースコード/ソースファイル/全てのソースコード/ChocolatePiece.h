#ifndef __CHOCOLATEPIECE_H__
#define __CHOCOLATEPIECE_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class ChocolatePiece : public Object
{
public:
	ChocolatePiece(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ,
		DirectX::XMVECTOR dropDirection = DirectX::XMVectorZero(), ModelManager* pModelManager = nullptr,
		int strawberry = false);
	~ChocolatePiece();	// デストラクタ
private:
};

#endif // __CHOCOLATEPIECE_H__

