#ifndef __CHOCOLATEPIECEROYAL_H__
#define __CHOCOLATEPIECEROYAL_H__


//----�C���N���[�h��----
#include "Object.h"

//----�N���X��`----
class ChocolatePieceRoyal : public Object
{
public:
	ChocolatePieceRoyal(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ,
		DirectX::XMVECTOR dropDirection = DirectX::XMVectorZero(), ModelManager* pModelManager = nullptr,
		int strawberry = false);
	~ChocolatePieceRoyal();	// �f�X�g���N�^
private:
};

#endif // __CHOCOLATEPIECEROYAL_H__

