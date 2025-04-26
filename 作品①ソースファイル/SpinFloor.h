// 回転床ギミッククラス

// インクルードガード
#ifndef __SPIN_FLOOR_H__
#define __SPIN_FLOOR_H__

// インクルード部
#include "GimmickBase.h"
#include <DirectXMath.h>

// クラス定義
class SpinFloor : public GimmickBase
{
public:
	enum class SpinType
	{
		XSpin,	// X軸回転
		YSpin,	// Y軸回転
		ZSpin,	// Z軸回転
	};
public:
	SpinFloor(std::string name = "SpinFloor");	// コンストラクタ
	~SpinFloor();								// デストラクタ

	// ターゲットオブジェクトの処理
	void Gimmick(int index, float rotY);
	// 通常のネジを回す方向と逆方向に回されたときに呼ぶ
	void InvertGimmick(int index, float rotY);

	// 回転タイプセット
	inline void SetType(SpinType type)
	{
		m_spinType = type;
	}
	// 初期角度設定
	inline void SetInitAngle()
	{
		for (int i = 0; i < m_TargetScrew.size(); i++)
		{
			m_InitAngle.push_back(m_TargetScrew[i]->GetMultiplier() * 90.0f * m_TargetScrew[i]->GetRatio());
		}

		// ペアギミックがなかったら終了
		if (!m_PairGimmick) return;

		// ギミックの初期位置と円周上のスタート位置との角度を求める

		float3 pos = float3::Tofloat3(m_pos);
		float3 pairPos = float3::Tofloat3(m_PairGimmick->GetPos());

		float distance = float3::distance(pairPos, pos);	// 半径


		DirectX::XMVECTOR difference = DirectX::XMVectorSubtract(	// 減算→(引数1 - 引数2)
			DirectX::XMLoadFloat3(&m_pos),		// ギミックの座標
			DirectX::XMLoadFloat3(&m_PairGimmick->GetPos())			// ペアギミックの座標
		);
		// オブジェクトへのベクトルを正規化
		difference = DirectX::XMVector3Normalize(difference);

		// 円周上にある座標を求める
		DirectX::XMFLOAT3 circlePoint = m_PairGimmick->GetPos();
		circlePoint.x -= distance;

		// X軸に沿ったベクトル
		DirectX::XMVECTOR circleDir = DirectX::XMVectorSubtract(
			DirectX::XMLoadFloat3(&circlePoint),
			DirectX::XMLoadFloat3(&m_PairGimmick->GetPos())
		);

		// 正規化
		circleDir = DirectX::XMVector3Normalize(circleDir);

		// オブジェクトへの方向ベクトルとプレイヤーの向きのベクトルの間のラジアン角を取得
		DirectX::XMStoreFloat(&m_GimmickInitAngle, DirectX::XMVector3AngleBetweenNormals(
			difference,				// ペアギミックから自分への方向ベクトル
			circleDir				// X軸に沿ったベクトル 
		));

		m_GimmickInitAngle = DirectX::XMConvertToDegrees(m_GimmickInitAngle);
	}
private:

	// 軸に合わせた回転
	void GimmickSetQuat(DirectX::XMFLOAT3 axis, float rot);
private:
	SpinType m_spinType;	// 回転タイプ
	std::vector<float> m_InitAngle; // ネジの位置による初期角度
	float m_GimmickInitAngle;		// ギミックの初期位置と円周上のスタート位置との角度
};

#endif // __SPIN_FLOOR_H__