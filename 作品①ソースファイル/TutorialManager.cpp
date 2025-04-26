// �C���N���[�h��
#include "TutorialManager.h"
#include "Input.h"

// �R���|�[�l���g
#include "ModelRenderer2D.h"

// �}�l�[�W���[
#include "SoundManager.h"	// �T�E���h�}�l�[�W���[

// �X�V����
void TutorialManager::Update()
{
	// �`���[�g���A��UI����
	for (UIList::iterator it = m_UILists.begin(); it != m_UILists.end(); ++it)
	{
		if (it->first == m_Page)
		{
			UIUpdate(it);	// UI�X�V����
			DrawFlgON(it);	// �`��t���OON
		}
		else
		{
			DrawFlgOFF(it);	// �`��t���OOFF
		}
	}

	// 2�y�[�W�ڂ�
	if (IsKeyTrigger(VK_RIGHT) || IsKeyTrigger('D'))
	{
		m_Page = 2;	// 2�y�[�W��
		// �J��SE�Đ�
		SoundManager::GetInstance().playSound(SoundManager::SystemSE::Select);
	}
	// 1�y�[�W�ڂ�
	else if (IsKeyTrigger(VK_LEFT) || IsKeyTrigger('A'))
	{
		m_Page = 1;	// 1�y�[�W��
		// �J��SE�Đ�
		SoundManager::GetInstance().playSound(SoundManager::SystemSE::Select);
	}
	// �Q�[���X�^�[�g
	else if (m_Page == 2 && IsKeyTrigger(VK_RETURN))
	{
		// �S�ĕ`��t���OOFF
		m_TutorialFlg = false;
		for (UIList::iterator it = m_UILists.begin(); it != m_UILists.end(); ++it)
		{
			DrawFlgOFF(it);
		}
		for (std::vector<GameObject*>::iterator it = m_pNormalUI.begin(); it != m_pNormalUI.end(); ++it)
		{
			DrawFlgOFF(it);
		}

		// ����SE�Đ�
		SoundManager::GetInstance().playSound(SoundManager::SystemSE::Decision);
	}
}

// UI�X�V����
void TutorialManager::UIUpdate(UIList::iterator & pair)
{
	// �J���Ă���y�[�WUI�X�V����
	for (GameObject* obj : pair->second)
	{
		obj->Execute();
	}
	// �y�[�W�֌W�Ȃ��\������Ă���UI�X�V����
	for (std::vector<GameObject*>::iterator it = m_pNormalUI.begin(); it != m_pNormalUI.end(); ++it)
	{
		(*it)->GetComponent<ModelRenderer2D>()->SetDraw(true);
		(*it)->Execute();
	}
}

// �`��ON
void TutorialManager::DrawFlgON(UIList::iterator & pair)
{
	ModelRenderer2D* modelRenderer2D;
	for (GameObject* obj : pair->second)
	{
		modelRenderer2D = obj->GetComponent<ModelRenderer2D>();
		modelRenderer2D->SetDraw(true);
	}
}

// �`��OFF
void TutorialManager::DrawFlgOFF(UIList::iterator & pair)
{
	ModelRenderer2D* modelRenderer2D;
	for (GameObject* obj : pair->second)
	{
		modelRenderer2D = obj->GetComponent<ModelRenderer2D>();
		modelRenderer2D->SetDraw(false);
	}
}

// �`��OFF
void TutorialManager::DrawFlgOFF(std::vector<GameObject*>::iterator & pair)
{
	ModelRenderer2D* modelRenderer2D;
	modelRenderer2D = (*pair)->GetComponent<ModelRenderer2D>();
	modelRenderer2D->SetDraw(false);
}