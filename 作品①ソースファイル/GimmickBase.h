// ギミック基底クラス

// インクルードガード
#ifndef __Gimmick_Base_H__
#define __Gimmick_Base_H__

// インクルード部
#include "GameObject.hpp"
#include "Screw.h"

// コンポーネント
#include "BoxCollider.h"		// 当たり判定
#include "ModelRenderer3D.h"	// 3Dモデル描画

// クラス定義
class GimmickBase : public GameObject
{
public:
	GimmickBase(std::string name);	// コンストラクタ
	~GimmickBase();									// デストラクタ

	void Update();									// 更新処理

	// ターゲットオブジェクトの処理
	virtual void Gimmick(int index, float rotY);
	// 通常のネジを回す方向と逆方向に回されたときに呼ぶ
	virtual void InvertGimmick(int index, float rotY);

	// 当たったオブジェクトのあとの処理
	virtual void OnCollision(GameObject* obj);

	// セット関数
	// 初期座標をセット
	inline void SetInitePos(DirectX::XMFLOAT3 pos)
	{
		m_InitPos = pos;
	}

	// ペアギミックオブジェクトセット
	inline void SetPair(GameObject* pair)
	{
		m_PairGimmick = pair;
	}
	// 対象ネジセット
	inline void SetScrew(Screw* obj)
	{
		m_TargetScrew.push_back(obj);
		m_OldRotY.push_back(m_TargetScrew.back()->GetQuat().y);
	}
	// 効果反転フラグ
	inline void SetInvertEffect(bool flg)
	{
		m_invertEffectFlg = flg;
	}
	// 地面に当たったフラグに設定
	inline void SetGroundCollision(bool flg)
	{
		m_GroundCollision = flg;
		m_CollisionUpdate = flg;
	}

	// ゲット関数
	inline GameObject* GetPair()
	{
		return m_PairGimmick;
	}
	// 地面に当たったフラグを返す
	inline bool GetGroundCollision()
	{
		return m_GroundCollision;
	}

protected:
	// コンポーネント
	BoxCollider* _boxCollider;			// ボックスコライダーコンポーネント
	ModelRenderer3D* _modelRenderer3D;	// 3D描画コンポーネント

	GameObject* m_PairGimmick;			// ペアのギミックオブジェクト

	std::vector<Screw*> m_TargetScrew;	// 対象ネジ
	std::vector<float> m_OldRotY;		// 過去角度

	DirectX::XMFLOAT3 m_InitPos;		// 初期座標

	// ネジを回した方向で呼ぶ関数を逆にする
	bool m_invertEffectFlg;				// 反転フラグ
	bool m_CollisionUpdate;				// 当たった後の処理が通ったフラグ
	bool m_GroundCollision;				// 地面に当たったフラグ
};

#endif // __Gimmick_Base_H__