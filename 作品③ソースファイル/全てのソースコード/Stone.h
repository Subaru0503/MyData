#ifndef __STONE_H__
#define __STONE_H__

//----�C���N���[�h��----
#include "Object.h"

//----�N���X��`----
class CStone : public Object
{
public:
	CStone(float posX, float posY, float posZ);
	CStone(float posX, float posY, float posZ, DirectX::XMVECTOR dropDirection, ModelManager* pModelManager);
	~CStone();	// �f�X�g���N�^
private:
};

#endif // __STONE_H__
