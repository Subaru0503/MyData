// �C���N���[�h��
#include "AfterGameOverManager.h"
#include "SceneRoot.h"
#include "Input.h"

// �}�l�[�W���[
#include "SoundManager.h"	// �T�E���h�}�l�[�W���[

// �X�V����
void AfterGameOverManager::Update()
{
	if (!m_pObj) return;

	// �����x���Ȃ��Ȃ��ĕ`��o���Ă邩�m�F
	bool draw = m_pObj->GetDraw();
	if (!draw)
	{
		m_pObj->Update();	// �X�V����
		// �X�J�C�h�[���X�V����
		m_pSkyDome->Update();	// ����Ȃ��悤�ɍX�V����
		return;
	}

	// ���g���C
	if (IsKeyTrigger('R'))
	{
		// �����X�e�[�W�����������
		SceneRoot::SetNextScene(SceneRoot::GetCurrentScene());
		// ���g���CSE
		SoundManager::GetInstance().playSound(SoundManager::SystemSE::Decision);
	}
	// �^�C�g���ɖ߂�
	else if (IsKeyTrigger(VK_ESCAPE))
	{
		// �^�C�g���ɖ߂�
		SceneRoot::SetNextScene(SceneBase::Scene::TITLE);
		// �^�C�g���߂�SE
		SoundManager::GetInstance().playSound(SoundManager::SystemSE::Decision);
	}

	// �X�J�C�h�[���X�V����
	m_pSkyDome->Update();	// ����Ȃ��悤�ɍX�V����
}