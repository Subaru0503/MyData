//////////////////////////////
//
// �E���UI
//
//////////////////////////////

// �C���N���[�h��
#include "Right.h"

#include "ShaderManager.h"

// �萔�E�}�N����`
#define VALUE (0.0025f)

// �R���X�g���N�^
Right::Right(std::string name)
	: GameObject(name)
{
	// �R���|�[�l���g�ǉ�
	AddComponent<ModelRenderer2D>();

	// �R���|�[�l���g�擾
	_modelRenderer2D = GetComponent<ModelRenderer2D>();

	// �����o�ϐ�������
	_modelRenderer2D_param = _modelRenderer2D->GetParam();

	_modelRenderer2D_param->color = DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);

	// �V�F�[�_�[�t�@�C��
	const char* file[] = {
		"VS_Color",
		"PS_Color",
	};

	// �V�F�[�_�[�ݒ�
	_modelRenderer2D->SetVertexShader(ShaderManager::GetInstance().GetShader<VertexShader>(file[0]), file[0]);
	_modelRenderer2D->SetPixelShader(ShaderManager::GetInstance().GetShader<PixelShader>(file[1]), file[1]);

	m_MaxFlg = false;
}

// �f�X�g���N�^
Right::~Right()
{
}

// �X�V����
void Right::Update()
{
	Blink();
}

// �_�ŏ���
void Right::Blink()
{
	float G = _modelRenderer2D_param->color.y;
	// �����ɂȂ��Ă�����
	if (m_MaxFlg)
	{
		G += VALUE;		// �Ώグ��
		// ���l�܂ł�������
		if (G >= 0.15f)
		{
			m_MaxFlg = false;	// �t���O����
		}
	}
	// �����x���Ȃ��Ȃ��Ă�����
	else
	{
		G -= VALUE;		// �΂�������
		// �����ɂȂ�����
		if (G <= 0.0f)
		{
			m_MaxFlg = true;	// �t���O�グ
		}
	}

	_modelRenderer2D_param->color.y = G;
}