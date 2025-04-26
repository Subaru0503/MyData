#include "GreenPlanet.h"

GreenPlanet::GreenPlanet()
{
	m_pos = {0.0f,0.0f,0.0f};
	m_scale = { 1.0f, 1.0f, 1.0f };
	m_rotate = { 0.0f, -90.0f, 0.0f };

	// ���f���ǂݍ���
	m_pModel = new Model();
	if (!m_pModel->Load("Assets/Model/GreenPlanet/GreenPlanet.fbx", 0.07f, Model::Flip::XFlip)) {
		MessageBox(NULL, "Assets/Model//GreenPlanet/GreenPlanet.fbx", "Error", MB_OK);
	}
	// ���_�V�F�[�_�[�ǂݍ���
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}
	m_pModel->SetVertexShader(m_pVS);	// ���f���ɒ��_�V�F�[�_�[��ݒ�
}

GreenPlanet::~GreenPlanet()
{
}

DirectX::XMFLOAT3 GreenPlanet::GetPos()
{
	return m_pos;
}
