//----�C���N���[�h�K�[�h----
#ifndef __BISCUIT_PIECE_H__
#define __BISCUIT_PIECE_H__

//----�C���N���[�h��----
#include "Object.h"

//----�N���X��`----
class CBiscuitPiece : public Object
{
public:
	CBiscuitPiece(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ,
		DirectX::XMVECTOR dropDirection = DirectX::XMVectorZero(), ModelManager* pModelManager = nullptr);
	~CBiscuitPiece();	// �f�X�g���N�^
private:
};

#endif // __BISCUIT_PIECE_H__
