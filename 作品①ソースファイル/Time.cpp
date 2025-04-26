//////////////////////////////
//
// ����
//
//////////////////////////////

// �C���N���[�h��
#include "Time.h"

// �萔�E�}�N����`
#define TOTAL_TIME (1.0f)	// �t�F�[�h�A�E�g�ɂ����鎞��(�b)

// �R���X�g���N�^
Time::Time(std::string name)
	: GameObject(name)
{
	// �R���|�[�l���g�ǉ�
	AddComponent<ModelRenderer2D>();

	// �R���|�[�l���g�擾
	_modelRenderer2D = GetComponent<ModelRenderer2D>();

	// �����o�ϐ�������
	_modelRenderer2D_param = _modelRenderer2D->GetParam();

	_modelRenderer2D_param->MaxGrid = DirectX::XMINT2(5, 2);
	_modelRenderer2D_param->uvSize.x = 1.0f / _modelRenderer2D_param->MaxGrid.x;
	_modelRenderer2D_param->uvSize.y = 1.0f / _modelRenderer2D_param->MaxGrid.y;
	m_Time = 0.0f;

	// �l�Z�b�g
	m_Alpha = 0.5f;
}

// �f�X�g���N�^
Time::~Time()
{
}

// �X�V����
void Time::Update()
{
}

void Time::AlphaUpdate()
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
