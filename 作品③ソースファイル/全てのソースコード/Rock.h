#ifndef __ROCK_H__
#define __ROCK_H__

//----�C���N���[�h��----
#include "Object.h"

//----�N���X��`----
class CRock : public Object
{
public:
	CRock(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ, int level);
	~CRock();

private:
};

#endif // __ROCK_H__

