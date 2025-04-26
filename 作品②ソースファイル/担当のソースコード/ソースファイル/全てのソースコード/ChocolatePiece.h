#ifndef __CHOCOLATEPIECE_H__
#define __CHOCOLATEPIECE_H__

//----�C���N���[�h��----
#include "Object.h"

//----�N���X��`----
class ChocolatePiece : public Object
{
public:
	ChocolatePiece(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ,
		DirectX::XMVECTOR dropDirection = DirectX::XMVectorZero(), ModelManager* pModelManager = nullptr,
		int strawberry = false);
	~ChocolatePiece();	// �f�X�g���N�^
private:
};

#endif // __CHOCOLATEPIECE_H__

