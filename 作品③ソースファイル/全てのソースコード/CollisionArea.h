#ifndef COLLISION_AREA_H
#define COLLISION_AREA_H

// ========== インクルード部 ==========
#include "Player.h"
#include "ObjectManager.h"
#include <DirectXMath.h>
#include "Geometory.h"
class CCollisionAreaMng;
#include <list>

// ========== クラス ==========
class CCollisionArea
{
public:// パロメータ
	enum areaKind {
		sea = 1,
		ground,
		hill,
		slope,
	};

public:// 関数
	CCollisionArea() {}
	virtual ~CCollisionArea() {}

	virtual void Update(CCollisionAreaMng* mng, bool objCollision = false) = 0;
	void Draw(DirectX::XMFLOAT4X4* mat);		// 判定空間を可視化
	DirectX::XMFLOAT3 GetPos();					// 座標渡し
	DirectX::XMFLOAT3 GetScale();				// サイズ渡し
	areaKind GetKind();							// 判定の種類渡し
	void SetPlayer(CPlayer* pPlayer);			// プレイヤーの座標・サイズを取得
	void SetObj(Object* pObj);					// オブジェクトリスト取得
	void InitObjHieght();						// 

protected:
	int m_stage;								// 何ステージか
	DirectX::XMFLOAT3 m_pos, m_scale;			// 座標・サイズ
	areaKind m_areakind;						// 判定の種類
	CPlayer* m_pPlayer;							// プレイヤー情報受け取り用
	Object* m_pObject;							// オブジェクト受け取り用
	int m_height;								// 天面の高さ(～段目)
	int m_lowHt;								// 底面(設置位置)の高さ(～段目)
};

#endif // !COLLISION_AREA_H