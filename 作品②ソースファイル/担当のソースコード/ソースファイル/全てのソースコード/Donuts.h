#ifndef __DONUTS_H__
#define __DONUTS_H__

//----�C���N���[�h��----
#include "Object.h"

//----�N���X��`----
class Donuts : public Object
{
public:
	Donuts(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ);
	~Donuts();	// �f�X�g���N�^
private:
};

#endif // __DONUTS_H__
