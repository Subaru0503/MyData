///////////////////////////////////////
//
// モデル描画クラス
//
// 描画に必要なシェーダーの設定等をする
//
///////////////////////////////////////

// インクルード部
#include "ModelRenderer3D.h"

// コンストラクタ
ModelRenderer3D::ModelRenderer3D()
	: m_pModel(nullptr)
	, m_ModelName{}
	, m_Scale(1.0f)
	, m_Time(0.0f)
	, m_DrawFlg(true)
{
}

// デストラクタ
ModelRenderer3D::~ModelRenderer3D()
{
	if (m_pModel)
		delete m_pModel;
}

// 更新
void ModelRenderer3D::Execute()
{
	// 時間経過
	m_Time += 1.0f / 60.0f * 2;
}

// 描画
void ModelRenderer3D::Draw()
{
	// 描画フラグが下がってたら描画しない
	if (!m_DrawFlg) return;

	// セットしているシェーダーの名前によって
	// シェーダーに渡すデータを変える
	CallByName();

	// 描画
	// モデルがセットされてない
	if (!m_pModel)
	{
		MessageBox(NULL, "モデルがセットされてない", "ModelRenderer3D", MB_OK);
		return;
	}

	// シェーダーセット
	m_pModel->SetVertexShader(m_Shader[0]);
	m_pModel->SetPixelShader(m_Shader[1]);

	// モデル描画
	m_pModel->Draw();
}

// シェーダーによってバッファに渡す情報を変える
void ModelRenderer3D::CallByName()
{
	// 頂点シェーダーの定数バッファに情報を渡す
	// 使用する頂点シェーダーによって呼ぶ関数を変える
	if (m_ShagerName[0] == "VS_Object" || m_ShagerName[0] == "VS_World")
	{
		SetVS_Default();	// 行列情報を渡す
	}


	// ピクセルシェーダーの定数バッファに情報を渡す
	// 使用するピクセルシェーダーによって呼ぶ関数を変える
	if (m_ShagerName[1] == "PS_SkyBrightness")
	{
		// 空の色を変えるシェーダー
		SetPS_Sky();
	}
}

// 行列情報を渡す
void ModelRenderer3D::SetVS_Default()
{
	// カメラがセットされてない
	if (!m_pCamera)
	{
		MessageBox(NULL, "カメラがセットされてない", "ModelRenderer3D", MB_OK);
		return;
	}

	// 定数バッファに渡す行列の情報
	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixIdentity());
	mat[1] = m_pCamera->GetView();
	mat[2] = m_pCamera->GetProj();

	// シェーダーがセットされてない
	if (!m_Shader[0] || !m_Shader[1])
	{
		MessageBox(NULL, "シェーダーがセットされてない", "ModelRenderer3D", MB_OK);
		return;
	}

	// 座標の更新
	mat[0] = transform->GetWorld();
	m_Shader[0]->WriteBuffer(0, mat);
}

// 空の色を変えるピクセルシェーダー
void ModelRenderer3D::SetPS_Sky()
{
	// シェーダーの時間パラメータを更新
	float dayDuration = 360.0f; // 1週の時間
	float timeOfDay = fmod(m_Time, dayDuration) / dayDuration;

	// 現在の時間を渡す
	m_Shader[1]->WriteBuffer(0, &timeOfDay);
}

// パス指定
void ModelRenderer3D::SetPath(std::string name)
{
	for (int i = 0; i < name.size(); i++)
	{
		m_ModelName[i] = name[i];
	}
	m_ModelName[name.size()] = '\0';

	m_pModel = new Model();
	m_pModel->Load(m_ModelName, m_Scale);
}

// シェーダーセット
void ModelRenderer3D::SetShader(const char ** shaderFiles)
{
	for (int i = 0; i < 2; ++i)
	{
		if (strstr(shaderFiles[i], "PS_") == shaderFiles[i]) {
			m_Shader[1] = ShaderManager::GetInstance().GetShader<PixelShader>(shaderFiles[i]);
			m_ShagerName[1] = shaderFiles[i];	// 名前保存
		}
		else if (strstr(shaderFiles[i], "VS_") == shaderFiles[i]) {
			m_Shader[0] = ShaderManager::GetInstance().GetShader<VertexShader>(shaderFiles[i]);
			m_ShagerName[0] = shaderFiles[i];	// 名前保存
		}
		else {
			MessageBox(NULL, shaderFiles[i], "Shader name [VS_ / PS_]", MB_OK);
		}
	}
}

// 描画フラグをセット
void ModelRenderer3D::SetDrawFlg(bool flg)
{
	m_DrawFlg = flg;
}

// 描画フラグを返す
bool ModelRenderer3D::GetDrawFlg()
{
	return m_DrawFlg;
}
