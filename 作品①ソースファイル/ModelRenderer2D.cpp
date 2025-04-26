///////////////////////////////////////
//
// 2D���f���`��N���X
//
// �`��ɕK�v�ȃV�F�[�_�[�̐ݒ蓙������
//
///////////////////////////////////////

//----�C���N���[�h��----
#include "ModelRenderer2D.h"
#include "Defines.h"

// �R���X�g���N�^
ModelRenderer2D::ModelRenderer2D()
{
	// ������
	m_VS = nullptr;
	m_PS = nullptr;
	m_pTexture = new Texture();
	m_Param.uvSize = DirectX::XMFLOAT2(1.0f, 1.0f);
	m_Param.color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Param.animeNo = 0;
	m_Param.MaxGrid.x = 1.0f;
	m_Param.MaxGrid.y = 1.0f;
	m_DrawFlg = true;
}

// �f�X�g���N�^
ModelRenderer2D::~ModelRenderer2D()
{
	if (m_pTexture)
	{
		delete m_pTexture;
		m_pTexture = nullptr;
	}
}

// �`��
void ModelRenderer2D::Draw()
{
	if (!m_DrawFlg) return;

	DirectX::XMFLOAT3 pos = transform->GetPos();
	DirectX::XMFLOAT4 quat = transform->GetQuat();
	DirectX::XMFLOAT3 scale = transform->GetScale();

	// �萔�o�b�t�@�ɓn���s��̏��
	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixIdentity());
	mat[1] = m_pCamera->GetView();
	mat[2] = m_pCamera->GetProj();

	DirectX::XMMATRIX world;
	world = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
	DirectX::XMMATRIX R = DirectX::XMMatrixRotationQuaternion(
		DirectX::XMVectorSet(quat.x, quat.y, quat.z, quat.w)
	);

	DirectX::XMMATRIX M = R * world;

	// 2D�\���p�̍s����v�Z
	DirectX::XMStoreFloat4x4(&mat[0],
		DirectX::XMMatrixTranspose(M));
	// ���s���Ȃ���3D�ŃX�v���C�g��\��
	DirectX::XMStoreFloat4x4(&mat[1],
		DirectX::XMMatrixIdentity());

	DirectX::XMStoreFloat4x4(&mat[2],
		DirectX::XMMatrixTranspose(
			DirectX::XMMatrixOrthographicOffCenterLH(
				// ��ʂɍ��킹�ĕ\��
				0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f, 0.1f, 10.0f
			)));

	// �o�b�t�@�ɏ���n��
	CallByName();

	// �����_�[�^�[�Q�b�g�̓��e��
	// �X�v���C�g(�l�p�`�̃|���S��)�ɓ\��t����
	// �\��
	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(scale.x, scale.y));
	Sprite::SetUVPos(DirectX::XMFLOAT2((float)(m_Param.animeNo % m_Param.MaxGrid.x) / m_Param.MaxGrid.x,
		(float)(m_Param.animeNo / m_Param.MaxGrid.x) / m_Param.MaxGrid.y));
	Sprite::SetUVScale(m_Param.uvSize);
	Sprite::SetColor(m_Param.color);
	Sprite::SetTexture(m_pTexture);
	Sprite::SetVertexShader(m_VS);
	Sprite::SetPixelShader(m_PS);
	Sprite::Draw();
}

// �V�F�[�_�[�ɂ���ăo�b�t�@�ɓn������ς���
void ModelRenderer2D::CallByName()
{
	// �s�N�Z���V�F�[�_�[�̒萔�o�b�t�@�ɏ���n��
	// �g�p����s�N�Z���V�F�[�_�[�ɂ���ČĂԊ֐���ς���
	if (m_ShagerName[1] == "PS_Title")
	{
		// �^�C�g���Ɏg���V�F�[�_�[
		SetPS_Title();
	}
}

// �^�C�g���ɂŎg���V�F�[�_�[�ɏ���n��
void ModelRenderer2D::SetPS_Title()
{
	// �J�������W�擾
	DirectX::XMFLOAT3 camPos = m_pCamObj->GetPos();

	// �s�N�Z���V�F�[�_�[�ɏ���n��
	m_PS->WriteBuffer(0, &camPos);
}

// ���_�V�F�[�_�[�ݒ�
void ModelRenderer2D::SetVertexShader(Shader * vs, const char* shaderFiles)
{
	// ���_�V�F�[�_�[�ݒ�
	m_VS = vs;

	// ���O�擾
	m_ShagerName[0] = shaderFiles;
}

// �s�N�Z���V�F�[�_�[�ݒ�
void ModelRenderer2D::SetPixelShader(Shader * ps, const char* shaderFiles)
{
	// �s�N�Z���V�F�[�_�[�ݒ�
	m_PS = ps;

	// ���O�擾
	m_ShagerName[1] = shaderFiles;
}
