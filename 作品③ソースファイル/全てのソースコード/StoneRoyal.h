#ifndef __STONEROYAL_H__
#define __STONEROYAL_H__


//----�C���N���[�h��----
#include "Object.h"

//----�N���X��`----
class CStoneRoyal : public Object
{
public:
	CStoneRoyal(float posX, float posY, float posZ);
	CStoneRoyal(float posX, float posY, float posZ, DirectX::XMVECTOR dropDirection, ModelManager* pModelManager);
	~CStoneRoyal();	// �f�X�g���N�^
private:
};

#endif // __STONEROYAL_H__
