//Trade.cpp
//=====インクルード部=====
#include "Trade.h"
#include "ShaderList.h"
//=====コンストラクタ=====
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
	//---モデル読込
	m_pModel = new Model;
	//if (!m_pModel->Load("Assets/Model/Trade/Sub.fbx", 1.0f, Model::Flip::XFlip)) {
	//	MessageBox(NULL, "Assets/Model/Sub.fbx", "Error", MB_OK);
	//}
	if (!m_pModel->Load("Assets/Model/Trade/shouninn_tati6.fbx", 1.0f, Model::Flip::XFlip,Model::Kind::Anime)) {
		MessageBox(NULL, "Assets/Model/Sub.fbx", "Error", MB_OK);
	}

	//---頂点シェーダー読込
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

//=====デストラクタ=====
CTrade::~CTrade()
{
	// ----- データが存在していれば -----
	SAFE_DELETE(m_pModel);
	SAFE_DELETE(m_pVS);
	SAFE_DELETE(m_pTradeIcon);
	SAFE_DELETE(m_pTutorialIcon);
}

//=====更新処理=====
void CTrade::Update(float tick)
{
	//m_pModel->Step(tick);
}

//======描画処理=====
void CTrade::Draw()
{
	DirectX::XMFLOAT4X4 mat[3];					//行列準備
	mat[0] = GetWorldMatrix();					//モデルのワールド行列格納
	mat[1] = m_pPlayer->GetViewMatrix();		//プレイヤービュー行列格納
	mat[2] = m_pPlayer->GetProjectionMatrix();	//プレイヤープロジェクション行列格納
	m_pVS->WriteBuffer(0, mat);					//割り当て
	m_pModel->Draw();							
	/*ShaderList::SetWVP(mat);
	m_pModel->Draw(nullptr, [this](int index)//描画
	{
		const Model::Mesh* pMesh = m_pModel->GetMesh(index);
		const Model::Material* pMaterial = m_pModel->GetMaterial(pMesh->materialID);
		ShaderList::SetMaterial(*pMaterial);

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
	});*/

}

//=====プレイヤー情報設定=====
void CTrade::SetPlayer(CPlayer* player)
{
	m_pPlayer = player;
}

float CTrade::GetRadius()
{
	return m_radius;
}

//=====ワールド行列受け渡し=====
DirectX::XMFLOAT4X4 CTrade::GetWorldMatrix()
{
	DirectX::XMFLOAT4X4 mat;

	//---ワールド行列 Player Transform
	DirectX::XMMATRIX worldTrans = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y + 0.8f, m_pos.z);
	DirectX::XMMATRIX Rx = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_angle.x));
	DirectX::XMMATRIX Ry = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_angle.y));
	DirectX::XMMATRIX Rz = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_angle.z));
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);

	//---TransformとRotationを統合
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
