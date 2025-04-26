// �v���C���[�N���X

// �C���N���[�h�K�[�h
#ifndef __PLAYER_H__
#define __PLAYER_H__

// �C���N���[�h��
#include "GameObject.hpp"

// �R���|�[�l���g
#include "Move.h"				// �ړ�
#include "Jump.h"				// �W�����v
#include "BoxCollider.h"		// �����蔻��
#include "Scanner.h"			// �I�u�W�F�N�g�X�L���i
#include "ModelRenderer3D.h"	// 3D�`��
#include "ScaleAnimation.h"		// �X�P�[���A�j���[�V����

// �N���X��`
class Player : public GameObject
{
public:
	Player(std::string name = "Player");// �R���X�g���N�^
	~Player();							// �f�X�g���N�^

	// ������Ԃɖ߂�
	void ResetState();

	void Update();						// �X�V����

	void OnCollision(GameObject* obj);	// ���������I�u�W�F�N�g�̂��Ƃ̏���
	void OnScanner(GameObject* obj);	// ���m�����I�u�W�F�N�g�̂��Ƃ̏���

	void MoveAfterGoal(GameObject* obj);// �S�[����̈ړ�����

private:
	void InputCheck();					// ���͂���Ă���L�[���`�F�b�N
	void Rotate();						// �v���C���[��]

protected:
	//----�R���|�[�l���g----

	// �ړ��R���|�[�l���g
	Move* _move;

	// �W�����v�R���|�[�l���g
	Jump* _jump;

	// �{�b�N�X�R���C�_�[�R���|�[�l���g
	BoxCollider* _boxCollider;

	// �I�u�W�F�N�g�X�L���i�R���|�[�l���g
	Scanner* _scanner;

	// 3D���f�������_���[
	ModelRenderer3D* _modelRenderer3D;

	// �X�P�[���A�j���[�V�����R���|�[�l���g
	ScaleAnimation* _scaleAnimation;


	//----�ϐ�----

	// ���Z�b�g�ʒu
	DirectX::XMFLOAT3 m_ResetPos;

	// ��]�o�ߎ���
	float m_SpinTime;

	// �W�����v�\�t���O
	bool m_Jump;
};

#endif // __PLAYER_H__