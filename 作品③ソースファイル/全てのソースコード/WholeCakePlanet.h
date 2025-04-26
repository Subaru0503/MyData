#ifndef __WHOLECAKE_PLANET_H__
#define __WHOLECAKE_PLANET_H__

//=====インクルード=====
#include "Planet.h"	// 惑星基底クラス

/********************************************
*@brief セレクト画に配置するきのこ惑星の処理
********************************************/
class WholeCakePlanet : public Planet
{
public:
	WholeCakePlanet();
	~WholeCakePlanet();
	DirectX::XMFLOAT3 GetPos();
};

#endif // !__WHOLECAKE_PLANET_H__