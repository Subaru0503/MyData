///////////////////////////////////////
//
//  �ꐶ�񂹂�l�W�N���X
//
///////////////////////////////////////

// �C���N���[�h��
#include "EndLess.h"

//----�}�l�[�W���[----
#include "SoundManager.h"	// �T�E���h�}�l�[�W���[

// �R���X�g���N�^
EndLess::EndLess(std::string name)
	: Screw(name)
{

}

// �f�X�g���N�^
EndLess::~EndLess()
{
}

// ��]�֐�
void EndLess::ObjRightSpin(bool Right)
{
	//----�ϐ��錾----

	// �Đ��I���t���O
	bool PlayEnd;

	// ���Ԋm�F
	if (!m_Nut)
	{
		MessageBox(NULL, "�i�b�g�̐ݒ肪����ĂȂ�", "Screw.cpp", MB_OK);
	}

	// ��]�t���O�グ
	m_SpinFlg = true;

	// �Đ��I���t���O���擾
	PlayEnd = SoundManager::GetInstance().CheckSoundEnd(SoundManager::ScrewSE::Spin);

	// �E��]
	if (m_Nut->GetPos().y <= m_pos.y && Right)
	{
		// Y���E��]
		_spin->YSpin();

		// �Đ����ĂȂ�������
		if (PlayEnd)
		{
			// ��]SE
			SoundManager::GetInstance().playSound(SoundManager::ScrewSE::Spin);
		}

		// �񂵐؂���SE�Đ��σt���O��������
		m_SpinMaxPlayingSE = false;
	}
	// ����]
	else if (m_Nut->GetPos().y + 0.5f >= m_pos.y && !Right)
	{
		// Y������]
		_spin->YSpin(false);

		// �Đ����ĂȂ�������
		if (PlayEnd)
		{
			// ��]SE
			SoundManager::GetInstance().playSound(SoundManager::ScrewSE::Spin);
		}

		// �񂵐؂���SE�Đ��σt���O��������
		m_SpinMaxPlayingSE = false;
	}
}
