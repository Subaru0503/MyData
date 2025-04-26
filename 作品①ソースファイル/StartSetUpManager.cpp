// �C���N���[�h��
#include "StartSetUpManager.h"

// �}�l�[�W���[
#include "PauseManager.h"	// �|�[�Y��ʃ}�l�[�W���[

// �R���|�[�l���g
#include "ModelRenderer2D.h"

// �X�V����
void StartSetUpManager::Update()
{
	ModelRenderer2D* modelRenderer2D = m_UI->GetComponent<ModelRenderer2D>();

	m_UI->Execute();
	if (!m_UI->GetStart() && !modelRenderer2D->GetDraw())
	{
		modelRenderer2D->SetDraw(true);
	}

	// �Q�[���X�^�[�g�t���O�������Ă���
	if (m_UI->GetStart())
	{
		// ���W��T�C�Y��ݒ肵�����Ƃ�
		PauseManager::GetInstance().Init();			// ����������
		m_StartSetUpFlg = true;
	}
}
