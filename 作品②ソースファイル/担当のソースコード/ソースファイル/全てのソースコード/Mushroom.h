#ifndef __MUSHROOM_H__
#define __MUSHROOM_H__

//----�C���N���[�h��----
#include "Object.h"

//----�N���X��`----
class Mushroom : public Object
{
public:
	Mushroom(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ, int level);
	~Mushroom();	// �f�X�g���N�^
private:
};

#endif // __Mushroom_H__