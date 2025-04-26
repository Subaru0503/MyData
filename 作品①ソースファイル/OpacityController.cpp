// �C���N���[�h��
#include "OpacityController.h"

// �R���X�g���N�^
Opacity::Opacity()
{
	m_Alpha = 1.0f;
	m_ClearFlg = false;
}

// �f�X�g���N�^
Opacity::~Opacity()
{
}

// �X�V����
void Opacity::Execute()
{
	Blink();
}

// �����x�ω�
void Opacity::Blink()
{
	// �����ɂȂ��Ă�����
	if (m_ClearFlg)
	{
		m_Alpha += m_Value;		// �����x��������
		// �����x���Ȃ��Ȃ�����
		if (m_Alpha >= 1.0f)
		{
			m_ClearFlg = false;	// �t���O����
		}
	}
	// �����x���Ȃ��Ȃ��Ă�����
	else
	{
		m_Alpha -= m_Value;		// �����x���グ��
		// �����ɂȂ�����
		if (m_Alpha <= 0.0f)
		{
			m_ClearFlg = true;	// �t���O�グ
		}
	}

	// �����x�X�V
	m_Param->color.w = m_Alpha;
}
