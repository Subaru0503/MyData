////////////////////////////////////////////////////////
//
//	Collision.h
//
////////////////////////////////////////////////////////

#ifndef __COLLISION_H__
#define __COLLISION_H__

// ========== インクルード部 ==========
#include "Player.h"
#include "ObjectManager.h"
#include "Shop.h"
#include "Trade.h"
#include "TradeIcon.h"
#include "Tutorial.h"

// ========== CCollisionクラス ==========
class CCollision
{
public:
	CCollision();
	~CCollision() {};
	void Update();

	// 矩形と矩形の当たり判定
	static bool CheckCollisionRectToRect(DirectX::XMFLOAT3 Pos1, DirectX::XMFLOAT3 Pos2,
		DirectX::XMFLOAT3 Scale1, DirectX::XMFLOAT3 Scale2);
	static bool CheckCollisionRectToPoint(DirectX::XMFLOAT3 Pos1, DirectX::XMFLOAT3 Pos2, DirectX::XMFLOAT3 Scale1);
	// 円と円の当たり判定
	static bool CheckCollisionCircleToCircle(DirectX::XMFLOAT3 centerPos1, DirectX::XMFLOAT3 centerPos2,
		float radius1, float radius2);	
	// 円と円の当たり判定+角度
	static bool CheckCollisionCircleToCircleWithAngle(DirectX::XMFLOAT3 centerPos1, DirectX::XMFLOAT3 centerPos2,
		float radius1, float radius2, DirectX::XMFLOAT3 angle2);
	// 円と矩形の当たり判定
	//static bool CheckCollisionCircleToRect();
	bool IsObjectOnCameraLine(DirectX::XMFLOAT3 playerPos, DirectX::XMFLOAT3 cameraPos,
		DirectX::XMFLOAT3 objectPos, DirectX::XMFLOAT3 objectSize);

	void SetPlayer(CPlayer* player);			// Player情報設定
	void SetObjectManager(CObjectMng* objMng);	// ObjectMng設定
	void SetTrade(vector<CTrade*> trade);
	void SetPlayerPos(DirectX::XMFLOAT3 Pos1, DirectX::XMFLOAT3 Pos2,
		DirectX::XMFLOAT3 Scale1, DirectX::XMFLOAT3 Scale2);
	void SetTradeIcon(TradeIcon* tIcon);
	void SetTutorialIcon(Tutorial* TutorialIcon);

private:
	CPlayer* m_pPlayer;							// Playerポインタ格納用
	CObjectMng* m_pObjMng;						// ObjectMngポインタ格納用
	CShop* m_pShop;
	vector<CTrade*> m_pTrade;
	TradeIcon* m_pTradeIcon;
	Tutorial* m_pTutorial;
};

#endif // !__COLLISION_H__