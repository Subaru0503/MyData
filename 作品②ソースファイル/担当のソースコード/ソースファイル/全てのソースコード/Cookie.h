#ifndef __COOKIE_H__
#define __COOKIE_H__

//----�C���N���[�h��----
#include "Object.h"

//----�N���X��`----
class Cookie : public Object
{
public:
	Cookie(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ);
	~Cookie();	// �f�X�g���N�^
private:
};

#endif // __COOKIE_H__

