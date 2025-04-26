// �S�[���N���X

// �C���N���[�h�K�[�h
#ifndef __GOAL_H__
#define __GOAL_H__

// �C���N���[�h��
#include "GameObject.hpp"

// �R���|�[�l���g
#include "BoxCollider.h"		// �����蔻��
//#include "Scanner.h"			// �X�L�����R���|�[�l���g
#include "ModelRenderer3D.h"	// 3D���f���`��

// �N���X��`
class Goal : public GameObject
{
public:
	Goal(std::string name = "Goal");	// �R���X�g���N�^
	~Goal();							// �f�X�g���N�^

	void Update();						// �X�V����

	void OnCollision(GameObject* obj);	// ���������I�u�W�F�N�g�̂��Ƃ̏���

	// �Q�b�g�֐�
	// �S�[���t���O��Ԃ�
	inline bool GetGoalFlg()
	{
		return m_GoalFlg;
	}

private:
	// �R���|�[�l���g
	BoxCollider* _boxCollider;			// �{�b�N�X�R���C�_�[�R���|�[�l���g
	//Scanner* _scanner;					// �X�L���i�R���|�[�l���g
	ModelRenderer3D* _modelRenderer3D;	// 3D�`��R���|�[�l���g

	bool m_GoalFlg;						// �S�[���t���O

};

#endif // __GOAL_H__