// インクルード部
#include "Spin.h"

#define SCREW_THREAD (10)	// ネジ山数
#define INCH (25.4)			// インチ

// X軸回転
void Spin::XSpin(bool Right, float time)
{
	int sign;

	if (Right)
	{
		sign = -1;
	}
	else
	{
		sign = 1;
	}

	float rotX;
	DirectX::XMFLOAT4 m_quat = transform->GetQuat();
	// 回転取得
	DirectX::XMVECTOR qRotate = DirectX::XMLoadFloat4(&m_quat);

	DirectX::XMMATRIX RotMat = DirectX::XMMatrixRotationQuaternion(qRotate);

	float acc = AngularAcceleration();					// 角加速度

	rotX = sign * 1.0f / 2.0f * acc * (time * time);	// 角度計算

	// 進む距離を求める
	float lead = INCH / SCREW_THREAD;					// リード

	m_ScrewTravel = std::abs(lead / 360.0f * rotX);		// 進んだ距離

	// 軸に合わせて回転
	DirectX::XMVECTOR quat = DirectX::XMQuaternionRotationAxis(
		DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), DirectX::XMConvertToRadians(rotX)
	);

	// クォータニオン掛け算
	qRotate = DirectX::XMQuaternionMultiply(qRotate, quat);

	// 角度更新
	DirectX::XMStoreFloat4(&m_quat, qRotate);

	transform->SetQuat(m_quat);
}

// Y軸回転
void Spin::YSpin(bool Right, float time)
{
	int sign;

	if (Right)
	{
		sign = -1;
	}
	else
	{
		sign = 1;
	}

	float rotY;
	DirectX::XMFLOAT4 m_quat = transform->GetQuat();
	// 回転取得
	DirectX::XMVECTOR qRotate = DirectX::XMLoadFloat4(&m_quat);

	DirectX::XMMATRIX RotMat = DirectX::XMMatrixRotationQuaternion(qRotate);
	
	float acc = AngularAcceleration();						// 角加速度

	rotY = sign * 1.0f / 2.0f * acc * (time * time);	// 角度計算

	// 進む距離を求める
	float lead = INCH / SCREW_THREAD;						// リード

	m_ScrewTravel = std::abs(lead / 360.0f * rotY);			// 進んだ距離

	// 軸に合わせて回転
	DirectX::XMVECTOR quat = DirectX::XMQuaternionRotationAxis(
		DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), DirectX::XMConvertToRadians(rotY)
	);

	// クォータニオン掛け算
	qRotate = DirectX::XMQuaternionMultiply(qRotate, quat);

	// 角度更新
	DirectX::XMStoreFloat4(&m_quat, qRotate);

	transform->SetQuat(m_quat);
}

// Z軸回転
void Spin::ZSpin(bool Right, float time)
{
	int sign;

	if (Right)
	{
		sign = -1;
	}
	else
	{
		sign = 1;
	}

	float rotZ;
	DirectX::XMFLOAT4 m_quat = transform->GetQuat();
	// 回転取得
	DirectX::XMVECTOR qRotate = DirectX::XMLoadFloat4(&m_quat);

	DirectX::XMMATRIX RotMat = DirectX::XMMatrixRotationQuaternion(qRotate);

	float acc = AngularAcceleration();					// 角加速度

	rotZ = sign * 1.0f / 2.0f * acc * (time * time);	// 角度計算

	// 進む距離を求める
	float lead = INCH / SCREW_THREAD;					// リード

	m_ScrewTravel = std::abs(lead / 360.0f * rotZ);		// 進んだ距離

	// 軸に合わせて回転
	DirectX::XMVECTOR quat = DirectX::XMQuaternionRotationAxis(
		DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), DirectX::XMConvertToRadians(rotZ)
	);

	// クォータニオン掛け算
	qRotate = DirectX::XMQuaternionMultiply(qRotate, quat);

	// 角度更新
	DirectX::XMStoreFloat4(&m_quat, qRotate);

	transform->SetQuat(m_quat);
}

// 角加速度を求める
float Spin::AngularAcceleration()
{
	float a = m_Torque / m_MomentOfInertia;

	return a;
}
