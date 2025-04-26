#ifndef AREA_HILL_H
#define AREA_HILL_H

#include "CollisionArea.h"
class CCollisionAreaMng;

class CAreaHill :
	public CCollisionArea
{
public:
	CAreaHill(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ, int height, int stage);
	~CAreaHill() {}
	void Update(CCollisionAreaMng* mng, bool objCollision);

private:
	void SetPlayerPos(DirectX::XMFLOAT3 Pos1, DirectX::XMFLOAT3 Pos2,
		DirectX::XMFLOAT3 Scale1, DirectX::XMFLOAT3 Scale2);			// �����蔻�莞�̃v���C���[���W�Z�b�g�p

	void SetObjectPos(DirectX::XMFLOAT3 Pos1, DirectX::XMFLOAT3 Pos2,
		DirectX::XMFLOAT3 Scale1, DirectX::XMFLOAT3 Scale2);			// �����蔻�莞�̃I�u�W�F�N�g���W�Z�b�g�p

};

#endif