//////////////////////////////
//
// �N���AUI
//
//////////////////////////////

// �C���N���[�h��
#include "Clear.h"

// �萔�E�}�N����`
#define TOTAL_TIME (1.0f)	// �t�F�[�h�A�E�g�ɂ����鎞��(�b)

// �R���X�g���N�^
Clear::Clear(std::string name)
	: GameObject(name)
{
	// �R���|�[�l���g�ǉ�
	AddComponent<ModelRenderer2D>();

	// �R���|�[�l���g�擾
	_modelRenderer2D = GetComponent<ModelRenderer2D>();

	// �e�N�X�`���ǂݍ���
	_modelRenderer2D->Load("Assets/Texture/ClearUI/ClearUI.png");

	// �����o�ϐ�������
	_modelRenderer2D_param = _modelRenderer2D->GetParam();
	m_Time = 0.0f;

	// �l�Z�b�g
	m_Alpha = 0.5f;
	m_pos.x = 640.0f;
	m_pos.y = 360.0f;
	m_scale.x = 1280.0f;
	m_scale.y = 720.0f;
	_modelRenderer2D_param->color.w = m_Alpha;
}

// �f�X�g���N�^
Clear::~Clear()
{
}

// �X�V����
void Clear::Update()
{
	// �����x���Ȃ��Ȃ��Ă��珈�����Ȃ�
	if (m_Alpha >= 1.0f) return;

	m_Time += 1.0f / 60.0f;

	// �t�F�[�h�̌o�ߎ��Ԃ̊������瓧���x�����߂�
	float rate = m_Time / TOTAL_TIME;
	rate = 0.5f + 0.5f * rate;	// 0.5�`1.0�ɕ␳��������
	m_Alpha = rate;				// �����x��������
	// �����x�X�V
	_modelRenderer2D_param->color.w = m_Alpha;		
	
}