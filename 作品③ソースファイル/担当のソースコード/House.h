#ifndef __HOUSE_H__
#define __HOUSE_H__

//----�C���N���[�h��----
#include "Object.h"

//----�N���X��`----
class CHouse : public Object
{
public:
	CHouse(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ, int level);
	~CHouse();

private:
};

#endif // __HOUSE_H__



