// �C���N���[�h��
#include "Jump.h"

// �R���X�g���N�^
Jump::Jump()
	: m_JumpForce(0.0f)
	, m_CurrentTime(0.0f)
{

}

// �X�V����
void Jump::Execute()
{
	// �W�����v�����ĂȂ������珈�������Ȃ�
	if (m_JumpForce <= 0.0f) return;

	DirectX::XMFLOAT3 newPos = transform->GetPos();	// ���W�擾

	newPos.y += m_JumpForce * (1.0f - m_CurrentTime);		// �W�����v

	transform->SetPos(newPos);						// ���W�Z�b�g

	m_CurrentTime += 1.0f / 60.0f;	// ���Ԍo��

	// 1�b�𒴂�����l�����Z�b�g
	if (m_CurrentTime >= 1.0f)
	{
		m_JumpForce = 0.0f;		// �W�����v�̓��Z�b�g
		m_CurrentTime = 0.0f;	// �o�ߎ��ԃ��Z�b�g
	}
}
