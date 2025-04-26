#ifndef __METAL_H__
#define __METAL_H__

//----�C���N���[�h��----
#include "Object.h"

//----�N���X��`----
class CMetal : public Object
{
public:
	CMetal(float posX, float posY, float posZ);
	CMetal(float posX, float posY, float posZ, DirectX::XMVECTOR dropDirection, ModelManager* pModelManager);
	~CMetal();	// �f�X�g���N�^
private:
};

#endif // __METAL_H__