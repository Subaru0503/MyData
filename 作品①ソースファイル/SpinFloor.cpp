// ��]�M�~�b�N�N���X

// �C���N���[�h��
#include "SpinFloor.h"

// �V�X�e��
#include "Input.h"

// �R���X�g���N�^
SpinFloor::SpinFloor(std::string name)
	: GimmickBase(name)
{

}

// �f�X�g���N�^
SpinFloor::~SpinFloor()
{
}

// �^�[�Q�b�g�I�u�W�F�N�g�̏���
void SpinFloor::Gimmick(int index, float rotY)
{
	// ��]�����
	DirectX::XMFLOAT3 axis = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	// �p�x
	float rot = 0.0f;

	// ��]�M�~�b�N
	switch (m_spinType)
	{
	// X����]
	case SpinType::XSpin:
		axis.x = -1.0f;
		for (int i = 0; i < m_TargetScrew.size(); i++)
		{
			rot += m_TargetScrew[i]->GetMultiplier() * 90.0f * m_TargetScrew[i]->GetRatio();
		}
		break;
	// Y����]
	case SpinType::YSpin:
		axis.y = -1.0f;
		for (int i = 0; i < m_TargetScrew.size(); i++)
		{
			rot += m_TargetScrew[i]->GetMultiplier() * 90.0f * m_TargetScrew[i]->GetRatio() - m_InitAngle[i];
		}

		// �ꏏ�ɓ����M�~�b�N������Ȃ��]�ƈꏏ�ɏꏊ�𓮂���
		if (m_PairGimmick)
		{
			float3 pos = float3::Tofloat3(m_pos);
			float3 pairPos = float3::Tofloat3(m_PairGimmick->GetPos());

			float distance = float3::distance(pairPos, pos);	// ���a

			////float3 AN = pos.normalize();
			////float3 BN = pairPos.normalize();

			////float dot = float3::dot(AN, BN);
			////float initRot = acos(dot);

			m_pos.x = pairPos.x - cos(DirectX::XMConvertToRadians(rot + m_GimmickInitAngle)) * distance;
			m_pos.z = pairPos.z - sin(DirectX::XMConvertToRadians(rot + m_GimmickInitAngle)) * distance;
		}
		break;
	// Z����]
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

// �ʏ�̃l�W���񂷕����Ƌt�����ɉ񂳂ꂽ�Ƃ��ɌĂ�
void SpinFloor::InvertGimmick(int index, float rotY)
{
	// ��]�����
	DirectX::XMFLOAT3 axis = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	// �p�x
	float rot = 0.0f;

	// ��]�M�~�b�N
	switch (m_spinType)
	{
		// X����]
	case SpinType::XSpin:
		axis.x = 1.0f;
		for (int i = 0; i < m_TargetScrew.size(); i++)
		{
			rot -= m_TargetScrew[i]->GetMultiplier() * 90.0f * m_TargetScrew[i]->GetRatio();
		}
		break;
		// Y����]
	case SpinType::YSpin:
		axis.y = 1.0f;
		for (int i = 0; i < m_TargetScrew.size(); i++)
		{
			rot -= m_TargetScrew[i]->GetMultiplier() * 90.0f * m_TargetScrew[i]->GetRatio() - m_InitAngle[i];
		}

		// �ꏏ�ɓ����M�~�b�N������Ȃ��]�ƈꏏ�ɏꏊ�𓮂���
		if (m_PairGimmick)
		{
			float3 pos = float3::Tofloat3(m_pos);
			float3 pairPos = float3::Tofloat3(m_PairGimmick->GetPos());

			float distance = float3::distance(pairPos, pos);	// ���a

			////float3 AN = pos.normalize();
			////float3 BN = pairPos.normalize();

			////float dot = float3::dot(AN, BN);
			////float initRot = acos(dot);
			m_pos.x = pairPos.x - cos(DirectX::XMConvertToRadians(rot - m_GimmickInitAngle)) * distance;
			m_pos.z = pairPos.z + sin(DirectX::XMConvertToRadians(rot - m_GimmickInitAngle)) * distance;
		}
		break;
		// Z����]
	case SpinType::ZSpin:
		axis.z = 1.0f;
		for (int i = 0; i < m_TargetScrew.size(); i++)
		{
			rot -= m_TargetScrew[i]->GetMultiplier() * 90.0f * m_TargetScrew[i]->GetRatio();
		}
		break;
	}

	// ��]
	GimmickSetQuat(axis, rot);
}

// ���ɍ��킹����]
void SpinFloor::GimmickSetQuat(DirectX::XMFLOAT3 axis, float rot)
{
	m_quat = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);			// �p�x������
	DirectX::XMVECTOR qRotate = DirectX::XMLoadFloat4(&m_quat);	// �^�ϊ�

	// ���ɍ��킹�ĉ�]
	DirectX::XMVECTOR quat = DirectX::XMQuaternionRotationAxis(
		DirectX::XMVectorSet(axis.x, axis.y, axis.z, 0.0f), DirectX::XMConvertToRadians(rot)
	);

	// �N�H�[�^�j�I���|���Z
	qRotate = DirectX::XMQuaternionMultiply(qRotate, quat);

	// �p�x�X�V
	DirectX::XMStoreFloat4(&m_quat, qRotate);

}
