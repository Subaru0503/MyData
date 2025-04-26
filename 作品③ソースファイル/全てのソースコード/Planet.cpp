// Planet.cpp

//=====�C���N���[�h=====
#include "Planet.h"
#include "Geometory.h"

/**********************
*@brief �R���X�g���N�^
***********************/
Planet::Planet()
	: m_pos(0.0f, 0.0f, 0.0f)
	, m_scale(1.0f, 1.0f, 1.0f)
	, m_rotate(0.0f, 0.0f, 0.0f)
	, m_pModel(nullptr)
	, m_pVS(nullptr)
	, m_bFocus(false)
{
}

/*********************
*@brief �f�X�g���N�^
*********************/
Planet::~Planet()
{
	// ������������ł���Ή��
	SAFE_DELETE(m_pModel);
	SAFE_DELETE(m_pVS);
}

void Planet::Update(float tick)
{
	if (m_bFocus)
	{
		m_rotate.y += 30.0f * tick;
	}
}

void Planet::Draw(DirectX::XMFLOAT4X4* mat)
{
	DirectX::XMMATRIX world;
	// ���[���h�s��̌v�Z
	world = DirectX::XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z) *
		DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_rotate.x)) *
		DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_rotate.y)) *
		DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_rotate.z)) *
		DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);

	world = DirectX::XMMatrixTranspose(world);	// �V�F�[�_�[�ɓn���p�Ƀ��[���h�s���]�u

	DirectX::XMStoreFloat4x4(&mat[0], world);	// �V�F�[�_�[�ɓn���f�[�^�Ƀ��[���h�s���ϊ����ăZ�b�g

	Geometory::SetWorld(mat[0]);
	Geometory::SetView(mat[1]);
	Geometory::SetProjection(mat[2]);

	RenderTarget* pRTV = GetDefaultRTV();	// �f�t�H�̃����_�[�^�[�Q�b�g�r���[���擾
	DepthStencil* pDSV = GetDefaultDSV();	// �f�t�H�̃f�v�X�X�e���V���r���[���擾
	SetRenderTargets(1, &pRTV, pDSV);		// �����_�[�^�[�Q�b�g��1�ԂɃZ�b�g

	m_pVS->WriteBuffer(0, mat);	// ���W�ϊ��s��𒸓_�V�F�[�_�[�̒萔�o�b�t�@�ɃR�s�[
	m_pModel->Draw();			// ���f����`��
}

DirectX::XMFLOAT3 Planet::GetPos()
{
	return m_pos;
}

void Planet::StartFocus()
{
	m_bFocus = true;
}

void Planet::EndFocus()
{
	m_bFocus = false;
}
