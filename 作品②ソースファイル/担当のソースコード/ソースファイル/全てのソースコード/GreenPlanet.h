#ifndef __GREEN_PLANET_H__
#define __GREEN_PLANET_H__

//=====�C���N���[�h=====
#include "Planet.h"	// �f�����N���X

/********************************************
*@brief �Z���N�g��ɔz�u����stage1�̘f���̏���
********************************************/
class GreenPlanet : public Planet
{
public:
	GreenPlanet();
	~GreenPlanet();
	DirectX::XMFLOAT3 GetPos();
};

#endif // !__GREEN_PLANET_H__
