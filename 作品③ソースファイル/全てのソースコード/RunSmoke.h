#pragma once
#ifndef _RUNSMOKE__H_
#define __RUNSMOKE_H_


#include"Effect.h"

class RunSmoke : public Emitter
{
public:
	RunSmoke();
	~RunSmoke();

protected:
	void Spawn(Particle* particle, const DirectX::XMFLOAT3& rootPos);
};

#endif // !__MOVE_EMITTER_H_
