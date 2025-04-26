// �����蔻��Ǘ��N���X

// �C���N���[�h�K�[�h
#ifndef __COLLISION_MANAGER_H__
#define __COLLISION_MANAGER_H__

// �C���N���[�h��
#include "GameObject.hpp"

// �N���X��`
class CollisionManager
{
public:
	inline static CollisionManager& GetInstance()
	{
		static CollisionManager instance;
		return instance;
	}

	// �I�u�W�F�N�g���X�g�ɒǉ��B
	inline void AddObj(GameObject* obj)
	{
		// �I�u�W�F�N�g�i���o�[�̏d�����Ȃ����m�F
		for (auto it = m_pObjList.begin(); it != m_pObjList.end(); it++)
		{
			GameObject* m_obj = *it;
			// ���ɂ�������ǉ������ɔ�΂�
			if (m_obj->Get3DObjNo() == obj->Get3DObjNo())
			{
				return;
			}
		}
		// �I�u�W�F�N�g�ǉ�
		m_pObjList.push_back(obj);
	}

	inline void RemoveALLObj()
	{
		// �S�č폜
		for (auto it = m_pObjList.begin(); it != m_pObjList.end();)
		{
			it = m_pObjList.erase(it);
		}
	}

	// �X�V����
	void Update();

	// �Q�b�g�֐�
	inline int GetObjSize()
	{
		return (int)m_pObjList.size();
	}

private:
	
	CollisionManager()
	{

	};
	~CollisionManager()
	{
	};

private:
	// �R���C�_�[�����̃I�u�W�F�N�g���X�g
	std::vector<GameObject*> m_pObjList;

	bool m_Collision;
};

#endif // __COLLISION_MANAGER_H__