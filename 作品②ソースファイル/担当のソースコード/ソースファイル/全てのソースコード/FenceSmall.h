#ifndef __FENCESMALL_H__
#define __FENCESMALL_H__

//----�C���N���[�h��----
#include "Object.h"

//----�N���X��`----
class CFenceSmall : public Object
{
public:
	CFenceSmall(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ, float rot, CSoundMng* sound);
	~CFenceSmall();	// �f�X�g���N�^
private:
};

#endif // __FENCESMALL_H__
