#ifndef __BURNINGOBJECT_H__
#define __BURNINGOBJECT_H__

//----�C���N���[�h��----
#include "Object.h"

//----�N���X��`----
class CBurningObject : public Object
{
public:
	CBurningObject(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ);
	~CBurningObject();	// �f�X�g���N�^
private:
};

#endif // __BURNINGOBJECT_H__
