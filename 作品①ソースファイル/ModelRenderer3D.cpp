///////////////////////////////////////
//
// ���f���`��N���X
//
// �`��ɕK�v�ȃV�F�[�_�[�̐ݒ蓙������
//
///////////////////////////////////////

// �C���N���[�h��
#include "ModelRenderer3D.h"

// �R���X�g���N�^
ModelRenderer3D::ModelRenderer3D()
	: m_pModel(nullptr)
	, m_ModelName{}
	, m_Scale(1.0f)
	, m_Time(0.0f)
	, m_DrawFlg(true)
{
}

// �f�X�g���N�^
ModelRenderer3D::~ModelRenderer3D()
{
	if (m_pModel)
		delete m_pModel;
}

// �X�V
void ModelRenderer3D::Execute()
{
	// ���Ԍo��
	m_Time += 1.0f / 60.0f * 2;
}

// �`��
void ModelRenderer3D::Draw()
{
	// �`��t���O���������Ă���`�悵�Ȃ�
	if (!m_DrawFlg) return;

	// �Z�b�g���Ă���V�F�[�_�[�̖��O�ɂ����
	// �V�F�[�_�[�ɓn���f�[�^��ς���
	CallByName();

	// �`��
	// ���f�����Z�b�g����ĂȂ�
	if (!m_pModel)
	{
		MessageBox(NULL, "���f�����Z�b�g����ĂȂ�", "ModelRenderer3D", MB_OK);
		return;
	}

	// �V�F�[�_�[�Z�b�g
	m_pModel->SetVertexShader(m_Shader[0]);
	m_pModel->SetPixelShader(m_Shader[1]);

	// ���f���`��
	m_pModel->Draw();
}

// �V�F�[�_�[�ɂ���ăo�b�t�@�ɓn������ς���
void ModelRenderer3D::CallByName()
{
	// ���_�V�F�[�_�[�̒萔�o�b�t�@�ɏ���n��
	// �g�p���钸�_�V�F�[�_�[�ɂ���ČĂԊ֐���ς���
	if (m_ShagerName[0] == "VS_Object" || m_ShagerName[0] == "VS_World")
	{
		SetVS_Default();	// �s�����n��
	}


	// �s�N�Z���V�F�[�_�[�̒萔�o�b�t�@�ɏ���n��
	// �g�p����s�N�Z���V�F�[�_�[�ɂ���ČĂԊ֐���ς���
	if (m_ShagerName[1] == "PS_SkyBrightness")
	{
		// ��̐F��ς���V�F�[�_�[
		SetPS_Sky();
	}
}

// �s�����n��
void ModelRenderer3D::SetVS_Default()
{
	// �J�������Z�b�g����ĂȂ�
	if (!m_pCamera)
	{
		MessageBox(NULL, "�J�������Z�b�g����ĂȂ�", "ModelRenderer3D", MB_OK);
		return;
	}

	// �萔�o�b�t�@�ɓn���s��̏��
	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixIdentity());
	mat[1] = m_pCamera->GetView();
	mat[2] = m_pCamera->GetProj();

	// �V�F�[�_�[���Z�b�g����ĂȂ�
	if (!m_Shader[0] || !m_Shader[1])
	{
		MessageBox(NULL, "�V�F�[�_�[���Z�b�g����ĂȂ�", "ModelRenderer3D", MB_OK);
		return;
	}

	// ���W�̍X�V
	mat[0] = transform->GetWorld();
	m_Shader[0]->WriteBuffer(0, mat);
}

// ��̐F��ς���s�N�Z���V�F�[�_�[
void ModelRenderer3D::SetPS_Sky()
{
	// �V�F�[�_�[�̎��ԃp�����[�^���X�V
	float dayDuration = 360.0f; // 1�T�̎���
	float timeOfDay = fmod(m_Time, dayDuration) / dayDuration;

	// ���݂̎��Ԃ�n��
	m_Shader[1]->WriteBuffer(0, &timeOfDay);
}

// �p�X�w��
void ModelRenderer3D::SetPath(std::string name)
{
	for (int i = 0; i < name.size(); i++)
	{
		m_ModelName[i] = name[i];
	}
	m_ModelName[name.size()] = '\0';

	m_pModel = new Model();
	m_pModel->Load(m_ModelName, m_Scale);
}

// �V�F�[�_�[�Z�b�g
void ModelRenderer3D::SetShader(const char ** shaderFiles)
{
	for (int i = 0; i < 2; ++i)
	{
		if (strstr(shaderFiles[i], "PS_") == shaderFiles[i]) {
			m_Shader[1] = ShaderManager::GetInstance().GetShader<PixelShader>(shaderFiles[i]);
			m_ShagerName[1] = shaderFiles[i];	// ���O�ۑ�
		}
		else if (strstr(shaderFiles[i], "VS_") == shaderFiles[i]) {
			m_Shader[0] = ShaderManager::GetInstance().GetShader<VertexShader>(shaderFiles[i]);
			m_ShagerName[0] = shaderFiles[i];	// ���O�ۑ�
		}
		else {
			MessageBox(NULL, shaderFiles[i], "Shader name [VS_ / PS_]", MB_OK);
		}
	}
}

// �`��t���O���Z�b�g
void ModelRenderer3D::SetDrawFlg(bool flg)
{
	m_DrawFlg = flg;
}

// �`��t���O��Ԃ�
bool ModelRenderer3D::GetDrawFlg()
{
	return m_DrawFlg;
}
