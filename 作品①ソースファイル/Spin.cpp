// �C���N���[�h��
#include "Spin.h"

#define SCREW_THREAD (10)	// �l�W�R��
#define INCH (25.4)			// �C���`

// X����]
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
	// ��]�擾
	DirectX::XMVECTOR qRotate = DirectX::XMLoadFloat4(&m_quat);

	DirectX::XMMATRIX RotMat = DirectX::XMMatrixRotationQuaternion(qRotate);

	float acc = AngularAcceleration();					// �p�����x

	rotX = sign * 1.0f / 2.0f * acc * (time * time);	// �p�x�v�Z

	// �i�ދ��������߂�
	float lead = INCH / SCREW_THREAD;					// ���[�h

	m_ScrewTravel = std::abs(lead / 360.0f * rotX);		// �i�񂾋���

	// ���ɍ��킹�ĉ�]
	DirectX::XMVECTOR quat = DirectX::XMQuaternionRotationAxis(
		DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), DirectX::XMConvertToRadians(rotX)
	);

	// �N�H�[�^�j�I���|���Z
	qRotate = DirectX::XMQuaternionMultiply(qRotate, quat);

	// �p�x�X�V
	DirectX::XMStoreFloat4(&m_quat, qRotate);

	transform->SetQuat(m_quat);
}

// Y����]
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
	// ��]�擾
	DirectX::XMVECTOR qRotate = DirectX::XMLoadFloat4(&m_quat);

	DirectX::XMMATRIX RotMat = DirectX::XMMatrixRotationQuaternion(qRotate);
	
	float acc = AngularAcceleration();						// �p�����x

	rotY = sign * 1.0f / 2.0f * acc * (time * time);	// �p�x�v�Z

	// �i�ދ��������߂�
	float lead = INCH / SCREW_THREAD;						// ���[�h

	m_ScrewTravel = std::abs(lead / 360.0f * rotY);			// �i�񂾋���

	// ���ɍ��킹�ĉ�]
	DirectX::XMVECTOR quat = DirectX::XMQuaternionRotationAxis(
		DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), DirectX::XMConvertToRadians(rotY)
	);

	// �N�H�[�^�j�I���|���Z
	qRotate = DirectX::XMQuaternionMultiply(qRotate, quat);

	// �p�x�X�V
	DirectX::XMStoreFloat4(&m_quat, qRotate);

	transform->SetQuat(m_quat);
}

// Z����]
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
	// ��]�擾
	DirectX::XMVECTOR qRotate = DirectX::XMLoadFloat4(&m_quat);

	DirectX::XMMATRIX RotMat = DirectX::XMMatrixRotationQuaternion(qRotate);

	float acc = AngularAcceleration();					// �p�����x

	rotZ = sign * 1.0f / 2.0f * acc * (time * time);	// �p�x�v�Z

	// �i�ދ��������߂�
	float lead = INCH / SCREW_THREAD;					// ���[�h

	m_ScrewTravel = std::abs(lead / 360.0f * rotZ);		// �i�񂾋���

	// ���ɍ��킹�ĉ�]
	DirectX::XMVECTOR quat = DirectX::XMQuaternionRotationAxis(
		DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), DirectX::XMConvertToRadians(rotZ)
	);

	// �N�H�[�^�j�I���|���Z
	qRotate = DirectX::XMQuaternionMultiply(qRotate, quat);

	// �p�x�X�V
	DirectX::XMStoreFloat4(&m_quat, qRotate);

	transform->SetQuat(m_quat);
}

// �p�����x�����߂�
float Spin::AngularAcceleration()
{
	float a = m_Torque / m_MomentOfInertia;

	return a;
}
