#ifndef __BISCUIT_H__
#define __BISCUIT_H__

//----�C���N���[�h��----
#include "Object.h"

//----�N���X��`----
class Biscuit : public Object
{
public:
	Biscuit(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ, float height);
	~Biscuit();	// �f�X�g���N�^
private:
};

#endif // __BISCUIT_H__