// �C���N���[�h��
#include "AfterGoalManager.h"
#include "SceneRoot.h"
#include "Input.h"

// �}�l�[�W���[
#include "SoundManager.h"	// �T�E���h�}�l�[�W���[

// �X�V����
void AfterGoalManager::Update()
{
	if (!m_pClear) return;

	float3 goalPos = float3::Tofloat3(m_pGoal->GetPos());
	float3 playerPos = float3::Tofloat3(m_pPlayer->GetPos());

	// �v���C���[�̍����ɍ��킹��
	goalPos.y = playerPos.y;

	// �S�[�������܂ł̋������v�Z
	float distance = float3::distance(goalPos, playerPos);

	if (distance > 0.1f)
	{
		m_pPlayer->MoveAfterGoal(m_pGoal);	// �����܂ňړ�������
		// �J�����ƃX�J�C�h�[���X�V����
		for (auto itA = m_pObjList.begin(); itA != m_pObjList.end(); ++itA)
		{
			GameObject* obj = *itA;
			obj->Execute();			// �X�V����
		}
		return;
	}
	// BGM���Đ����ĂȂ�������Đ�
	else if (!m_PlayBGM)
	{
		// �S�Ĕj��
		SoundManager::GetInstance().AllDeleteSpeaker();
		// �N���ABGM�Đ�
		SoundManager::GetInstance().playSound(SoundManager::BGM::Clear);
		m_PlayBGM = true;
	}

	// �J�����ƃX�J�C�h�[���X�V����
	for (auto itA = m_pObjList.begin(); itA != m_pObjList.end(); ++itA)
	{
		GameObject* obj = *itA;
		obj->Execute();			// �X�V����
	}

	// �����x���Ȃ��Ȃ��ĕ`��o���Ă邩�m�F
	bool draw = m_pClear->GetDraw();
	if (!draw)
	{
		m_pClear->Update();	// �X�V����
		AlphaUpdate();		// ����UI���ꏏ�ɂɕω�
		return;
	}

	// ���̃X�e�[�W��
	if (IsKeyTrigger(VK_RETURN))
	{
		// ���݂̃V�[���擾
		SceneBase::Scene scene = SceneRoot::GetCurrentScene();

		// 1���Z���Ď��̃V�[����
		// ���̃V�[�����Ȃ�������^�C�g���V�[���ɖ߂�
		scene = static_cast<SceneBase::Scene>((scene + 1) % SceneBase::Scene::MAX + (scene + 1) / SceneBase::Scene::MAX);

		// ���̃X�e�[�W�ɍs��
		SceneRoot::SetNextScene(scene);
		// ����SE
		SoundManager::GetInstance().playSound(SoundManager::SystemSE::Decision);
	}
	// ���g���C
	else if (IsKeyTrigger('R'))
	{
		// �����X�e�[�W�����������
		SceneRoot::SetNextScene(SceneRoot::GetCurrentScene());
		// ����SE
		SoundManager::GetInstance().playSound(SoundManager::SystemSE::Decision);
	}
	// �^�C�g���ɖ߂�
	else if (IsKeyTrigger(VK_ESCAPE))
	{
		// �^�C�g���ɖ߂�
		SceneRoot::SetNextScene(SceneBase::Scene::TITLE);
		// ����SE
		SoundManager::GetInstance().playSound(SoundManager::SystemSE::Decision);
	}
}

// �A���t�@�l�ω�
void AfterGoalManager::AlphaUpdate()
{
	for (int i = 0; i < m_TimeObj.size(); i++)
	{
		m_TimeObj[i]->AlphaUpdate();
	}
}