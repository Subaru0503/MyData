#ifndef __CAKEPIECE_H__
#define __CAKEPIECE_H__

//----�C���N���[�h��----
#include "Object.h"

//----�N���X��`----
class CakePiece : public Object
{
public:
	CakePiece(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ);
	~CakePiece();	// �f�X�g���N�^
private:
};

#endif // __CAKEPIECE_H__

