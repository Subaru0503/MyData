#ifndef __SIGNBOARD_H__
#define __SIGNBOARD_H__

//----�C���N���[�h��----
#include "Object.h"

//----�N���X��`----
class CSignboard : public Object
{
public:
	CSignboard(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ, float rot);
	~CSignboard();	// �f�X�g���N�^
private:
};

#endif // __SIGNBOARD_H__
