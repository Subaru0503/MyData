///////////////////////////////////////
//
// �I�u�W�F�N�g���Z�b�g�Ǘ��N���X
//
// �I�u�W�F�N�g�̔z�u�������ʒu�ɖ߂�
//
///////////////////////////////////////


// �C���N���[�h�K�[�h
#ifndef __RESET_MANAGER_H__
#define __RESET_MANAGER_H__

// �C���N���[�h��
#include "GameObject.hpp"
#include "Fade.h"

// �N���X��`
class ResetManager
{
public:

	// �C���X�^���X�擾
	inline static ResetManager& GetInstance()
	{
		static ResetManager instance;
		return instance;
	}

	// �X�V����
	void Update();

	// �I�u�W�F�N�g��������Ԃɖ߂�
	void ResetState();

	// �I�u�W�F�N�g�폜
	inline void RemoveALLObj()
	{
		// �S�č폜
		for (auto it = m_Obj.begin(); it != m_Obj.end();)
		{
			it = m_Obj.erase(it);
		}
	}

	//----�Z�b�g�֐�----

	// �I�u�W�F�N�g���Z�b�g
	inline void SetObj(GameObject* obj)
	{
		// ���X�g�ɒǉ�
		m_Obj.push_back(obj);
	}

	// �t�F�[�h�Z�b�g
	void SetFade(Fade* fade);

	//----�Q�b�g�֐�----

	// ���Z�b�g�t���O��Ԃ�
	bool GetResetFlg();

private:

	// �R���X�g���N�^
	ResetManager()
	{
		m_ResetFlg = false;
	};

	// �f�X�g���N�^
	~ResetManager()
	{
	};

private:

	// ������Ԃɖ߂��I�u�W�F�N�g���X�g
	std::vector<GameObject*> m_Obj;

	// �t�F�[�h
	Fade* m_pFade;

	// ���Z�b�g�t���O
	bool m_ResetFlg;
};

#endif // __RESET_MANAGER_H__