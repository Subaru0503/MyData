//////////////////////////////
//
// �Q�[���X�^�[�g����UI
//
//////////////////////////////

// �C���N���[�h��
#include "Start.h"

// �萔�E�}�N����`
#define VALUE (0.005f)

// �R���X�g���N�^
Start::Start(std::string name)
	: GameObject(name)
{
	// �R���|�[�l���g�ǉ�
	AddComponent<ModelRenderer2D>();
	AddComponent<Opacity>();

	// �R���|�[�l���g�擾
	_modelRenderer2D = GetComponent<ModelRenderer2D>();
	_opacity = GetComponent<Opacity>();

	// �����o�ϐ�������
	_modelRenderer2D_param = _modelRenderer2D->GetParam();
	_opacity->SetChangeValue(VALUE);
	_opacity->SetParam(_modelRenderer2D_param);
}

// �f�X�g���N�^
Start::~Start()
{
}

// �X�V����
void Start::Update()
{
	
}