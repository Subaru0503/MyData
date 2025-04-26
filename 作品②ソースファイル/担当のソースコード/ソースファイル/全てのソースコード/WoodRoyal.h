#ifndef __WOODROYAL_H__
#define __WOODROYAL_H__


//----�C���N���[�h��----
#include "Object.h"

//----�N���X��`----
class CWoodRoyal : public Object
{
public:
	CWoodRoyal(float posX, float posY, float posZ);
	CWoodRoyal(float posX, float posY, float posZ, DirectX::XMVECTOR dropDirection, ModelManager* pModelManager);
	~CWoodRoyal();	// �f�X�g���N�^
private:
};

#endif // __WOODROYAL_H__