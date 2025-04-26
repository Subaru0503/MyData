#ifndef AREA_GROUND_H
#define AREA_GROUND_H

#include "CollisionArea.h"
class CCollisionAreaMng;

class CAreaGround :
	public CCollisionArea
{
public:
	enum kind {	// ’n–Ê‚ÌŽí—Þ
		grass = 1,
		beach,
		cream,
		spong,
	};
public:
	CAreaGround(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ, int kind);
	~CAreaGround() {}
	void Update(CCollisionAreaMng* mng, bool b);

private:
	kind m_kind;	// ’n–Ê‚ÌŽí—Þ
};

#endif