///////////////////////////////////////
//
// �I�u�W�F�N�g���Z�b�g�Ǘ��N���X
//
// �I�u�W�F�N�g�̔z�u�������ʒu�ɖ߂�
//
///////////////////////////////////////

// �C���N���[�h��
#include "ResetManager.h"
#include "SceneRoot.h"
#include "Input.h"

// �}�l�[�W���[
#include "SoundManager.h"	// �T�E���h�}�l�[�W���[

// �X�V����
void ResetManager::Update()
{
	// ���Z�b�g�O����
	if (IsKeyTrigger('R') && !m_ResetFlg &&
		!m_pFade->GetPlay())
	{
		// �t�F�[�h�A�E�g
		m_pFade->Start(FADE_OUT, FADE_OUT_TIME, Fade::FadeColor::White);

		// ���Z�b�g�t���O���グ��
		m_ResetFlg = true;

		// ����SE
		SoundManager::GetInstance().playSound(SoundManager::SystemSE::Decision);
	}

	// ���Z�b�g�t���O���オ���Ă���
	if (m_ResetFlg && !m_pFade->GetPlay())
	{
		// �I�u�W�F�N�g��������Ԃɖ߂�
		ResetState();
	}
}

// �I�u�W�F�N�g��������Ԃɖ߂�
void ResetManager::ResetState()
{
	// �o�^���Ă��镪���[�v���Ė߂�
	for (auto it = m_Obj.begin(); it != m_Obj.end(); it++)
	{
		// �f�[�^�^��ϊ�
		GameObject* obj = *(it);

		// ������Ԃɖ߂�
		obj->ResetState();
	}

	// �t�F�[�h�C��
	m_pFade->Start(FADE_IN, FADE_IN_TIME, Fade::FadeColor::White);

	// ���Z�b�g�t���O��������
	m_ResetFlg = false;
}

// �t�F�[�h�Z�b�g
void ResetManager::SetFade(Fade * fade)
{
	m_pFade = fade;
}

// ���Z�b�g�t���O��Ԃ�
bool ResetManager::GetResetFlg()
{
	return m_ResetFlg;
}
