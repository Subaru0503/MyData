#include "MushroomPlanet.h"

MushroomPlanet::MushroomPlanet()
{
	m_pos = { 6.0f, 1.2f, 5.0f };
	m_scale = { 1.0f, 1.0f, 1.0f};
	m_rotate = { 0.0f, 90.0f, 0.0f};

	// ���f���ǂݍ���
	m_pModel = new Model();
	if (!m_pModel->Load("Assets/Model/MushroomPlanet/MushroomPlanet.fbx", 0.12f, Model::Flip::XFlip)) {
		MessageBox(NULL, "Assets/Model//MushroomPlanet/MushroomPlanet.fbx", "Error", MB_OK);
	}
	// ���_�V�F�[�_�[�ǂݍ���
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}
	m_pModel->SetVertexShader(m_pVS);	// ���f���ɒ��_�V�F�[�_�[��ݒ�
}

MushroomPlanet::~MushroomPlanet()
{
}

DirectX::XMFLOAT3 MushroomPlanet::GetPos()
{
	return m_pos;
}
