// �`���[�g���A���Ǘ��N���X

// �C���N���[�h�K�[�h
#ifndef __TUTORIAL_MANAGER_H__
#define __TUTORIAL_MANAGER_H__

// �C���N���[�h��
#include "GameObject.hpp"
#include <map>
// �R���|�[�l���g
#include "ModelRenderer2D.h"

// �N���X��`
class TutorialManager
{
private:
	using UIList = std::map<int, std::vector<GameObject*>>;
public:
	inline static TutorialManager& GetInstance()
	{
		static TutorialManager instance;
		return instance;
	}

	// �X�V����
	void Update();

	// �I�u�W�F�N�g�폜
	inline void RemoveALLObj()
	{
		// �S�č폜
		for (auto it = m_UILists.begin(); it != m_UILists.end();)
		{
			it = m_UILists.erase(it);
		}
		for (auto it = m_pNormalUI.begin(); it != m_pNormalUI.end();)
		{
			it = m_pNormalUI.erase(it);
		}
	}

	// ���Z�b�g�֐�
	inline void Reset()
	{
		m_TutorialFlg = true;
		m_Page = 1;
	}

	// �Z�b�g�֐�
	inline void SetTutorialUI(int page, GameObject* obj)
	{
		m_UILists[page].push_back(obj);
		obj->GetComponent<ModelRenderer2D>()->SetDraw(false);
	}
	inline void SetNormalUI(GameObject* obj)
	{
		m_pNormalUI.push_back(obj);
		obj->GetComponent<ModelRenderer2D>()->SetDraw(false);
	}

	// �Q�b�g�֐�
	inline bool GetTutorial()
	{
		return m_TutorialFlg;
	}

private:

	TutorialManager()
	{
		m_Page = 1;
		m_TutorialFlg = false;
	};
	~TutorialManager()
	{
	};

	// UI�X�V����
	void UIUpdate(UIList::iterator& pair);

	// �`��ON
	void DrawFlgON(UIList::iterator& pair);
	// �`��OFF
	void DrawFlgOFF(UIList::iterator& pair);
	void DrawFlgOFF(std::vector<GameObject*>::iterator& pair);
private:
	UIList m_UILists;	// �`�悷��UI���X�g
	std::vector<GameObject*> m_pNormalUI;	// �y�[�W�Ɋ֌W�Ȃ��\������UI

	int m_Page;			// ���݊J���Ă�y�[�W
	bool m_TutorialFlg;	// �`���[�g���A�����s���t���O
};

#endif // __TUTORIAL_MANAGER_H__