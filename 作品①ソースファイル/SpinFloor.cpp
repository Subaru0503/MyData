// 回転ギミッククラス

// インクルード部
#include "SpinFloor.h"

// システム
#include "Input.h"

// コンストラクタ
SpinFloor::SpinFloor(std::string name)
	: GimmickBase(name)
{

}

// デストラクタ
SpinFloor::~SpinFloor()
{
}

// ターゲットオブジェクトの処理
void SpinFloor::Gimmick(int index, float rotY)
{
	// 回転軸情報
	DirectX::XMFLOAT3 axis = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	// 角度
	float rot = 0.0f;

	// 回転ギミック
	switch (m_spinType)
	{
	// X軸回転
	case SpinType::XSpin:
		axis.x = -1.0f;
		for (int i = 0; i < m_TargetScrew.size(); i++)
		{
			rot += m_TargetScrew[i]->GetMultiplier() * 90.0f * m_TargetScrew[i]->GetRatio();
		}
		break;
	// Y軸回転
	case SpinType::YSpin:
		axis.y = -1.0f;
		for (int i = 0; i < m_TargetScrew.size(); i++)
		{
			rot += m_TargetScrew[i]->GetMultiplier() * 90.0f * m_TargetScrew[i]->GetRatio() - m_InitAngle[i];
		}

		// 一緒に動くギミックがあるなら回転と一緒に場所を動かす
		if (m_PairGimmick)
		{
			float3 pos = float3::Tofloat3(m_pos);
			float3 pairPos = float3::Tofloat3(m_PairGimmick->GetPos());

			float distance = float3::distance(pairPos, pos);	// 半径

			////float3 AN = pos.normalize();
			////float3 BN = pairPos.normalize();

			////float dot = float3::dot(AN, BN);
			////float initRot = acos(dot);

			m_pos.x = pairPos.x - cos(DirectX::XMConvertToRadians(rot + m_GimmickInitAngle)) * distance;
			m_pos.z = pairPos.z - sin(DirectX::XMConvertToRadians(rot + m_GimmickInitAngle)) * distance;
		}
		break;
	// Z軸回転
	case SpinType::ZSpin:
		axis.z = -1.0f;
		for (int i = 0; i < m_TargetScrew.size(); i++)
		{
			rot += m_TargetScrew[i]->GetMultiplier() * 90.0f * m_TargetScrew[i]->GetRatio();
		}
		break;
	}

	GimmickSetQuat(axis, rot);
}

// 通常のネジを回す方向と逆方向に回されたときに呼ぶ
void SpinFloor::InvertGimmick(int index, float rotY)
{
	// 回転軸情報
	DirectX::XMFLOAT3 axis = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	// 角度
	float rot = 0.0f;

	// 回転ギミック
	switch (m_spinType)
	{
		// X軸回転
	case SpinType::XSpin:
		axis.x = 1.0f;
		for (int i = 0; i < m_TargetScrew.size(); i++)
		{
			rot -= m_TargetScrew[i]->GetMultiplier() * 90.0f * m_TargetScrew[i]->GetRatio();
		}
		break;
		// Y軸回転
	case SpinType::YSpin:
		axis.y = 1.0f;
		for (int i = 0; i < m_TargetScrew.size(); i++)
		{
			rot -= m_TargetScrew[i]->GetMultiplier() * 90.0f * m_TargetScrew[i]->GetRatio() - m_InitAngle[i];
		}

		// 一緒に動くギミックがあるなら回転と一緒に場所を動かす
		if (m_PairGimmick)
		{
			float3 pos = float3::Tofloat3(m_pos);
			float3 pairPos = float3::Tofloat3(m_PairGimmick->GetPos());

			float distance = float3::distance(pairPos, pos);	// 半径

			////float3 AN = pos.normalize();
			////float3 BN = pairPos.normalize();

			////float dot = float3::dot(AN, BN);
			////float initRot = acos(dot);
			m_pos.x = pairPos.x - cos(DirectX::XMConvertToRadians(rot - m_GimmickInitAngle)) * distance;
			m_pos.z = pairPos.z + sin(DirectX::XMConvertToRadians(rot - m_GimmickInitAngle)) * distance;
		}
		break;
		// Z軸回転
	case SpinType::ZSpin:
		axis.z = 1.0f;
		for (int i = 0; i < m_TargetScrew.size(); i++)
		{
			rot -= m_TargetScrew[i]->GetMultiplier() * 90.0f * m_TargetScrew[i]->GetRatio();
		}
		break;
	}

	// 回転
	GimmickSetQuat(axis, rot);
}

// 軸に合わせた回転
void SpinFloor::GimmickSetQuat(DirectX::XMFLOAT3 axis, float rot)
{
	m_quat = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);			// 角度初期化
	DirectX::XMVECTOR qRotate = DirectX::XMLoadFloat4(&m_quat);	// 型変換

	// 軸に合わせて回転
	DirectX::XMVECTOR quat = DirectX::XMQuaternionRotationAxis(
		DirectX::XMVectorSet(axis.x, axis.y, axis.z, 0.0f), DirectX::XMConvertToRadians(rot)
	);

	// クォータニオン掛け算
	qRotate = DirectX::XMQuaternionMultiply(qRotate, quat);

	// 角度更新
	DirectX::XMStoreFloat4(&m_quat, qRotate);

}
