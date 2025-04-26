///////////////////////////////////////
//
// �n�ʃN���X
//
// �X�e�[�W�̏�
//
///////////////////////////////////////

//----�C���N���[�h��----
#include "Ground.h"

// �R���X�g���N�^
Ground::Ground(std::string name)
	: GameObject(name)
{
	m_tag = "Ground";

	// �R���|�[�l���g�ǉ�
	AddComponent<BoxCollider>();			// �����蔻��ǉ��B
	AddComponent<ModelRenderer3D>();		// 3D�`��

	// �R���|�[�l���g�擾
	_boxCollider = GetComponent<BoxCollider>();
	_modelRenderer3D = GetComponent<ModelRenderer3D>();

	// �V�F�[�_�[�Z�b�g
	const char* file[] = {
		"VS_Object",
		"PS_TexColor",
	};

	_modelRenderer3D->SetShader(file);
}

// �f�X�g���N�^
Ground::~Ground()
{
}

// �X�V����
void Ground::Update()
{

}