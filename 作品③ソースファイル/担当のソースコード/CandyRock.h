#ifndef __CANDYROCK_H__
#define __CANDYROCK_H__

//----�C���N���[�h��----
#include "Object.h"

//----�N���X��`----
class CandyRock : public Object
{
public:
	CandyRock(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ, int level);
	~CandyRock();	// �f�X�g���N�^
private:
};

#endif // __CANDYROCK_H__
