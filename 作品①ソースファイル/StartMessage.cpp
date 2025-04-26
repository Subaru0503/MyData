//////////////////////////////
//
// �^�C�g���X�^�[�g���b�Z�[�W
//
//////////////////////////////

// �C���N���[�h��
#include "StartMessage.h"

// �R���X�g���N�^
StartMessage::StartMessage(std::string name)
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
	_opacity->SetParam(_modelRenderer2D_param);

}

// �f�X�g���N�^
StartMessage::~StartMessage()
{
}

// �X�V����
void StartMessage::Update()
{
	
}