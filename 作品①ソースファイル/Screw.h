///////////////////////////////////////
//
// ネジ基底クラス
//
///////////////////////////////////////

// インクルードガード
#ifndef __SCREW_H__
#define __SCREW_H__

// インクルード部
#include "GameObject.hpp"

// コンポーネント
#include "Move.h"	// 移動
#include "Spin.h"	// 回転
#include "BoxCollider.h"		// 当たり判定
#include "ModelRenderer3D.h"	// 3Dモデル描画

// クラス定義
class Screw : public GameObject
{
public:

	// コンストラクタ
	Screw(std::string name = "Screw");

	// デストラクタ
	~Screw();

	// 更新処理
	void Update();

	// 初期状態に戻す
	void ResetState();

	// 回転関数
	virtual void ObjRightSpin(bool Right = true);

	// リセットタイム
	inline void ResetTime()
	{
		m_SpinFlg = false;
	}

	// ナットとの距離を割合にして返す
	float GetRatio()
	{
		float ratio = 1 - abs((m_Nut->GetPos().y - m_pos.y)) / m_SpinDistance;
		// 補正
		if (0.98f < ratio)
		{
			ratio = 1.0f;
		}
		else if (0.02f > ratio)
		{
			ratio = 0.0f;
		}

		return ratio;
	}

	//----セット関数----

	// 初期座標をセット
	inline void SetInitePos(DirectX::XMFLOAT3 pos)
	{
		m_InitPos = pos;
	}

	// ナットセット
	void SetNut(GameObject* nut)
	{
		m_Nut = nut;
	}

	// ナットとの最長距離セット
	void SetNutMaxDistance(float distance)
	{
		m_SpinDistance = distance;
	}

	// 効果倍率セット
	void SetMultiplier(float mul)
	{
		m_Multiplier = mul;
	}

	// 回転力、抵抗力セット
	void SetSpinParam(float torque, float moment)
	{
		_spin->SetTorque(torque);
		_spin->SetMoment(moment);
	}

	//----ゲット関数----

	// スピンフラグ取得
	bool GetSpinFlg()
	{
		return m_SpinFlg;
	}

	// 効果倍率取得
	float GetMultiplier()
	{
		return m_Multiplier;
	}

protected:
	//----コンポーネント----

	// 移動コンポーネント
	Move* _move;

	// 回転コンポーネント
	Spin* _spin;

	// ボックスコライダーコンポーネント
	BoxCollider* _boxCollider;

	// 3D描画コンポーネント
	ModelRenderer3D* _modelRenderer3D;


	//----メンバ変数----

	// ナット
	GameObject* m_Nut;

	// 初期座標
	DirectX::XMFLOAT3 m_InitPos;

	// 回転量の効果倍率
	float m_Multiplier;

	// ネジを動かせる最大量
	float m_SpinDistance;

	// 回されているフラグ
	bool m_SpinFlg;

	// SE再生フラグ
	bool m_SpinMaxPlayingSE;
};

#endif // __SCREW_H__