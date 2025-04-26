#ifndef __GREEN_PLANET_H__
#define __GREEN_PLANET_H__

//=====インクルード=====
#include "Planet.h"	// 惑星基底クラス

/********************************************
*@brief セレクト画に配置するstage1の惑星の処理
********************************************/
class GreenPlanet : public Planet
{
public:
	GreenPlanet();
	~GreenPlanet();
	DirectX::XMFLOAT3 GetPos();
};

#endif // !__GREEN_PLANET_H__
