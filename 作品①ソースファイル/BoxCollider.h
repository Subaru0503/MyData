///////////////////////////////////////
//
// 当たり判定クラス
// OBBによる当たり判定
// オブジェクトごとの補正をする
// 
///////////////////////////////////////

// インクルードガード
#ifndef __BOXCOLLIDER_H__
#define __BOXCOLLIDER_H__

// インクルード部
#include "Component.h"
#include <string>
#include "float3.h"

using namespace std;

// クラス定義
class BoxCollider : public Component
{
public:
	// コンストラクタ
	BoxCollider();

	// obb同士の当たり判定チェック
	bool CheckObb(GameObject* objA, GameObject* objB);

	// 分離軸に投影された軸成分から投影線分長を算出
	float LenSegOnSeparateAxis(float3* Sep, float3* e1, float3* e2, float3* e3 = 0);

	// 座標補正
	void FixPos(GameObject* objB);

	// 押し出して補正
	bool PushAdjust(GameObject* objB);

	// 高さのみの補正か判定+補正もする
	bool CheckHeightOnly(GameObject* objB);

	// 移動床の範囲外にいるか判定する関数
	bool FloorInSide(GameObject* objB);
	// 移動床用の座標補正
	void MoveGimmickFixPos(GameObject* objB);

	// 通常補正
	void NormalFixPos(GameObject* objB);

	// 当たり判定を取らないタグ設定
	inline void SetTag(string tag)
	{
		m_noHitTag.push_back(tag);
	}

	// タグチェック
	inline bool CheckTag(GameObject* objB)
	{
		for (auto it = m_noHitTag.begin(); it != m_noHitTag.end(); it++)
		{			
			// 設定してるタグか
			if (*it == objB->GetTag())
			{
				return true;	// 判定を取らないタグだった
			}
		}

		return false;			// 対象のタグがなかった
	}

	// プレイヤーの座標真ん中に補正
	DirectX::XMFLOAT3 PlayerAdjust(GameObject* obj);

	// 末尾の数値を取得する
	int extractNumber(const string& str);

	//----セット関数----

	// 貫通フラグをセット
	inline void SetIsTrigger(bool flg)
	{
		m_isTrigger = flg;
	}

	// サイズをセット
	inline void SetScale(float3 scale)
	{
		m_Scale = scale;
	}

	// 当たり判定フラグセット
	inline void SetCollision(bool collision)
	{
		m_Collision = collision;
	}

	//----ゲット関数----

	// 貫通フラグを取得
	inline bool GetIsTrigger()
	{
		return m_isTrigger;
	}

	// サイズを取得
	inline float3 GetScale()
	{
		return m_Scale;
	}

	// 当たり判定フラグを取得
	inline bool GetCollision()
	{
		return m_Collision;
	}

private:
	// すり抜け状態にするフラグ
	bool m_isTrigger;

	// 当たり判定を取らないタグ
	std::vector<string> m_noHitTag;

	// 当たり判定サイズ
	float3 m_Scale;

	// 当たったフラグ
	bool m_Collision;
};

#endif // __BOXCOLLIDER_H__