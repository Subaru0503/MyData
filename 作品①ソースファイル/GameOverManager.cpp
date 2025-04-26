// �C���N���[�h��
#include "GameOverManager.h"

// �}�l�[�W���[
#include "TimeManager.h"	// �^�C���}�l�[�W���[
#include "SoundManager.h"	// �T�E���h�}�l�[�W���[

// �X�V����
void GameOverManager::Update()
{
	// �v���C���[��NULL��������
	// �Q�[���I�[�o�[�ɂȂ��Ă��珈�����Ȃ�
	if (!m_pPlayer || m_GameOverFlg) return;

	// �������`�F�b�N
	FallDeadCheck();

	// �^�C���I�[�o�[�`�F�b�N
	TimeOverCheck();
}

// �������`�F�b�N
void GameOverManager::FallDeadCheck()
{
	DirectX::XMFLOAT3 pos = m_pPlayer->GetPos();

	if (pos.y <= -10.0f)
	{
		m_GameOverFlg = true;
	}
}

// �^�C���I�[�o�[�`�F�b�N
void GameOverManager::TimeOverCheck()
{
	// ���Ԏ擾
	float time = TimeManager::GetInstance().GetTime();

	if (time <= 0.0f)
	{
		m_GameOverFlg = true;
		SoundManager::GetInstance().playSound(SoundManager::SystemSE::TimeOver);
	}
}
