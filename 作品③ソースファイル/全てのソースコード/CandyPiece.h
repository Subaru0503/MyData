#ifndef __CANDYPIECE_H__
#define __CANDYPIECE_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class CandyPiece : public Object
{
public:
	CandyPiece(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ,
		DirectX::XMVECTOR dropDirection = DirectX::XMVectorZero(), ModelManager* pModelManager = nullptr);
	~CandyPiece();	// デストラクタ
private:
};

#endif // __CANDYPIECE_H__
