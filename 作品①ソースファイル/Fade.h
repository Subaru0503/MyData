// �t�F�[�h�N���X

// �C���N���[�h�K�[�h
#ifndef __FADE_H__
#define __FADE_H__

// �C���N���[�h��
#include "GameObject.hpp"
#include "ModelRenderer2D.h"

// �萔�E�}�N����`
#define FADE_IN (true)
#define FADE_IN_TIME (1.0f)		// �t�F�[�h�C������
#define FADE_OUT (false)
#define FADE_OUT_TIME (2.0f)	// �t�F�[�h�A�E�g����

// �N���X��`
class Fade : public GameObject
{
public:

	// �t�F�[�h�J���[
	enum FadeColor
	{
		White,	// ���F
		Black,	// ���F
	};

public:

	// �R���X�g���N�^
	Fade(std::string name = "Fade");

	// �f�X�g���N�^
	~Fade();

	// �X�V����
	void Update();

	// �t�F�[�h�J�n
	void Start(bool isIn, float time, FadeColor fadeColor);

	// �t�F�[�h���s�����ۂ�
	bool GetPlay();

	// �t�F�[�h�C�����ǂ�����Ԃ�
	bool GetFadeIn();

private:

	// �R���|�[�l���g
	ModelRenderer2D* _modelRenderer2D;

	// ���f�������_���[2D�`��p�����[�^
	ModelRenderer2D::Param* _modelRenderer2D_param;

	// �t�F�[�h�J���[
	FadeColor m_FadeColor;

	// �t�F�[�h�C���@or�@�t�F�[�h�A�E�g
	bool  m_FadeIn;

	// �o�ߎ���
	float m_Time;

	// �t�F�[�h�ɂ����鍇�v����
	float m_TotalTime;

	// �A���t�@�l
	float m_Alpha;
};

#endif // __GAME_OVER_H__