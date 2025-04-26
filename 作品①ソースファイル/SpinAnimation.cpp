// �C���N���[�h��
#include "SpinAnimation.h"

// �R���X�g���N�^
SpinAnimation::SpinAnimation()
{
	// �����o�ϐ�������
	m_CurrentSpinNum = 0;
	m_SpinNum = 0;
	m_Rot = 0.0f;
	m_DeltaRot = 0.0f;
	m_Axis = DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 0.0f);
	m_SpinStop = true;
}

// �f�X�g���N�^
SpinAnimation::~SpinAnimation()
{
}

// �X�V����
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

// ��]�A�j���[�V����
void SpinAnimation::Spin()
{
	DirectX::XMFLOAT4 quat = transform->GetQuat();

	// ��]�擾
	DirectX::XMVECTOR qRotate = DirectX::XMLoadFloat4(&quat);

	DirectX::XMMATRIX RotMat = DirectX::XMMatrixRotationQuaternion(qRotate);

	// ���ɍ��킹�ĉ�]
	DirectX::XMVECTOR newquat = DirectX::XMQuaternionRotationAxis(
		DirectX::XMVectorSet(m_Axis.x, m_Axis.y, m_Axis.z, m_Axis.w), DirectX::XMConvertToRadians(m_Rot)
	);

	// �N�H�[�^�j�I���|���Z
	//qRotate = DirectX::XMQuaternionMultiply(qRotate, newquat);

	// �p�x�X�V
	DirectX::XMStoreFloat4(&quat, newquat);

	transform->SetQuat(quat);
}

// ��]���Z�b�g
void SpinAnimation::SetSpinNum(int num)
{
	m_SpinNum = num;
	m_SpinStop = false;
}

// ��]���ݒ�
void SpinAnimation::SetAxis(DirectX::XMFLOAT4 axis)
{
	m_Axis = axis;
}

// ��]�ʐݒ�
void SpinAnimation::SetDeltaRot(float rot)
{
	m_DeltaRot = rot;
}

// ��]���擾
int SpinAnimation::GetSpinNum()
{
	return m_SpinNum;
}

// ��]�񐔂�Ԃ�
int SpinAnimation::GetCurrentSpinNum()
{
	return m_CurrentSpinNum;
}

// ��]���~�܂��Ă邩�擾
bool SpinAnimation::GetStop()
{
	return m_SpinStop;
}
