//Trade.cpp
//=====�C���N���[�h��=====
#include "Trade.h"
#include "ShaderList.h"
//=====�R���X�g���N�^=====
CTrade::CTrade(float posX, float posY, float posZ, float Rot)
	: m_pos(posX, posY, posZ)
	, m_scale(0.18f, 0.18f, 0.18f)
	, m_angle(0.0f, Rot, 0.0f)
	, m_radius(3.0f)
	, m_pPlayer(nullptr)
	, m_pModel(nullptr)
	, m_pVS(nullptr)
	, m_nMaxRatio(0)
	, m_fRatio(1.0f)
{
	//---���f���Ǎ�
	m_pModel = new Model;
	//if (!m_pModel->Load("Assets/Model/Trade/Sub.fbx", 1.0f, Model::Flip::XFlip)) {
	//	MessageBox(NULL, "Assets/Model/Sub.fbx", "Error", MB_OK);
	//}
	if (!m_pModel->Load("Assets/Model/Trade/shouninn_tati6.fbx", 1.0f, Model::Flip::XFlip,Model::Kind::Anime)) {
		MessageBox(NULL, "Assets/Model/Sub.fbx", "Error", MB_OK);
	}

	//---���_�V�F�[�_�[�Ǎ�
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}
	m_pModel->SetVertexShader(m_pVS);
	//m_pModel->SetVertexShader(ShaderList::GetVS(ShaderList::VS_ANIME));
	//m_pModel->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	//anime = m_pModel->AddAnimation("Assets/Model/Trade/shouninn_taiki.fbx");
	//m_pModel->Play(anime, true, 1.0f);
	m_pTradeIcon = new Texture();
	m_pTutorialIcon = new Texture();
	if (FAILED(m_pTradeIcon->Create("Assets/Texture/UI_TradeIcon2.png")))
	{
		MessageBox(NULL, "Trade UI_TradeIcon2.png", "Error", MB_OK);
	}
	if (FAILED(m_pTutorialIcon->Create("Assets/Texture/UI_TradeIcon3.png")))
	{
		MessageBox(NULL, "Trade UI_TradeIcon3.png", "Error", MB_OK);
	}
}

//=====�f�X�g���N�^=====
CTrade::~CTrade()
{
	// ----- �f�[�^�����݂��Ă���� -----
	SAFE_DELETE(m_pModel);
	SAFE_DELETE(m_pVS);
	SAFE_DELETE(m_pTradeIcon);
	SAFE_DELETE(m_pTutorialIcon);
}

//=====�X�V����=====
void CTrade::Update(float tick)
{
	//m_pModel->Step(tick);
}

//======�`�揈��=====
void CTrade::Draw()
{
	DirectX::XMFLOAT4X4 mat[3];					//�s�񏀔�
	mat[0] = GetWorldMatrix();					//���f���̃��[���h�s��i�[
	mat[1] = m_pPlayer->GetViewMatrix();		//�v���C���[�r���[�s��i�[
	mat[2] = m_pPlayer->GetProjectionMatrix();	//�v���C���[�v���W�F�N�V�����s��i�[
	m_pVS->WriteBuffer(0, mat);					//���蓖��
	m_pModel->Draw();							
	/*ShaderList::SetWVP(mat);
	m_pModel->Draw(nullptr, [this](int index)//�`��
	{
		const Model::Mesh* pMesh = m_pModel->GetMesh(index);
		const Model::Material* pMaterial = m_pModel->GetMaterial(pMesh->materialID);
		ShaderList::SetMaterial(*pMaterial);

		DirectX::XMFLOAT4X4 bones[500];
		for (int i = 0; i < pMesh->bones.size() && i < 500; ++i)
		{
			// ���̌v�Z�̓Q�[������[�u�X�L�����b�V���̎d�g�݁v���Q�l�ɂȂ�
			DirectX::XMStoreFloat4x4(&bones[i], DirectX::XMMatrixTranspose(
				pMesh->bones[i].invOffset *
				m_pModel->GetBone(pMesh->bones[i].index)
			));
		}
		ShaderList::SetBones(bones);
	});*/

}

//=====�v���C���[���ݒ�=====
void CTrade::SetPlayer(CPlayer* player)
{
	m_pPlayer = player;
}

float CTrade::GetRadius()
{
	return m_radius;
}

//=====���[���h�s��󂯓n��=====
DirectX::XMFLOAT4X4 CTrade::GetWorldMatrix()
{
	DirectX::XMFLOAT4X4 mat;

	//---���[���h�s�� Player Transform
	DirectX::XMMATRIX worldTrans = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y + 0.8f, m_pos.z);
	DirectX::XMMATRIX Rx = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_angle.x));
	DirectX::XMMATRIX Ry = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_angle.y));
	DirectX::XMMATRIX Rz = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_angle.z));
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);

	//---Transform��Rotation�𓝍�
	DirectX::XMMATRIX worldMatrix = S * Rx * Ry * Rz * worldTrans;

	worldMatrix = DirectX::XMMatrixTranspose(worldMatrix);
	DirectX::XMStoreFloat4x4(&mat, worldMatrix);

	return mat;
}

DirectX::XMFLOAT3 CTrade::GetPos()
{
	return m_pos;
}

DirectX::XMFLOAT3 CTrade::GetAngle()
{
	return m_angle;
}



void CTrade::SetPos(DirectX::XMFLOAT3 pos)
{
	IconPos = pos;
}
