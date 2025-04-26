// �C���N���[�h��
#include "PauseManager.h"
#include "SceneRoot.h"
#include "Input.h"

// �R���|�[�l���g
#include "ModelRenderer2D.h"

// �}�l�[�W���[
#include "SoundManager.h"	// �T�E���h�}�l�[�W���[

// ������
void PauseManager::Init()
{
	// �y�[�W�ݒ肠��UI
	// �������O����������␳����
	for (UIList::iterator itA = m_PauseUILists.begin(); itA != m_PauseUILists.end(); ++itA)
	{
		for (UIPosScaleList::iterator itB = m_UIPosScale.begin(); itB != m_UIPosScale.end(); ++itB)
		{
			// ��v�����玟��UI�`�F�b�N
			if (NameCheck(itA->second, itB)) continue;
		}
	}

	// �ʏ�UI
	// �������O����������␳����
	for (std::vector<GameObject*>::iterator it = m_pNormalUI.begin(); it != m_pNormalUI.end(); ++it)
	{
		for (UIPosScaleList::iterator itB = m_UIPosScale.begin(); itB != m_UIPosScale.end(); ++itB)
		{
			// ��v�����玟��UI�`�F�b�N
			if (NameCheck(it, itB)) continue;
		}
	}
}

// �X�V����
void PauseManager::Update()
{
	// �`���[�g���A��UI����
	for (UIList::iterator it = m_PauseUILists.begin(); it != m_PauseUILists.end(); ++it)
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
	// �Q�[���ɖ߂�
	else if (IsKeyTrigger(VK_ESCAPE))
	{
		// �S�ĕ`��t���OOFF
		m_PauseOpenFlg = false;
		for (UIList::iterator it = m_PauseUILists.begin(); it != m_PauseUILists.end(); ++it)
		{
			DrawFlgOFF(it);
		}
		for (std::vector<GameObject*>::iterator it = m_pNormalUI.begin(); it != m_pNormalUI.end(); ++it)
		{
			DrawFlgOFF(it);
		}
		// �|�[�Y��ʂ����
		SoundManager::GetInstance().playSound(SoundManager::SystemSE::PauseClose);
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
	else if (IsKeyTrigger('Z'))
	{
		// �^�C�g���ɖ߂�
		SceneRoot::SetNextScene(SceneBase::Scene::TITLE);
		// ����SE
		SoundManager::GetInstance().playSound(SoundManager::SystemSE::Decision);
	}
}

// ���O���m�F���č��W�A�T�C�Y��␳
bool PauseManager::NameCheck(std::vector<GameObject*>& itA, UIPosScaleList::iterator itB)
{
	// ���O�ɗp�ӂ���UI����(�y�[�W�ݒ肳��Ă����)
	for (auto it = itA.begin(); it != itA.end(); ++it)
	{
		// �I�u�W�F�N�g�ԍ�����v����̂����邩
		int uiNo = (*it)->Get2DObjNo();
		if (uiNo == itB->first)
		{
			GameObject* ui = (*it);
			DirectX::XMFLOAT3 pos = (itB->second)[0];	// ���W
			DirectX::XMFLOAT3 scale = (itB->second)[1];	// �T�C�Y

			// ���W�A�T�C�Y��␳
			ui->SetPos(pos);
			ui->SetScale(scale);

			return true;
		}
	}

	return false;
}

// ���O���m�F���č��W�A�T�C�Y��␳
bool PauseManager::NameCheck(std::vector<GameObject*>::iterator itA, UIPosScaleList::iterator itB)
{
	// ���O�ɗp�ӂ���UI����(�y�[�W�ݒ肳��Ă����)
	// �I�u�W�F�N�g�ԍ�����v����̂����邩
	int uiNo = (*itA)->Get2DObjNo();
	if (uiNo == itB->first)
	{
		GameObject* ui = (*itA);
		DirectX::XMFLOAT3 pos = (itB->second)[0];	// ���W
		DirectX::XMFLOAT3 scale = (itB->second)[1];	// �T�C�Y

		// ���W�A�T�C�Y��␳
		ui->SetPos(pos);
		ui->SetScale(scale);

		return true;
	
	}
	return false;
}


// UI�X�V����
void PauseManager::UIUpdate(UIList::iterator & pair)
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
void PauseManager::DrawFlgON(UIList::iterator & pair)
{
	ModelRenderer2D* modelRenderer2D;
	for (GameObject* obj : pair->second)
	{
		modelRenderer2D = obj->GetComponent<ModelRenderer2D>();
		modelRenderer2D->SetDraw(true);
	}
}

// �`��OFF
void PauseManager::DrawFlgOFF(UIList::iterator & pair)
{
	ModelRenderer2D* modelRenderer2D;
	for (GameObject* obj : pair->second)
	{
		modelRenderer2D = obj->GetComponent<ModelRenderer2D>();
		modelRenderer2D->SetDraw(false);
	}
}

// �`��OFF
void PauseManager::DrawFlgOFF(std::vector<GameObject*>::iterator & pair)
{
	ModelRenderer2D* modelRenderer2D;
	modelRenderer2D = (*pair)->GetComponent<ModelRenderer2D>();
	modelRenderer2D->SetDraw(false);
}