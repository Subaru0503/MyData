#ifndef AREA_SEA_H
#define AREA_SEA_H

#include "CollisionArea.h"
class CCollisionAreaMng;

class CAreaSea : public CCollisionArea
{
public:
	CAreaSea(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ);
	~CAreaSea() {}
	void Update(CCollisionAreaMng* mng, bool objCollision);

private:

};

#endif