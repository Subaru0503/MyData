#ifndef __WHOLECAKE_PLANET_H__
#define __WHOLECAKE_PLANET_H__

//=====�C���N���[�h=====
#include "Planet.h"	// �f�����N���X

/********************************************
*@brief �Z���N�g��ɔz�u���邫�̂��f���̏���
********************************************/
class WholeCakePlanet : public Planet
{
public:
	WholeCakePlanet();
	~WholeCakePlanet();
	DirectX::XMFLOAT3 GetPos();
};

#endif // !__WHOLECAKE_PLANET_H__