// �S�[���N���X

// �C���N���[�h��
#include "Goal.h"

#include "Player.h"

// �R���X�g���N�^
Goal::Goal(std::string name)
	: GameObject(name)
	, m_GoalFlg(false)
{
	m_tag = "Goal";

	// �R���|�[�l���g�ǉ�
	AddComponent<BoxCollider>();			// �����蔻��ǉ��B
	//AddComponent<Scanner>();				// �X�L���i
	AddComponent<ModelRenderer3D>();		// 3D�`��

	// �R���|�[�l���g�擾
	_boxCollider = GetComponent<BoxCollider>();
	//_scanner = GetComponent<Scanner>();
	_modelRenderer3D = GetComponent<ModelRenderer3D>();

	// �V�F�[�_�[�Z�b�g
	const char* file[] = {
		"VS_Object",
		"PS_TexColor",
	};

	_modelRenderer3D->SetShader(file);
}

// �f�X�g���N�^
Goal::~Goal()
{
}

// �X�V����
void Goal::Update()
{

}

// �S�[������`�F�b�N
void Goal::OnCollision(GameObject* obj)
{
	if (obj && obj->GetTag() == "Player")
	{
		m_GoalFlg = true;	// �S�[���t���O���グ��
	}
	// ���̂Ȃ�
	else if (!obj)
	{
		m_pCollisionObj = nullptr;
	}
}