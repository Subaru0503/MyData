#ifndef __CANDYPIECEROYAL_H__
#define __CANDYPIECEROYAL_H__


//----�C���N���[�h��----
#include "Object.h"

//----�N���X��`----
class CandyPieceRoyal : public Object
{
public:
	CandyPieceRoyal(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ,
		DirectX::XMVECTOR dropDirection = DirectX::XMVectorZero(), ModelManager* pModelManager = nullptr);
	~CandyPieceRoyal();	// �f�X�g���N�^
private:
};

#endif // __CANDYPIECEROYAL_H__
