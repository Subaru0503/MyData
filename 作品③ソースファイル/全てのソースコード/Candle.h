#ifndef __CANDLE_H__
#define __CANDLE_H__

//----�C���N���[�h��----
#include "Object.h"

//----�N���X��`----
class Candle : public Object
{
public:
	Candle(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ, int level);
	~Candle();	// �f�X�g���N�^
private:
};

#endif // __CANDLE_H__
