//////////////////////////////
//
// �^�C�g����
//
//////////////////////////////

//----�C���N���[�h�K�[�h----
#ifndef __TITLE_SCREW_H__
#define __TITLE_SCREW_H__

//----�C���N���[�h��----
#include "GameObject.hpp"
// �R���|�[�l���g
#include "ModelRenderer2D.h"
#include "Move.h"

// �A�j���[�V�����p
#include "Move2DAnimation.h"
#include "SpinAnimation.h"

#include "float3.h"

// �N���X��`
class TitleScrew : public GameObject
{
private:
	// �ő�܂ŉ񂵂��Ƃ���SE�Đ����
	enum SoundState
	{
		CanPlay,		// �ǂ�����Đ��ł�����
		NotPlayMaxSE,	// �ő�܂Œ��߂��Ƃ���SE���Đ��ł��Ȃ����
		NotPlayMinSE,	// �ő�܂Ŋɂ߂��Ƃ���SE���Đ��ł��Ȃ����
	};

public:

	// �R���X�g���N�^
	TitleScrew(std::string name = "Name");

	// �f�X�g���N�^
	~TitleScrew();

	// �X�V����
	void Update();

	// �Z�b�g�֐�
	void SetAnimationSpeed(DirectX::XMFLOAT2 speed);

	// �l�W�����߂��Ƃ��Ɍ������ʒu��ݒ�
	void SetTargetPos(DirectX::XMFLOAT3 pos);

private:
	// �l�W���񂷏���
	void ScrewSpin();

private:

	// ��]�A�j���[�V�������ɂ�鏈��
	void ApplyRotationSettings();

private:
	//----�R���|�[�l���g----

	// 2D���f�������_���[
	ModelRenderer2D* _modelRenderer2D;

	// �ړ�
	Move* _move;

	// 2D�A�j���[�V����
	Move2DAnimation* _move2DAnimation;

	// ��]�A�j���[�V����
	SpinAnimation* _spinAnimation;

	// �A�j���[�V�����X�s�[�h
	DirectX::XMFLOAT2 m_AnimationSpeed;

	// �^�[�Q�b�g���W
	float3 m_TargetPos;

	// SE�Đ��t���O
	SoundState m_SpinMaxPlayingSE;
};

#endif // __TITLE_SCREW_H__