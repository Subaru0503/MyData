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
		DirectX::XMFLOAT3 Scale1, DirectX::XMFLOAT3 Scale2);			// �����蔻�莞�̃v���C���[���W�Z�b�g�p

	void SetObjectPos(DirectX::XMFLOAT3 Pos1, DirectX::XMFLOAT3 Pos2, DirectX::XMFLOAT3 Scale1, DirectX::XMFLOAT3 Scale2);

	int m_direct;	// ��̏��n�߂̕Ӂi�P�F���@�Q�F�E�@�R�F��O�@�S�F���j
	//int m_height;	// �������̍����i�`�i�ځj
};

#endif