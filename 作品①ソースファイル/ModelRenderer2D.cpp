///////////////////////////////////////
//
// 2Dモデル描画クラス
//
// 描画に必要なシェーダーの設定等をする
//
///////////////////////////////////////

//----インクルード部----
#include "ModelRenderer2D.h"
#include "Defines.h"

// コンストラクタ
ModelRenderer2D::ModelRenderer2D()
{
	// 初期化
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

// デストラクタ
ModelRenderer2D::~ModelRenderer2D()
{
	if (m_pTexture)
	{
		delete m_pTexture;
		m_pTexture = nullptr;
	}
}

// 描画
void ModelRenderer2D::Draw()
{
	if (!m_DrawFlg) return;

	DirectX::XMFLOAT3 pos = transform->GetPos();
	DirectX::XMFLOAT4 quat = transform->GetQuat();
	DirectX::XMFLOAT3 scale = transform->GetScale();

	// 定数バッファに渡す行列の情報
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

	// 2D表示用の行列を計算
	DirectX::XMStoreFloat4x4(&mat[0],
		DirectX::XMMatrixTranspose(M));
	// 実行しないと3Dでスプライトを表示
	DirectX::XMStoreFloat4x4(&mat[1],
		DirectX::XMMatrixIdentity());

	DirectX::XMStoreFloat4x4(&mat[2],
		DirectX::XMMatrixTranspose(
			DirectX::XMMatrixOrthographicOffCenterLH(
				// 画面に合わせて表示
				0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f, 0.1f, 10.0f
			)));

	// バッファに情報を渡す
	CallByName();

	// レンダーターゲットの内容は
	// スプライト(四角形のポリゴン)に貼り付けて
	// 表示
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

// シェーダーによってバッファに渡す情報を変える
void ModelRenderer2D::CallByName()
{
	// ピクセルシェーダーの定数バッファに情報を渡す
	// 使用するピクセルシェーダーによって呼ぶ関数を変える
	if (m_ShagerName[1] == "PS_Title")
	{
		// タイトルに使うシェーダー
		SetPS_Title();
	}
}

// タイトルにで使うシェーダーに情報を渡す
void ModelRenderer2D::SetPS_Title()
{
	// カメラ座標取得
	DirectX::XMFLOAT3 camPos = m_pCamObj->GetPos();

	// ピクセルシェーダーに情報を渡す
	m_PS->WriteBuffer(0, &camPos);
}

// 頂点シェーダー設定
void ModelRenderer2D::SetVertexShader(Shader * vs, const char* shaderFiles)
{
	// 頂点シェーダー設定
	m_VS = vs;

	// 名前取得
	m_ShagerName[0] = shaderFiles;
}

// ピクセルシェーダー設定
void ModelRenderer2D::SetPixelShader(Shader * ps, const char* shaderFiles)
{
	// ピクセルシェーダー設定
	m_PS = ps;

	// 名前取得
	m_ShagerName[1] = shaderFiles;
}
