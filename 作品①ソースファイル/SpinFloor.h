// ��]���M�~�b�N�N���X

// �C���N���[�h�K�[�h
#ifndef __SPIN_FLOOR_H__
#define __SPIN_FLOOR_H__

// �C���N���[�h��
#include "GimmickBase.h"
#include <DirectXMath.h>

// �N���X��`
class SpinFloor : public GimmickBase
{
public:
	enum class SpinType
	{
		XSpin,	// X����]
		YSpin,	// Y����]
		ZSpin,	// Z����]
	};
public:
	SpinFloor(std::string name = "SpinFloor");	// �R���X�g���N�^
	~SpinFloor();								// �f�X�g���N�^

	// �^�[�Q�b�g�I�u�W�F�N�g�̏���
	void Gimmick(int index, float rotY);
	// �ʏ�̃l�W���񂷕����Ƌt�����ɉ񂳂ꂽ�Ƃ��ɌĂ�
	void InvertGimmick(int index, float rotY);

	// ��]�^�C�v�Z�b�g
	inline void SetType(SpinType type)
	{
		m_spinType = type;
	}
	// �����p�x�ݒ�
	inline void SetInitAngle()
	{
		for (int i = 0; i < m_TargetScrew.size(); i++)
		{
			m_InitAngle.push_back(m_TargetScrew[i]->GetMultiplier() * 90.0f * m_TargetScrew[i]->GetRatio());
		}

		// �y�A�M�~�b�N���Ȃ�������I��
		if (!m_PairGimmick) return;

		// �M�~�b�N�̏����ʒu�Ɖ~����̃X�^�[�g�ʒu�Ƃ̊p�x�����߂�

		float3 pos = float3::Tofloat3(m_pos);
		float3 pairPos = float3::Tofloat3(m_PairGimmick->GetPos());

		float distance = float3::distance(pairPos, pos);	// ���a


		DirectX::XMVECTOR difference = DirectX::XMVectorSubtract(	// ���Z��(����1 - ����2)
			DirectX::XMLoadFloat3(&m_pos),		// �M�~�b�N�̍��W
			DirectX::XMLoadFloat3(&m_PairGimmick->GetPos())			// �y�A�M�~�b�N�̍��W
		);
		// �I�u�W�F�N�g�ւ̃x�N�g���𐳋K��
		difference = DirectX::XMVector3Normalize(difference);

		// �~����ɂ�����W�����߂�
		DirectX::XMFLOAT3 circlePoint = m_PairGimmick->GetPos();
		circlePoint.x -= distance;

		// X���ɉ������x�N�g��
		DirectX::XMVECTOR circleDir = DirectX::XMVectorSubtract(
			DirectX::XMLoadFloat3(&circlePoint),
			DirectX::XMLoadFloat3(&m_PairGimmick->GetPos())
		);

		// ���K��
		circleDir = DirectX::XMVector3Normalize(circleDir);

		// �I�u�W�F�N�g�ւ̕����x�N�g���ƃv���C���[�̌����̃x�N�g���̊Ԃ̃��W�A���p���擾
		DirectX::XMStoreFloat(&m_GimmickInitAngle, DirectX::XMVector3AngleBetweenNormals(
			difference,				// �y�A�M�~�b�N���玩���ւ̕����x�N�g��
			circleDir				// X���ɉ������x�N�g�� 
		));

		m_GimmickInitAngle = DirectX::XMConvertToDegrees(m_GimmickInitAngle);
	}
private:

	// ���ɍ��킹����]
	void GimmickSetQuat(DirectX::XMFLOAT3 axis, float rot);
private:
	SpinType m_spinType;	// ��]�^�C�v
	std::vector<float> m_InitAngle; // �l�W�̈ʒu�ɂ�鏉���p�x
	float m_GimmickInitAngle;		// �M�~�b�N�̏����ʒu�Ɖ~����̃X�^�[�g�ʒu�Ƃ̊p�x
};

#endif // __SPIN_FLOOR_H__