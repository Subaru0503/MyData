//=================================================================
//
//	Collision.cpp
//	当たり判定関連
//
//=================================================================

// ========== インクルード部 ==========
#include "Collision.h"
#include <cmath>
using namespace std;	// List用

//=====マクロ定義=====
#define REVISION_POS (1.05f)		// 貫通防止の座標補正
#define CLIMB_STAIRS (0.0f)			// 上れる段差の高さ
#define REVISION_HIDE_X (2.5f)		// オブジェクト透過範囲X
#define REVISION_HIDE_Y (1.5f)		// オブジェクト透過範囲Y
#define REVISION_HIDE_Z (2.5f)		// オブジェクト透過範囲Z
#define TUTORIAL_RADIUS	(3.0f)		// チュートリアル看板判定距離

// ========== コンストラクタ ==========
CCollision::CCollision()
	: m_pPlayer(nullptr)
	, m_pObjMng(nullptr)
	, m_pShop(nullptr)
	, m_pTrade{ nullptr, nullptr, nullptr }
	, m_pTradeIcon(nullptr)
	, m_pTutorial(nullptr)
{
}

// ========== 更新処理 ==========
// プレイヤーとオブジェクトの当たり判定をとる
// =============================
void CCollision::Update()
{
	bool tutorial = false;
	bool isBiscuit = false;	// ビスケットに当たったか

	m_pPlayer->SetTutorial(false, 1);

	// =-=-= 初期化 =-=-=
	// ----- オブジェクトのポインタリストを取得 -----
	list<Object*>*  ObjectList = m_pObjMng->GetObjectList();

	// =-=-= 当たり判定 =-=-=
	for (Object* pObj : *ObjectList)	// 全てのオブジェクトと当たり判定を取る
	{
		switch (pObj->GetKind())		// オブジェクトの種類に応じた形で当たり判定を取る
		{
			// ----- 矩形　対　矩形 -----
		case Object::NONE:	break;
		case Object::TREE:				// 木
		case Object::ROCK:				// 岩
		//case Object::HOUSE:			// 家
		case Object::BURNINGOBJECT:		// 燃えてるオブジェクト
		case Object::FENCE:				// フェンス
		case Object::SIGNBOARD:			// 看板
		case Object::MUSHROOM:			// キノコ
		case Object::RUBBISH:			// ゴミ
		case Object::STONE:				// 石
		case Object::WOOD:				// 木
		//case Object::BLUE_MUSHROOM:	// 青きのこ
		case Object::DONUTS:			// ドーナツ
		case Object::CAKEPIECE:			// ケーキ
		case Object::STRAWBERRY:		// イチゴ
		case Object::APOLO:				// アポロ
		case Object::COOKIE:			// クッキー
		case Object::CHOCOLATETREE:		// チョコ木
		case Object::CANDYROCK:			// 飴岩
		case Object::CHOCOLATEFENCE:	// チョコフェンス
		case Object::CHOCOLATEPIECE:	// チョコ欠片（木材）
		case Object::CANDYPIECE:		// 飴欠片（石ころ）
		case Object::CANDLE:			// ろうそく
		case Object::SWEETSHOUSE:		// お菓子の家
		case Object::BISCUIT:			// ビスケットギミック
		case Object::BISCUITPIECE:		// ビスケットギミックカス
		case Object::Kind::TUTORIALSIGNBOARD:	// チュートリアル看板

			//if (pObj->GetKind() == Object::Kind::COOKIE)
			//{
			//	if (CheckCollisionRectToRect(m_pPlayer->GetPos(),
			//		pObj->GetPos(), m_pPlayer->GetScale(), pObj->GetScale()))
			//	{
			//		//---当たっていたらオブジェクトの外に移動
			//		SetPlayerPos(m_pPlayer->GetPos(), pObj->GetPos(), m_pPlayer->GetScale(), pObj->GetScale());
			//		//---オブジェクトの速度を補正
			//		pObj->SetVelocity(0.0f);
			//		//---オブジェクト自身に接触を知らせる
			//		pObj->SetTouch(true);

			//		// ---ビスケットの場合は上に乗る
			//		if (pObj->GetKind() == Object::Kind::BISCUIT) {
			//			m_pPlayer->SetRandHeight(pObj->GetRandHeight());
			//			isBiscuit = true;
			//		}
			//	}
			//}
			//---当たり判定を取る
			if (CheckCollisionRectToRect(m_pPlayer->GetPos(),
				pObj->GetPos(), m_pPlayer->GetScale(), pObj->GetScale()))
			{
				// ---ビスケットの場合は上に乗る
				if (pObj->GetKind() == Object::Kind::BISCUIT) {
					if (m_pPlayer->GetPos().y >= pObj->GetPos().y) {	// ビスケットの下では判定しない
						pObj->SetTouch(true);
						m_pPlayer->SetRandHeight(pObj->GetRandHeight());
						isBiscuit = true;
					}
					break;
				}

				//---当たっていたらオブジェクトの外に移動
				SetPlayerPos(m_pPlayer->GetPos(), pObj->GetPos(), m_pPlayer->GetScale(), pObj->GetScale());
				//---オブジェクトの速度を補正
				pObj->SetVelocity(0.0f);
				//---オブジェクト自身に接触を知らせる
				pObj->SetTouch(true);
			}
			else
			{
				//---オブジェクト自身に接触していない判定を渡す
				pObj->SetTouch(false);
			}
			//---プレイヤーとカメラの直線状の当たり判定
			if (IsObjectOnCameraLine(m_pPlayer->GetPos(),
				m_pPlayer->GetCameraPos(), pObj->GetPos(), pObj->GetScale()))
			{
				//---当たっていたら描画停止
				pObj->SetDraw(false);
			}
			//---描画
			else pObj->SetDraw(true);

			if (pObj->GetKind() == Object::TUTORIALSIGNBOARD) {
				//---チュートリアル
				if (CheckCollisionCircleToCircleWithAngle(m_pPlayer->GetPos(),
					pObj->GetPos(), m_pPlayer->GetScale().x / 2.5, TUTORIAL_RADIUS, pObj->GetAngle()))
				{
					m_pPlayer->SetTutorial(true, pObj->GetTutorialKind());
					tutorial = true;
					m_pTutorial->SetPos(pObj->GetPos());
					break;
				}
				else if (!tutorial) {
					m_pPlayer->SetTutorial(false, pObj->GetTutorialKind());
				}
			}

			break;

			//---青キノコ　ギミックの判定
		case Object::BLUE_MUSHROOM:
			//---当たり判定を取る
			if (CheckCollisionRectToRect(m_pPlayer->GetPos(),
				pObj->GetPos(), m_pPlayer->GetScale(), pObj->GetScale()))
			{
				//---当たっていたらオブジェクトの外に移動
				SetPlayerPos(m_pPlayer->GetPos(), pObj->GetPos(), m_pPlayer->GetScale(), pObj->GetScale());
				//---オブジェクトの速度を補正
				pObj->SetVelocity(0.0f);
				//---オブジェクト自身に接触を知らせる
				pObj->SetTouch(true);
			}
			else
			{
				//---オブジェクト自身に接触していない判定を渡す
				pObj->SetTouch(false);
			}

			//---ギミックと壊せるオブジェクトの当たり判定
			for (Object* pDelObj : *ObjectList)
			{
				// ギミック以外、キノコ以外、レベル2以上
				if (!pDelObj->GetGimmick() && pDelObj->GetKind() != Object::MUSHROOM && pDelObj->GetLevel() > 1)
				{
					if (CheckCollisionRectToRect(pDelObj->GetPos(),
						pObj->GetPos(), pDelObj->GetScale(), pObj->GetScale()))
					{
						pDelObj->SetGetMoney(false);	// お金は入手しない
						pDelObj->SetDelete();			// 破壊
					}
				}
			}

			//---プレイヤーとカメラの直線状の当たり判定
			if (IsObjectOnCameraLine(m_pPlayer->GetPos(),
				m_pPlayer->GetCameraPos(), pObj->GetPos(), pObj->GetScale()))
			{
				//---当たっていたら描画停止
				pObj->SetDraw(false);
			}
			//---描画
			else pObj->SetDraw(true);
			break;

			break;

			// ----- 円　対　矩形 -----
		case Object::HOUSE:	// 家
			// *** 未実装 ***
			break;
		default:
			break;
		}
	}
	m_pPlayer->SetRandBiscuit(isBiscuit);	// ビスケットに乗ったかどうか

	// ----- プレイヤー　対　商人 -----
	for (auto pTrade : m_pTrade) {
		if (pTrade) {
			if (CheckCollisionCircleToCircleWithAngle(m_pPlayer->GetPos(),
				pTrade->GetPos(), m_pPlayer->GetScale().x / 2.5, pTrade->GetRadius(), pTrade->GetAngle()))
			{
				m_pPlayer->SetTrade(true);
				//pTrade->SetPos(pTrade->GetPos());
				m_pTradeIcon->SetPos(pTrade->GetPos());
				break;
			}
			else { m_pPlayer->SetTrade(false); }
		}
	}	
}

// ========== 矩形 対 矩形の当たり判定 ==========
// 引　数：
// XMFLOAT3 Pos1	対象１の中心座標
// XMFLOAT3 Pos2	対象２の中心座標
// XMFLOAT3 Scale1	対象１のサイズ
// XMFLOAT3 Scale2	対象２のサイズ
// 戻り値：bool 当たっていたらtrue
// 指定された矩形と矩形の当たり判定をとる
// ========================================
bool CCollision::CheckCollisionRectToRect(DirectX::XMFLOAT3 Pos1, DirectX::XMFLOAT3 Pos2,
	DirectX::XMFLOAT3 Scale1, DirectX::XMFLOAT3 Scale2)
{
	//---スケールの半径準備
	DirectX::XMFLOAT3 SizeHalf1;
	SizeHalf1.x = Scale1.x / 2.0f;
	SizeHalf1.y = Scale1.y / 2.0f;
	SizeHalf1.z = Scale1.z / 2.0f;
	DirectX::XMFLOAT3 SizeHalf2;
	SizeHalf2.x = Scale2.x / 2.0f;
	SizeHalf2.y = Scale2.y / 2.0f;
	SizeHalf2.z = Scale2.z / 2.0f;

	//---当たり判定
	if ((Pos2.x - SizeHalf2.x <= Pos1.x + SizeHalf1.x) &&		// 2の左端 < 1の右端
		(Pos1.x - SizeHalf1.x <= Pos2.x + SizeHalf2.x))			// 1の左端 < 2の右端
	{
		if ((Pos2.z - SizeHalf2.z <= Pos1.z + SizeHalf1.z) &&	// 2の上端 < 1の下端
			(Pos1.z - SizeHalf1.z <= Pos2.z + SizeHalf2.z))		// 1の上端 < 2の下端
		{

			//if ((Pos2.y - SizeHalf2.y < Pos1.y + SizeHalf1.y) &&
			//	(Pos1.y < Pos2.y + SizeHalf2.y))
			//{
			return true;
			//}
		}
	}
	return false;
}

// ========== 矩形 対 点の当たり判定 ==========
// 引　数：
// XMFLOAT3 Pos1	対象１の中心座標
// XMFLOAT3 Pos2	対象２の中心座標
// XMFLOAT3 Scale1	対象１のサイズ
// 戻り値：bool 当たっていたらtrue
// 指定された矩形と点の当たり判定をとる
// ========================================
bool CCollision::CheckCollisionRectToPoint(DirectX::XMFLOAT3 Pos1, DirectX::XMFLOAT3 Pos2, DirectX::XMFLOAT3 Scale1)
{
	//---スケールの半径準備
	DirectX::XMFLOAT3 SizeHalf1;
	SizeHalf1.x = Scale1.x / 2.0f;
	SizeHalf1.y = Scale1.y / 2.0f;
	SizeHalf1.z = Scale1.z / 2.0f;

	//---当たり判定
	if ((Pos2.x <= Pos1.x + SizeHalf1.x) &&			// 2 < 1の右端
		(Pos1.x - SizeHalf1.x <= Pos2.x))			// 1の左端 < 2
	{
		if ((Pos2.z <= Pos1.z + SizeHalf1.z) &&		// 2 < 1の下端
			(Pos1.z - SizeHalf1.z <= Pos2.z))		// 1の上端 < 2
		{
			//if ((Pos2.y <= Pos1.y + SizeHalf1.y) &&
			//	(Pos1.y <= Pos2.y))
			//{
			return true;
			//}
		}
	}
	return false;
}


// ========== 円 対 円の当たり判定 ==========
// 引　数：
//	XMFLOAT3 対象１の中心座標
//	XMFLOAT3 対象２の中心座標
//	float	対象１の半径
//	float	対象２の半径
// 戻り値：bool 当たっていたらtrue
// 指定された円と円の当たり判定をとる
// ========================================
bool CCollision::CheckCollisionCircleToCircle(DirectX::XMFLOAT3 centerPos1, DirectX::XMFLOAT3 centerPos2, float radius1, float radius2)
{
	if ((centerPos1.x - centerPos2.x) * (centerPos1.x - centerPos2.x) + (centerPos1.z - centerPos2.z) * (centerPos1.z - centerPos2.z) <=		// (円1の中心座標X - 円2の中心座標X)の2乗 + (円1の中心座標Y - 円2の中心座標Y)の2乗
		(radius1 + radius2) * (radius1 + radius2))	// (円1の半径+円2の半径)の2乗
	{
		return true;
	}
	return false;
}

bool CCollision::CheckCollisionCircleToCircleWithAngle(DirectX::XMFLOAT3 centerPos1, DirectX::XMFLOAT3 centerPos2, float radius1, float radius2, DirectX::XMFLOAT3 angle2)
{
	// 円対円の当たり判定
	if ((centerPos1.x - centerPos2.x) * (centerPos1.x - centerPos2.x) + (centerPos1.z - centerPos2.z) * (centerPos1.z - centerPos2.z) > (radius1 + radius2) * (radius1 + radius2)) {
		return false; // 円が重なっていない
	}

	// 2つ目のオブジェクトの前方ベクトルを計算
	DirectX::XMVECTOR forwardVec2 = DirectX::XMVectorSet(
		sin(DirectX::XMConvertToRadians(angle2.y)), // Y軸回転を考慮、正の値で計算
		0.0f,
		cos(DirectX::XMConvertToRadians(angle2.y)),
		0.0f
	);

	// 1つ目のオブジェクトと2つ目のオブジェクトの位置関係ベクトル
	DirectX::XMVECTOR toPos1Vec = DirectX::XMVectorSet(
		centerPos1.x - centerPos2.x,
		0.0f,
		centerPos1.z - centerPos2.z,
		0.0f
	);
	toPos1Vec = DirectX::XMVector3Normalize(toPos1Vec); // ベクトルを正規化

	// 2つ目のオブジェクトから見た1つ目のオブジェクトの方向と、2つ目のオブジェクトの前方ベクトルとの角度を計算
	float dotProduct = DirectX::XMVectorGetX(DirectX::XMVector3Dot(forwardVec2, toPos1Vec));
	float angleBetween = DirectX::XMConvertToDegrees(acos(dotProduct));

	// 角度が90度以内か判定
	if (angleBetween >= 90.0f) {
		return true; // 前方180度以内
	}

	return false; // 前方180度外
}

// ========== IsObjectOnCameraLine ==========
// 引　数：
// XMFLOAT3 playerPos	プレイヤーの中心座標
// XMFLOAT3 cameraPos	カメラの中心座標
// XMFLOAT3	objectpos	オブジェクトの中心座標
// XMFLOAT3	objectSize	オブジェクトの大きさ
// 戻り値：bool 当たっていたらtrue
// プレイヤーとカメラの直線状にオブジェクトがあるかの判定
// =========================================
bool CCollision::IsObjectOnCameraLine(DirectX::XMFLOAT3 playerPos, DirectX::XMFLOAT3 cameraPos, DirectX::XMFLOAT3 objectPos, DirectX::XMFLOAT3 objectSize)
{
	//---線分を定義
	DirectX::XMFLOAT3 focus = playerPos;
	DirectX::XMFLOAT3 objSize = objectSize;
	focus.y += 2.0f;	//焦点の補正
	objSize.x = objSize.x / 2.5f;	//判定を取るサイズ補正
	objSize.y = objSize.y / 1.5f;	//Y
	objSize.z = objSize.z / 2.5f;	//Z
	DirectX::XMVECTOR lineStartVec = DirectX::XMLoadFloat3(&cameraPos);
	DirectX::XMVECTOR lineEndVec = DirectX::XMLoadFloat3(&focus);
	DirectX::XMVECTOR lineDirVec = DirectX::XMVectorSubtract(lineEndVec, lineStartVec);

	DirectX::XMVECTOR boxCenterVec = DirectX::XMLoadFloat3(&objectPos);
	DirectX::XMVECTOR boxSizeVec = DirectX::XMLoadFloat3(&objSize);
	DirectX::XMVECTOR boxMinVec = DirectX::XMVectorSubtract(boxCenterVec, boxSizeVec);
	DirectX::XMVECTOR boxMaxVec = DirectX::XMVectorAdd(boxCenterVec, boxSizeVec);

	// tMinとtMaxを計算
	float tMin = 0.0f, tMax = 1.0f;
	for (int i = 0; i < 3; ++i) {
		float invD = 1.0f / DirectX::XMVectorGetByIndex(lineDirVec, i);
		float t0 = (DirectX::XMVectorGetByIndex(boxMinVec, i) - DirectX::XMVectorGetByIndex(lineStartVec, i)) * invD;
		float t1 = (DirectX::XMVectorGetByIndex(boxMaxVec, i) - DirectX::XMVectorGetByIndex(lineStartVec, i)) * invD;
		if (invD < 0.0f) std::swap(t0, t1);
		tMin = t0 > tMin ? t0 : tMin;
		tMax = t1 < tMax ? t1 : tMax;
		if (tMax <= tMin) return false;
	}
	return true;
}

// ========== SetPlayer ==========
// 引　数：CPlayer*	プレイヤーの実体のポインタ
// 戻り値：なし
// Player情報を設定する
// ==============================
void CCollision::SetPlayer(CPlayer* player)
{
	m_pPlayer = player;
}

// ========== SetObjectManager ==========
// 引　数：CObjectMng*	オブジェクトMngの実体のポインタ
// 戻り値：なし
// ObjectMng情報を設定する
// ======================================
void CCollision::SetObjectManager(CObjectMng* objMng)
{
	m_pObjMng = objMng;
}

void CCollision::SetTrade(vector<CTrade*> trade)
{
	m_pTrade = trade;
}

// ========== SetPlayerPos ==========
// 引　数：
// XMFLOAT3 Pos1	対象１の中心座標
// XMFLOAT3 Pos2	対象２の中心座標
// XMFLOAT3	Scale1	対象１の大きさ
// XMFLOAT3	Scale2	対象２の大きさ
// 戻り値：なし
// プレイヤーの座標をXYZ各要素ずつ設定
// ==================================
void CCollision::SetPlayerPos(DirectX::XMFLOAT3 Pos1, DirectX::XMFLOAT3 Pos2,
	DirectX::XMFLOAT3 Scale1, DirectX::XMFLOAT3 Scale2)
{
	//---スケールの半径準備
	DirectX::XMFLOAT3 SizeHalf1;
	SizeHalf1.x = Scale1.x / 2.0f;
	SizeHalf1.y = Scale1.y / 2.0f;
	SizeHalf1.z = Scale1.z / 2.0f;
	DirectX::XMFLOAT3 SizeHalf2;
	SizeHalf2.x = Scale2.x / 2.0f;
	SizeHalf2.y = Scale2.y / 2.0f;
	SizeHalf2.z = Scale2.z / 2.0f;

	//---Y軸、高さの貫通防止
	if (Pos1.y < Pos2.y + SizeHalf2.y && m_pPlayer->GetOldPos().y > Pos2.y + SizeHalf2.y)
	{
		m_pPlayer->SetPosY(Pos2.y + SizeHalf2.y + SizeHalf1.y * REVISION_POS);
	}

	//---上れなければXZ軸の貫通防止
	if (Pos1.x - SizeHalf1.x < Pos2.x + SizeHalf2.x && m_pPlayer->GetOldPos().x - SizeHalf1.x > Pos2.x + SizeHalf2.x)
	{
		m_pPlayer->SetPosX(Pos2.x + SizeHalf2.x + SizeHalf1.x * REVISION_POS);
	}
	if (Pos1.x + SizeHalf1.x > Pos2.x - SizeHalf2.x && m_pPlayer->GetOldPos().x + SizeHalf1.x < Pos2.x - SizeHalf2.x)
	{
		m_pPlayer->SetPosX(Pos2.x - SizeHalf2.x - SizeHalf1.x * REVISION_POS);
	}
	if (Pos1.z - SizeHalf1.z < Pos2.z + SizeHalf2.z && m_pPlayer->GetOldPos().z - SizeHalf1.z > Pos2.z + SizeHalf2.z)
	{
		m_pPlayer->SetPosZ(Pos2.z + SizeHalf2.z + SizeHalf1.z * REVISION_POS);
	}
	if (Pos1.z + SizeHalf1.z > Pos2.z - SizeHalf2.z && m_pPlayer->GetOldPos().z + SizeHalf1.z < Pos2.z - SizeHalf2.z)
	{
		m_pPlayer->SetPosZ(Pos2.z - SizeHalf2.z - SizeHalf1.z * REVISION_POS);
	}
	

	//---オブジェクト制御
	list<Object*>*  ObjectList = m_pObjMng->GetObjectList();

	for (Object* pObj : *ObjectList)
	{
		if (Pos2.x > Pos1.x + SizeHalf1.x)
		{
			pObj->SetPosX(pObj->GetOldPos().x);
		}
		else if (Pos2.x < Pos1.x - SizeHalf1.x)
		{
			pObj->SetPosX(pObj->GetOldPos().x);
		}
		if (Pos2.z > Pos1.z + SizeHalf1.z)
		{
			pObj->SetPosZ(pObj->GetOldPos().z);
		}
		else if (Pos2.z < Pos1.z - SizeHalf1.z)
		{
			pObj->SetPosZ(pObj->GetOldPos().z);
		}
	}
}

void CCollision::SetTradeIcon(TradeIcon * tIcon)
{
	m_pTradeIcon = tIcon;
}

void CCollision::SetTutorialIcon(Tutorial * TutorialIcon)
{
	m_pTutorial = TutorialIcon;
}
