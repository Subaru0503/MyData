//----インクルードガード----
#ifndef __BISCUIT_PIECE_H__
#define __BISCUIT_PIECE_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class CBiscuitPiece : public Object
{
public:
	CBiscuitPiece(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ,
		DirectX::XMVECTOR dropDirection = DirectX::XMVectorZero(), ModelManager* pModelManager = nullptr);
	~CBiscuitPiece();	// デストラクタ
private:
};

#endif // __BISCUIT_PIECE_H__
