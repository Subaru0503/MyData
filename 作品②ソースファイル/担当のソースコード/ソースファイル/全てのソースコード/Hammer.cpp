#include "Hammer.h"
#include "Geometory.h"
#include "Defines.h"
#include "ShaderList.h"
CHammer::CHammer()
	:m_scale(1.0f, 1.0f, 1.0f)
	,m_rotate(0.0f, 0.0f, 0.0f)
	,m_pos(0.0f, 0.0f, 0.0f)
	,HammerCount(0.0f)
{
	// ----- モデル -----
	m_pModel = new Model;
	if (!m_pModel->Load("Assets/Model/hunmmer/hunmer_taiki.fbx", 0.17f, Model::Flip::XFlip, Model::Kind::Anime)) {
		MessageBox(NULL, "Assets/Model/hunmmer/hunmer_taiki.fbx", "Error", MB_OK);
	}

	// ----- 頂点シェーダー -----
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}
	m_pModel->SetVertexShader(m_pVS);	//モデルへ読み込んだ頂点シェーダーを設定
	m_pModel->SetVertexShader(ShaderList::GetVS(ShaderList::VS_ANIME));
	m_pModel->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	anime[0] = m_pModel->AddAnimation("Assets/Model/hunmmer/hunmer_taiki.fbx");
	anime[1] = m_pModel->AddAnimation("Assets/Model/hunmmer/hunmer.fbx");
}

CHammer::~CHammer()
{
	SAFE_DELETE(m_pModel);
	SAFE_DELETE(m_pVS);
}

void CHammer::Update(float tick)
{
	if (HammerCount)
	{
		m_pModel->Play(anime[1], true, 1.0f);
		HammerCount--;
	}
	else
	{
		m_pModel->Play(anime[0], true, 1.0f);
	}
	m_pModel->Step(tick);
}

void CHammer::Draw(DirectX::XMFLOAT4X4 *mat, VertexShader* vs)
{
	DirectX::XMMATRIX world;
	//---変換行列を計算
	world = DirectX::XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z) *
		DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_rotate.x)) *
		DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(90.0f)) *
		DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_rotate.z)) *
		DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);

	world = DirectX::XMMatrixTranspose(world);
	DirectX::XMStoreFloat4x4(&mat[0], world);

	//---変換行列を設定
	Geometory::SetWorld(mat[0]);
	Geometory::SetView(mat[1]);
	Geometory::SetProjection(mat[2]);

	RenderTarget* pRTV = GetDefaultRTV();
	DepthStencil* pDSV = GetDefaultDSV();
	SetRenderTargets(1, &pRTV, pDSV);

	m_pVS->WriteBuffer(0, mat);

	m_pModel->Draw(nullptr, [this](int index)
	{
		const Model::Mesh* pMesh = m_pModel->GetMesh(index);
		const Model::Material* pMaterial = m_pModel->GetMaterial(pMesh->materialID);
		ShaderList::SetMaterial_Custom(*pMaterial);

		DirectX::XMFLOAT4X4 bones[500];
		for (int i = 0; i < pMesh->bones.size() && i < 500; ++i)
		{
			// この計算はゲームつくろー「スキンメッシュの仕組み」が参考になる
			DirectX::XMStoreFloat4x4(&bones[i], DirectX::XMMatrixTranspose(
				pMesh->bones[i].invOffset *
				m_pModel->GetBone(pMesh->bones[i].index)
			));
		}
		ShaderList::SetBones(bones);
	});

}


void CHammer::SetPlayerPos(DirectX::XMFLOAT3 pos)
{
	m_pos = pos;
}

void CHammer::HammerAnimetion()
{
	HammerCount = 60.0f;
}
