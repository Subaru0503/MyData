#ifndef __CHOCOLATEFENCE_H__
#define __CHOCOLATEFENCE_H__

//----�C���N���[�h��----
#include "Object.h"

//----�N���X��`----
class ChocolateFence : public Object
{
public:
	ChocolateFence(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ, float rot, int level);
	~ChocolateFence();	// �f�X�g���N�^
private:
};

#endif // __CHOCOLATEFENCE_H__
