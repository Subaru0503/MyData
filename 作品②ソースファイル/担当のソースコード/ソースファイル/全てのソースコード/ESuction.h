#pragma once
#include "LibEffekseer.h"

class CPlayer;

class ESuction
{
public:
	ESuction();
	~ESuction();
	void Update();
	void Draw();
	void Stop();
	void SetPlayer(CPlayer *pPlayer);
	void SetScale();
private:
	Effekseer::EffectRef effect;
	Effekseer::Handle efkHandle;
	CPlayer *m_pPlayer;

	float RadXZ;
	float scalex;
	float scalez;

};