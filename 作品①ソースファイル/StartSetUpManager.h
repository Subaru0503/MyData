// �Q�[���X�^�[�g�����Ǘ��N���X

// �C���N���[�h�K�[�h
#ifndef __START_SETUP_MANAGER_H__
#define __START_SETUP_MANAGER_H__

// �C���N���[�h��
#include "GameObject.hpp"
#include "Ready.h"

// �R���|�[�l���g
#include "ModelRenderer2D.h"

// �N���X��`
class StartSetUpManager
{
public:
	inline static StartSetUpManager& GetInstance()
	{
		static StartSetUpManager instance;
		return instance;
	}

	// �X�V����
	void Update();

	// ���Z�b�g�֐�
	inline void Reset()
	{
		m_StartSetUpFlg = false;
	}

	// �Z�b�g�֐�
	inline void SetStartSetUpUI(Ready* obj)
	{
		m_UI = obj;
		obj->GetComponent<ModelRenderer2D>()->SetDraw(false);
	}

	// �Q�b�g�֐�
	inline bool GetStartSetUp()
	{
		return m_StartSetUpFlg;
	}

private:

	StartSetUpManager()
	{
		m_StartSetUpFlg = false;
	};
	~StartSetUpManager()
	{
	};

private:
	Ready* m_UI;

	bool m_StartSetUpFlg;	// �X�^�[�g���������ꂽ�t���O
};

#endif // __START_SETUP_MANAGER_H__