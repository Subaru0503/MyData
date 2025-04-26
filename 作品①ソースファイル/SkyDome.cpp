///////////////////////////////////////
//
// �X�J�C�h�[���N���X
//
// �w�i���f���̏���������
//
///////////////////////////////////////

//----�C���N���[�h��----
#include "SkyDome.h"

//----�V�[��----
#include "SceneRoot.h"

// �R���X�g���N�^
SkyDome::SkyDome(std::string name)
	: GameObject(name)
{
	m_tag = "SkyDome";

	// �R���|�[�l���g�ǉ�
	AddComponent<ModelRenderer3D>();	// 3D�`��

	// �R���|�[�l���g�擾
	_modelRenderer3D = GetComponent<ModelRenderer3D>();

	// ���f���ǂݍ���
	_modelRenderer3D->SetPath("Assets/Model/Sky/Sky.fbx");

	// ������
	m_pos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	SetScale(DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));
	m_quat = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	pCamObj = nullptr;

	// �^�C�g���V�[���Ȃ��p�̃s�N�Z���V�F�[�_�[�ɂ���
	if (SceneRoot::GetCurrentScene() == SceneRoot::Scene::TITLE)
	{
		// �V�F�[�_�[�Z�b�g
		const char* file[] = {
			"VS_Object",
			"PS_SkyBrightness",
		};

		_modelRenderer3D->SetShader(file);
	}
	else
	{
		// �V�F�[�_�[�Z�b�g
		const char* file[] = {
			"VS_Object",
			"PS_TexColor",
		};

		_modelRenderer3D->SetShader(file);
	}
}

// �f�X�g���N�^
SkyDome::~SkyDome()
{
}

// �X�V����
void SkyDome::Update()
{
	// �J�����̐ݒ肪����ĂȂ������珈�����Ȃ�
	if (!pCamObj) return;

	// �w�i�ƃJ�����̍��W�𓯂��ɂ���
	SetPos(pCamObj->GetPos());

	// ��]
	Rot();
}

// ��]
void SkyDome::Rot()
{
	// ��]�擾
	DirectX::XMVECTOR qRotate = DirectX::XMLoadFloat4(&m_quat);

	DirectX::XMMATRIX RotMat = DirectX::XMMatrixRotationQuaternion(qRotate);

	float rotY = 0.0f;
	rotY += 1.0f / 60.0f;

	// ���ɍ��킹�ĉ�]
	DirectX::XMVECTOR quat = DirectX::XMQuaternionRotationAxis(
		DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), DirectX::XMConvertToRadians(rotY)
	);

	// �N�H�[�^�j�I���|���Z
	qRotate = DirectX::XMQuaternionMultiply(qRotate, quat);

	// �p�x�X�V
	DirectX::XMStoreFloat4(&m_quat, qRotate);
}
