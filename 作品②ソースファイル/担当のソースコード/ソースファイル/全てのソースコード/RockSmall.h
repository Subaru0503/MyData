#ifndef __ROCK_SMALL_H__
#define __ROCK_SMALL_H__

//----�C���N���[�h��----
#include "Object.h"

//----�N���X��`----
class CRockSmall : public Object
{
public:
	CRockSmall(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ, CSoundMng* sound);
	~CRockSmall();

private:
};

#endif // __ROCK_SMALL_H__

