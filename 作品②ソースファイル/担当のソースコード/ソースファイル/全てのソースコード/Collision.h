////////////////////////////////////////////////////////
//
//	Collision.h
//
////////////////////////////////////////////////////////

#ifndef __COLLISION_H__
#define __COLLISION_H__

// ========== �C���N���[�h�� ==========
#include "Player.h"
#include "ObjectManager.h"
#include "Shop.h"
#include "Trade.h"
#include "TradeIcon.h"
#include "Tutorial.h"

// ========== CCollision�N���X ==========
class CCollision
{
public:
	CCollision();
	~CCollision() {};
	void Update();

	// ��`�Ƌ�`�̓����蔻��
	static bool CheckCollisionRectToRect(DirectX::XMFLOAT3 Pos1, DirectX::XMFLOAT3 Pos2,
		DirectX::XMFLOAT3 Scale1, DirectX::XMFLOAT3 Scale2);
	static bool CheckCollisionRectToPoint(DirectX::XMFLOAT3 Pos1, DirectX::XMFLOAT3 Pos2, DirectX::XMFLOAT3 Scale1);
	// �~�Ɖ~�̓����蔻��
	static bool CheckCollisionCircleToCircle(DirectX::XMFLOAT3 centerPos1, DirectX::XMFLOAT3 centerPos2,
		float radius1, float radius2);	
	// �~�Ɖ~�̓����蔻��+�p�x
	static bool CheckCollisionCircleToCircleWithAngle(DirectX::XMFLOAT3 centerPos1, DirectX::XMFLOAT3 centerPos2,
		float radius1, float radius2, DirectX::XMFLOAT3 angle2);
	// �~�Ƌ�`�̓����蔻��
	//static bool CheckCollisionCircleToRect();
	bool IsObjectOnCameraLine(DirectX::XMFLOAT3 playerPos, DirectX::XMFLOAT3 cameraPos,
		DirectX::XMFLOAT3 objectPos, DirectX::XMFLOAT3 objectSize);

	void SetPlayer(CPlayer* player);			// Player���ݒ�
	void SetObjectManager(CObjectMng* objMng);	// ObjectMng�ݒ�
	void SetTrade(vector<CTrade*> trade);
	void SetPlayerPos(DirectX::XMFLOAT3 Pos1, DirectX::XMFLOAT3 Pos2,
		DirectX::XMFLOAT3 Scale1, DirectX::XMFLOAT3 Scale2);
	void SetTradeIcon(TradeIcon* tIcon);
	void SetTutorialIcon(Tutorial* TutorialIcon);

private:
	CPlayer* m_pPlayer;							// Player�|�C���^�i�[�p
	CObjectMng* m_pObjMng;						// ObjectMng�|�C���^�i�[�p
	CShop* m_pShop;
	vector<CTrade*> m_pTrade;
	TradeIcon* m_pTradeIcon;
	Tutorial* m_pTutorial;
};

#endif // !__COLLISION_H__