// �|�[�Y��ʊǗ��N���X

// �C���N���[�h�K�[�h
#ifndef __PAUSE_MENU_MANAGER_H__
#define __PAUSE_MENU_MANAGER_H__

// �C���N���[�h��
#include "GameObject.hpp"
#include <map>
// �R���|�[�l���g
#include "ModelRenderer2D.h"

// �N���X��`
class PauseManager
{
private:
	using UIList = std::map<int, std::vector<GameObject*>>;
	using UIPosScaleList = std::map<int, std::vector<DirectX::XMFLOAT3>>;
public:
	inline static PauseManager& GetInstance()
	{
		static PauseManager instance;
		return instance;
	}

	// ������
	void Init();

	// �X�V����
	void Update();

	// �I�u�W�F�N�g�폜
	inline void RemoveALLObj()
	{
		// �S�č폜
		for (auto it = m_PauseUILists.begin(); it != m_PauseUILists.end();)
		{
			it = m_PauseUILists.erase(it);
		}
		for (auto it = m_pNormalUI.begin(); it != m_pNormalUI.end();)
		{
			it = m_pNormalUI.erase(it);
		}
		for (auto it = m_UIPosScale.begin(); it != m_UIPosScale.end();)
		{
			it = m_UIPosScale.erase(it);
		}
	}

	inline void PauseOpen()
	{
		m_PauseOpenFlg = true;
	}

	// ���Z�b�g�֐�
	inline void Reset()
	{
		m_PauseOpenFlg = false;
		m_Page = 1;
	}

	// �Z�b�g�֐�
	inline void SetPauseUI(int page, GameObject* obj)
	{
		m_PauseUILists[page].push_back(obj);
		obj->GetComponent<ModelRenderer2D>()->SetDraw(false);
	}
	inline void SetNormalUI(GameObject* obj)
	{
		m_pNormalUI.push_back(obj);
		obj->GetComponent<ModelRenderer2D>()->SetDraw(false);
	}
	inline void SetPosScale(int no, DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 scale)
	{
		m_UIPosScale[no].push_back(pos);
		m_UIPosScale[no].push_back(scale);
	}

	// �Q�b�g�֐�
	inline bool GetPause()
	{
		return m_PauseOpenFlg;
	}

private:

	PauseManager()
	{
		m_Page = 1;
		m_PauseOpenFlg = false;
	};
	~PauseManager()
	{
	};

	// ���O���m�F���č��W�A�T�C�Y��␳
	bool NameCheck(std::vector<GameObject*>& itA, UIPosScaleList::iterator itB);
	bool NameCheck(std::vector<GameObject*>::iterator itA, UIPosScaleList::iterator itB);


	// UI�X�V����
	void UIUpdate(UIList::iterator& pair);

	// �`��ON
	void DrawFlgON(UIList::iterator& pair);
	// �`��OFF
	void DrawFlgOFF(UIList::iterator& pair);
	void DrawFlgOFF(std::vector<GameObject*>::iterator& pair);
private:
	UIList m_PauseUILists;					// �`�悷��UI���X�g
	std::vector<GameObject*> m_pNormalUI;	// �y�[�W�Ɋ֌W�Ȃ��\������UI
	UIPosScaleList m_UIPosScale;			// �`�悷��UI�̍��W�ƃT�C�Y

	int m_Page;				// ���݊J���Ă�y�[�W
	bool m_PauseOpenFlg;	// �|�[�Y��ʂ��J���Ă���t���O
};

#endif // __PAUSE_MENU_MANAGER_H__