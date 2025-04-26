#ifndef COLLISION_AREA_MNG
#define COLLISION_AREA_MNG

// ========== インクルード部 ==========
#include "Player.h"
#include "CollisionArea.h"
#include "AreaGround.h"
#include "AreaSea.h"
#include "AreaHill.h"
#include "AreaSlope.h"
#include "ObjectManager.h"

// --- リスト用 ---
#include <list>
using namespace std;

class CCollisionAreaMng
{
public:
	CCollisionAreaMng();
	~CCollisionAreaMng();
	void Update();
	void Draw(DirectX::XMFLOAT4X4* mat);

	void SetPlayer(CPlayer* pPlayer);		// プレイヤー実体取得
	void SetObjList(list<Object*>* pObj);	// オブジェクトリスト実体取得
	list<CCollisionArea*>* GetAreaList();   // AreaListのポインタ渡し

	bool isRandSlope();						// 坂に乗っているか
	bool isHtCheck();						// 高台判定済みか
	void SethtCheck(bool is);				// 高台判定済みセット

	void SetRandSlepe(bool rand);			// 坂に乗ってるかフラグをセット
	static float CheckHeight(int stage, int height);	// 高さを設定

private:
	list<CCollisionArea*> m_areaList;       // 空間判定リスト
	CPlayer* m_pPlayer;						// プレイヤーのポインタ
	list<Object*>* m_pObjList;				// オブジェクトリストのポインタ
	bool m_randSlope;						// 坂に乗っている
	bool m_ht;								// 高台判定済みか
};
#endif