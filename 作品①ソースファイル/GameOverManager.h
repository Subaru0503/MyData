// �Q�[���I�[�o�[����Ǘ��N���X

// �C���N���[�h�K�[�h
#ifndef __GAME_OVER_MANAGER_H__
#define __GAME_OVER_MANAGER_H__

// �C���N���[�h��
#include "GameObject.hpp"

// �N���X��`
class GameOverManager
{
public:
	inline static GameOverManager& GetInstance()
	{
		static GameOverManager instance;
		return instance;
	}

	// �X�V����
	void Update();

	// �������`�F�b�N
	void FallDeadCheck();
	// �^�C���I�[�o�[�`�F�b�N
	void TimeOverCheck();

	// ���Z�b�g�֐�
	inline void Reset()
	{
		m_GameOverFlg = false;
	}

	// �Z�b�g�֐�
	inline void SetPlyer(GameObject* obj)
	{
		m_pPlayer = obj;
	}

	// �Q�b�g�֐�
	inline bool GetGameOverFlg()
	{
		return m_GameOverFlg;
	}

private:

	GameOverManager()
	{
		m_GameOverFlg = false;
	};
	~GameOverManager()
	{
	};

private:
	GameObject* m_pPlayer;	// �v���C���[�I�u�W�F�N�g

	bool m_GameOverFlg;	// �Q�[���I�[�o�[�t���O
};

#endif // __GAME_OVER_MANAGER_H__