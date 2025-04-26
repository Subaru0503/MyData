#ifndef __MUSHROOM_PLANET_H__
#define __MUSHROOM_PLANET_H__

//=====インクルード=====
#include "Planet.h"	// 惑星基底クラス

/********************************************
*@brief セレクト画に配置するきのこ惑星の処理
********************************************/
class MushroomPlanet : public Planet
{
public:
	MushroomPlanet();
	~MushroomPlanet();
	DirectX::XMFLOAT3 GetPos();
};

#endif // !__MUSHROOM_PLANET_H__
