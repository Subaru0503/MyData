#ifndef __CANDYPIECE_H__
#define __CANDYPIECE_H__

//----�C���N���[�h��----
#include "Object.h"

//----�N���X��`----
class CandyPiece : public Object
{
public:
	CandyPiece(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ,
		DirectX::XMVECTOR dropDirection = DirectX::XMVectorZero(), ModelManager* pModelManager = nullptr);
	~CandyPiece();	// �f�X�g���N�^
private:
};

#endif // __CANDYPIECE_H__
