#ifndef __WOOD_H__
#define __WOOD_H__

//----�C���N���[�h��----
#include "Object.h"

//----�N���X��`----
class CWood : public Object
{
public:
	CWood(float posX, float posY, float posZ);
	CWood(float posX, float posY, float posZ, DirectX::XMVECTOR dropDirection, ModelManager* pModelManager);
	~CWood();	// �f�X�g���N�^
private:
};

#endif // __WOOD_H__
