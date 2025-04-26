// インクルード部
#include "SpinAnimation.h"

// コンストラクタ
SpinAnimation::SpinAnimation()
{
	// メンバ変数初期化
	m_CurrentSpinNum = 0;
	m_SpinNum = 0;
	m_Rot = 0.0f;
	m_DeltaRot = 0.0f;
	m_Axis = DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 0.0f);
	m_SpinStop = true;
}

// デストラクタ
SpinAnimation::~SpinAnimation()
{
}

// 更新処理
void SpinAnimation::Execute()
{
	if (m_SpinStop) return;

	m_Rot += m_DeltaRot;
	Spin();

	m_CurrentSpinNum = (int)(m_Rot / 360.0f);

	if (m_SpinNum == m_CurrentSpinNum)
	{
		m_SpinStop = true;
		m_Rot = 0.0f;
	}
}

// 回転アニメーション
void SpinAnimation::Spin()
{
	DirectX::XMFLOAT4 quat = transform->GetQuat();

	// 回転取得
	DirectX::XMVECTOR qRotate = DirectX::XMLoadFloat4(&quat);

	DirectX::XMMATRIX RotMat = DirectX::XMMatrixRotationQuaternion(qRotate);

	// 軸に合わせて回転
	DirectX::XMVECTOR newquat = DirectX::XMQuaternionRotationAxis(
		DirectX::XMVectorSet(m_Axis.x, m_Axis.y, m_Axis.z, m_Axis.w), DirectX::XMConvertToRadians(m_Rot)
	);

	// クォータニオン掛け算
	//qRotate = DirectX::XMQuaternionMultiply(qRotate, newquat);

	// 角度更新
	DirectX::XMStoreFloat4(&quat, newquat);

	transform->SetQuat(quat);
}

// 回転数セット
void SpinAnimation::SetSpinNum(int num)
{
	m_SpinNum = num;
	m_SpinStop = false;
}

// 回転軸設定
void SpinAnimation::SetAxis(DirectX::XMFLOAT4 axis)
{
	m_Axis = axis;
}

// 回転量設定
void SpinAnimation::SetDeltaRot(float rot)
{
	m_DeltaRot = rot;
}

// 回転数取得
int SpinAnimation::GetSpinNum()
{
	return m_SpinNum;
}

// 回転回数を返す
int SpinAnimation::GetCurrentSpinNum()
{
	return m_CurrentSpinNum;
}

// 回転が止まってるか取得
bool SpinAnimation::GetStop()
{
	return m_SpinStop;
}
