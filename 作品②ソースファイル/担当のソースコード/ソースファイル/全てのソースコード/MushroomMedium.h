#ifndef __MUSHROOM_MEDIUM_H__
#define __MUSHROOM_MEDIUM_H__

//----�C���N���[�h��----
#include "Object.h"

//----�N���X��`----
class MushroomMedium : public Object
{
public:
	MushroomMedium(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ);
	~MushroomMedium();	// �f�X�g���N�^
private:
};

#endif // __MUSHROOM_MEDIUM_H__