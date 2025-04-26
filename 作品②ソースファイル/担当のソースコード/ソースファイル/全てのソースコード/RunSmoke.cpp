#include "RunSmoke.h"

RunSmoke::RunSmoke()
	:Emitter("Assets/Effect/RunSmoke.png", { 2,0.1f,0.5f })
{
}

RunSmoke::~RunSmoke()
{

}

void RunSmoke::Spawn(Particle * particle, const DirectX::XMFLOAT3 & rootPos)
{
	particle->pos.value = rootPos;
	particle->pos.value.x += (rand() % 3 - 1) * 0.1f;
	particle->pos.add.y = 0.01f;
	particle->size.value.x = 0.5f;
	particle->size.value.y = 0.5f;
	particle->size.add.x = 0.005f;
	particle->size.add.y = 0.005f;
	//particle->alpha.add.x = -0.01f;
	particle->life = 0.3f;
}