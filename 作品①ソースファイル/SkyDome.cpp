///////////////////////////////////////
//
// スカイドームクラス
//
// 背景モデルの処理をする
//
///////////////////////////////////////

//----インクルード部----
#include "SkyDome.h"

//----シーン----
#include "SceneRoot.h"

// コンストラクタ
SkyDome::SkyDome(std::string name)
	: GameObject(name)
{
	m_tag = "SkyDome";

	// コンポーネント追加
	AddComponent<ModelRenderer3D>();	// 3D描画

	// コンポーネント取得
	_modelRenderer3D = GetComponent<ModelRenderer3D>();

	// モデル読み込み
	_modelRenderer3D->SetPath("Assets/Model/Sky/Sky.fbx");

	// 初期化
	m_pos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	SetScale(DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));
	m_quat = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	pCamObj = nullptr;

	// タイトルシーンなら専用のピクセルシェーダーにする
	if (SceneRoot::GetCurrentScene() == SceneRoot::Scene::TITLE)
	{
		// シェーダーセット
		const char* file[] = {
			"VS_Object",
			"PS_SkyBrightness",
		};

		_modelRenderer3D->SetShader(file);
	}
	else
	{
		// シェーダーセット
		const char* file[] = {
			"VS_Object",
			"PS_TexColor",
		};

		_modelRenderer3D->SetShader(file);
	}
}

// デストラクタ
SkyDome::~SkyDome()
{
}

// 更新処理
void SkyDome::Update()
{
	// カメラの設定がされてなかったら処理しない
	if (!pCamObj) return;

	// 背景とカメラの座標を同じにする
	SetPos(pCamObj->GetPos());

	// 回転
	Rot();
}

// 回転
void SkyDome::Rot()
{
	// 回転取得
	DirectX::XMVECTOR qRotate = DirectX::XMLoadFloat4(&m_quat);

	DirectX::XMMATRIX RotMat = DirectX::XMMatrixRotationQuaternion(qRotate);

	float rotY = 0.0f;
	rotY += 1.0f / 60.0f;

	// 軸に合わせて回転
	DirectX::XMVECTOR quat = DirectX::XMQuaternionRotationAxis(
		DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), DirectX::XMConvertToRadians(rotY)
	);

	// クォータニオン掛け算
	qRotate = DirectX::XMQuaternionMultiply(qRotate, quat);

	// 角度更新
	DirectX::XMStoreFloat4(&m_quat, qRotate);
}
