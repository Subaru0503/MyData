// �Q�[���I�[�o�[��Ǘ��N���X

// �C���N���[�h�K�[�h
#ifndef __AFTER_GAME_OVER_MANAGER_H__
#define __AFTER_GAME_OVER_MANAGER_H__

// �C���N���[�h��
#include "GameObject.hpp"
#include "SkyDome.h"
#include "GameOver.h"

// �N���X��`
class AfterGameOverManager
{
public:
	inline static AfterGameOverManager& GetInstance()
	{
		static AfterGameOverManager instance;
		return instance;
	}

	// �X�V����
	void Update();

	// ���Z�b�g�֐�
	inline void Reset()
	{
		m_pObj = nullptr;
		m_pSkyDome = nullptr;
	}

	// �Z�b�g�֐�
	inline void SetObj(GameOver* obj, SkyDome* skydome)
	{
		m_pObj = obj;
		m_pSkyDome = skydome;
	}

	// �Q�b�g�֐�
	inline bool GetObj()
	{
		return m_pObj == nullptr;
	}

private:

	AfterGameOverManager()
	{
	};
	~AfterGameOverManager()
	{
	};

private:
	SkyDome* m_pSkyDome;	// �X�J�C�h�[��
	GameOver* m_pObj;		// �Q�[���I�[�o�[UI

};

#endif // __AFTER_GAME_OVER_MANAGER_H__