// �S�[����Ǘ��N���X

// �C���N���[�h�K�[�h
#ifndef __AFTER_GOAL_MANAGER_H__
#define __AFTER_GOAL_MANAGER_H__

// �C���N���[�h��
#include "GameObject.hpp"
#include "Clear.h"
#include "Goal.h"
#include "Player.h"
#include "Time.h"

// �}�l�[�W���[
#include "TimeManager.h"

// �N���X��`
class AfterGoalManager
{
public:
	inline static AfterGoalManager& GetInstance()
	{
		static AfterGoalManager instance;
		return instance;
	}

	// �X�V����
	void Update();

	// �A���t�@�l�ω�
	void AlphaUpdate();
	// �`��t���OON
	inline void DrawON()
	{
		ModelRenderer2D* modelRenderer2D;

		for (int i = 0; i < m_TimeObj.size(); i++)
		{
			modelRenderer2D = m_TimeObj[i]->GetComponent<ModelRenderer2D>();
			modelRenderer2D->SetDraw(true);
		}
	}

	// �I�u�W�F�N�g���X�g�ɒǉ��B
	inline void AddObj(GameObject* obj)
	{
		// �I�u�W�F�N�g�i���o�[�̏d�����Ȃ����m�F
		for (auto it = m_pObjList.begin(); it != m_pObjList.end(); it++)
		{
			GameObject* m_obj = *it;
			// ���ɂ�������ǉ������ɔ�΂�
			if (m_obj->GetTag() == obj->GetTag())
			{
				return;
			}
		}
		// �I�u�W�F�N�g�ǉ�
		m_pObjList.push_back(obj);
	}

	// ���Z�b�g�֐�
	inline void Reset()
	{
		m_PlayBGM = false;
		m_pClear = nullptr;
		m_pPlayer = nullptr;
		m_pGoal = nullptr;
		// �S�č폜
		for (auto it = m_pObjList.begin(); it != m_pObjList.end();)
		{
			it = m_pObjList.erase(it);
		}
		// �S�č폜
		for (auto it = m_TimeObj.begin(); it != m_TimeObj.end();)
		{
			it = m_TimeObj.erase(it);
		}
		// �S�č폜
		for (auto it = m_TimePos.begin(); it != m_TimePos.end();)
		{
			it = m_TimePos.erase(it);
		}
	}

	// �Z�b�g�֐�
	inline void SetObj(Clear* obj, Player* player, Goal* goal)
	{
		m_pClear = obj;
		m_pPlayer = player;
		m_pGoal = goal;
		_clearModelRenderer2D = m_pClear->GetComponent<ModelRenderer2D>();
	}
	inline void SetTimeObj(Time* obj)
	{
		// ����UI�擾
		m_TimeObj.push_back(obj); //TimeManager::GetInstance().GetTimeObj();
	}
	inline void SetTimePos(DirectX::XMFLOAT3 pos)
	{
		m_TimePos.push_back(pos);
	}

	// �Q�b�g�֐�
	inline bool GetObj()
	{
		return m_pClear == nullptr;
	}
	inline std::vector<Time*> GetTimeObj()
	{
		return m_TimeObj;
	}

private:

	AfterGoalManager()
	{
		m_PlayBGM = false;
	};
	~AfterGoalManager()
	{
	};

private:
	ModelRenderer2D* _clearModelRenderer2D;
	std::vector<GameObject*> m_pObjList;		// �X�J�C�h�[���A�J����
	std::vector<Time*>  m_TimeObj;				// ����UI�I�u�W�F�N�g
	std::vector<DirectX::XMFLOAT3> m_TimePos;	// �N���A�^�C�����W
	Clear* m_pClear;	// �N���AUI
	Player* m_pPlayer;	// �v���C���[
	Goal* m_pGoal;		// �S�[��

	bool m_PlayBGM;		// BGM�Đ��t���O
};

#endif // __AFTER_GOAL_MANAGER_H__