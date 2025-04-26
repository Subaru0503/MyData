#pragma once
#include "LibEffekseer.h"


class TSuction
{
public:
	TSuction();
	~TSuction();
	void Update();
	void Draw();
	void Stop();
private:
	Effekseer::EffectRef effect;
	Effekseer::Handle efkHandle;

};
