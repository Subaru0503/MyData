//////////////////////////////
//
// �^�C�g����
//
//////////////////////////////

//----�C���N���[�h�K�[�h----
#ifndef __TITLE_H__
#define __TITLE_H__

//----�C���N���[�h��----
#include "GameObject.hpp"
// �R���|�[�l���g
#include "ModelRenderer2D.h"

// �A�j���[�V�����p
#include "Move2DAnimation.h"
#include "SpinAnimation.h"

// �N���X��`
class Title : public GameObject
{
public:

	// �R���X�g���N�^
	Title(std::string name = "Name");

	// �f�X�g���N�^
	~Title();

	// �X�V����
	void Update();

	// �Z�b�g�֐�
	void SetAnimationSpeed(DirectX::XMFLOAT2 speed);

private:

	// ��]�A�j���[�V�������ɂ�鏈��
	void ApplyRotationSettings();

private:
	//----�R���|�[�l���g----

	// 2D���f�������_���[
	ModelRenderer2D* _modelRenderer2D;

	// 2D�A�j���[�V����
	Move2DAnimation* _move2DAnimation;

	// ��]�A�j���[�V����
	SpinAnimation* _spinAnimation;

	// �A�j���[�V�����X�s�[�h
	DirectX::XMFLOAT2 m_AnimationSpeed;
};

#endif // __TITLE_H__