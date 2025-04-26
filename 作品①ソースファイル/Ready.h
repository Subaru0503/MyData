// �X�^�[�g����UI�N���X

// �C���N���[�h�K�[�h
#ifndef __READY_H__
#define __READY_H__

// �C���N���[�h��
#include "GameObject.hpp"

// �R���|�[�l���g
#include "ModelRenderer2D.h"
#include "Move.h"
#include "SpinAnimation.h"

// �N���X��`
class Ready : public GameObject
{
public:
	enum AnimKind
	{
		None,
		Before,
		Change,
		Scale,
		Start,
	};
public:
	Ready(std::string name = "Ready");	// �R���X�g���N�^
	~Ready();							// �f�X�g���N�^

	void Update();						// �X�V����

	// �Q�b�g�֐�
	inline bool GetStart()
	{
		return m_Start;
	}

private:
	void BeforeSpinAnimation();				// ��]�ړ��A�j���[�V�����O�ɂ�鏈��
	void MoveAndTextureChangeAnimation();	// ��]�ړ��A�j���[�V����+�e�N�X�`���ύX
	void ScaleAnimation();					// �g�k�A�j���[�V����
private:
	// �R���|�[�l���g
	ModelRenderer2D* _modelRenderer2D;
	Move* _move;
	SpinAnimation* _spinAnimation;

	// ���f�������_���[2D�`��p�����[�^
	ModelRenderer2D::Param* _modelRenderer2D_param;

	AnimKind animKind;		// �A�j���[�V�������

	float m_Delay;			// ��]�A�j���[�V�����J�n�܂ł̃f�B���C

	bool m_Start;			// �Q�[���X�^�[�g�J�n�t���O
	bool m_ScaleAnimFlg;	// �g�k�A�j���[�V�����t���O
};

#endif // __GAME_OVER_H__