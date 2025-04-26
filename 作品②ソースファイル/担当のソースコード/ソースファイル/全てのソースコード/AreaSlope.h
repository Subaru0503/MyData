#ifndef AREA_SLOPE_H
#define AREA_SLOPE_H

#include "CollisionArea.h"
class CCollisionAreaMng;

class CAreaSlope :
	public CCollisionArea
{
public:
	CAreaSlope(int lowHt, float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ, int direct, int height, int stage);
	~CAreaSlope() {}
	void Update(CCollisionAreaMng* mng, bool objCollition);

private:
	void CheckSlopePlayer(CCollisionAreaMng* mng);
	void CheckSlopeObj(CCollisionAreaMng* mng);
	void SetPlayerPos(DirectX::XMFLOAT3 Pos1, DirectX::XMFLOAT3 Pos2,
		DirectX::XMFLOAT3 Scale1, DirectX::XMFLOAT3 Scale2);			// 当たり判定時のプレイヤー座標セット用

	void SetObjectPos(DirectX::XMFLOAT3 Pos1, DirectX::XMFLOAT3 Pos2, DirectX::XMFLOAT3 Scale1, DirectX::XMFLOAT3 Scale2);

	int m_direct;	// 坂の上り始めの辺（１：奥　２：右　３：手前　４：左）
	//int m_height;	// 上った先の高さ（～段目）
};

#endif