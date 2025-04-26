// オブジェクトスキャナクラス

// インクルードガード
#ifndef __SCANNER_H__
#define __SCANNER_H__

// インクルード部
#include "Component.h"
#include "float3.h"

// クラス定義
class Scanner : public Component
{
public:
	Scanner();	// コンストラクタ

	// obb同士の当たり判定チェック
	bool CheckObb(GameObject* objA, GameObject* objB);

	// 分離軸に投影された軸成分から投影線分長を算出
	float LenSegOnSeparateAxis(float3* Sep, float3* e1, float3* e2, float3* e3 = 0);

	// プレイヤーの座標真ん中に補正
	DirectX::XMFLOAT3 PlayerAdjust(GameObject* obj);

	// セット関数
	inline void SetScale(float3 scale)
	{
		m_Scale = scale;
	}
	inline void SetCollision(bool flg)
	{
		m_Collision = flg;
	}

	// ゲット関数

	inline bool GetCollision()
	{
		return m_Collision;
	}

private:
	bool m_Collision;	// 当たったフラグ
	float3 m_Scale;		// 当たり判定サイズ
};

#endif // __SCANNER_H__