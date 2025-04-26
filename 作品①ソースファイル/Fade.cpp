//////////////////////////////
//
// �t�F�[�h
//
//////////////////////////////

// �C���N���[�h��
#include "Fade.h"

// �R���X�g���N�^
Fade::Fade(std::string name)
	: GameObject(name)
{
	// �R���|�[�l���g�ǉ�
	AddComponent<ModelRenderer2D>();

	// �R���|�[�l���g�擾
	_modelRenderer2D = GetComponent<ModelRenderer2D>();

	// �e�N�X�`���ǂݍ���
	_modelRenderer2D->Load("Assets/Texture/BlackFade.png");

	// �����o�ϐ�������
	_modelRenderer2D_param = _modelRenderer2D->GetParam();
	m_FadeIn = false;
	m_Time = 0.0f;
	m_TotalTime = 0.0f;

	// �l�Z�b�g
	m_Alpha = 0.0f;
	m_pos.x = 640.0f;
	m_pos.y = 360.0f;
	m_scale.x = 1280.0f;
	m_scale.y = 720.0f;
	_modelRenderer2D_param->color.w = m_Alpha;
	m_FadeColor = FadeColor::Black;
}

// �f�X�g���N�^
Fade::~Fade()
{
}

// �X�V����
void Fade::Update()
{
	// �t�F�[�h�����s����K�v�����邩
	if (!GetPlay())
	{
		return;
	}

	// �J�E���g�_�E��
	m_Time -= 1.0f / 60.0f;

	// �t�F�[�h�̌o�ߎ��Ԃ̊������瓧���x�����߂�
	float rate = m_Time / m_TotalTime;

	// �t�F�[�h�A�E�g�̏ꍇ�����A�����x�𔽓]������
	if (!m_FadeIn)
	{
		rate = 1.0f - rate;
	}

	// 0.5�`1.0�ɂȂ�悤�ɕ␳
	//rate = 0.5f + 0.5f * rate;

	m_Alpha = rate;

	_modelRenderer2D_param->color.w = m_Alpha;
}

// �t�F�[�h�J�n�̂��ߕK�v����ݒ肷��
void Fade::Start(bool fadeIn, float time, FadeColor fadeColor)
{
	// �t�F�[�h�Đ����͐ݒ�ł��Ȃ�
	if (GetPlay())
	{
		return;
	}

	// �t�F�[�h�J���[�ݒ�
	if (m_FadeColor != FadeColor::Black &&
		fadeColor == FadeColor::Black)
	{
		// ���݂̃t�F�[�h�J���[���ݒ�
		m_FadeColor = FadeColor::Black;

		// �e�N�X�`���ǂݍ���
		_modelRenderer2D->Load("Assets/Texture/BlackFade.png");
	}
	else if (m_FadeColor != FadeColor::White &&
		fadeColor == FadeColor::White)
	{
		// ���݂̃t�F�[�h�J���[���ݒ�
		m_FadeColor = FadeColor::White;

		// �e�N�X�`���ǂݍ���
		_modelRenderer2D->Load("Assets/Texture/WhiteFade.png");
	}

	if (fadeIn)	m_Alpha = 1.0f;
	else		m_Alpha = 0.0f;
	m_FadeIn = fadeIn;
	m_Time = time;
	m_TotalTime = time;	// time�̎��Ԃ����ăt�F�[�h��������
}

// �t�F�[�h����
bool Fade::GetPlay()
{
	return m_Time > 0.0f;
}

// �t�F�[�h�C�����ǂ�����Ԃ�
bool Fade::GetFadeIn()
{
	return m_FadeIn;
}