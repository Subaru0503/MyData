#ifndef __FENCE_H__
#define __FENCE_H__

//----�C���N���[�h��----
#include "Object.h"

//----�N���X��`----
class CFence : public Object
{
public:
	CFence(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ, float rot, int level);
	~CFence();	// �f�X�g���N�^
private:
};

#endif // __FENCE_H__
