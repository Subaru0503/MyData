#ifndef __CANDLEBIG_H__
#define __CANDLEBIG_H__

//----�C���N���[�h��----
#include "Object.h"

//----�N���X��`----
class CandleBig : public Object
{
public:
	CandleBig(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ, CSoundMng* sound);
	~CandleBig();	// �f�X�g���N�^
private:
};

#endif // __CANDLEBIG_H__
