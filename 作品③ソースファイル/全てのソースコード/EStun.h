#pragma once
#include "LibEffekseer.h"

class CPlayer;

class EStun
{
public:
	EStun();
	~EStun();
	void Update();
	void Draw();
	void Stop();
	void SetPlayer(CPlayer *pPlayer);
private:
	Effekseer::EffectRef effect;
	Effekseer::Handle efkHandle;
	CPlayer *m_pPlayer;

	float RadXZ;
};