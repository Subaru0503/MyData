#include "WholeCakePlanet.h"

WholeCakePlanet::WholeCakePlanet()
{
	m_pos = { -6.0f, 2.87f, 7.0f };
	m_scale = { 1.0f, 1.0f, 1.0f };
	m_rotate = { 0.0f, 90.0f, 0.0f };

	// ���f���ǂݍ���
	m_pModel = new Model();
	if (!m_pModel->Load("Assets/Model/WholeCakePlanet/SweetPlanet.fbx", 0.07f, Model::Flip::XFlip)) {
		MessageBox(NULL, "Assets/Model//WholeCakePlanet/SweetPlanet.fbx", "Error", MB_OK);
	}
	// ���_�V�F�[�_�[�ǂݍ���
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}
	m_pModel->SetVertexShader(m_pVS);	// ���f���ɒ��_�V�F�[�_�[��ݒ�
}

WholeCakePlanet::~WholeCakePlanet()
{
}

DirectX::XMFLOAT3 WholeCakePlanet::GetPos()
{
	return m_pos;
}
