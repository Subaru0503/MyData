#ifndef __MUSHROOM_PLANET_H__
#define __MUSHROOM_PLANET_H__

//=====�C���N���[�h=====
#include "Planet.h"	// �f�����N���X

/********************************************
*@brief �Z���N�g��ɔz�u���邫�̂��f���̏���
********************************************/
class MushroomPlanet : public Planet
{
public:
	MushroomPlanet();
	~MushroomPlanet();
	DirectX::XMFLOAT3 GetPos();
};

#endif // !__MUSHROOM_PLANET_H__
