///////////////////////////////////////
//
// 2Dモデル描画クラス
//
// 描画に必要なシェーダーの設定等をする
//
///////////////////////////////////////

//----インクルードガード----
#ifndef __MODEL_RENDERER_2D_H__
#define __MODEL_RENDERER_2D_H__

//----インクルード部----
#include "Component.h"
#include "Texture.h"
#include "Camera.h"
#include "Sprite.h"

// クラス定義
class ModelRenderer2D : public Component
{
public:
	// 描画パラメータ
	struct Param
	{
		DirectX::XMFLOAT2 uvSize;
		DirectX::XMFLOAT4 color;
		int animeNo;
		DirectX::XMINT2 MaxGrid;
	};

public:

	// コンストラクタ
	ModelRenderer2D();

	// デストラクタ
	~ModelRenderer2D();

	// 描画
	void Draw();

	// シェーダーによってバッファに渡す情報を変える
	void CallByName();
	
	// タイトルにで使うシェーダーに情報を渡す
	void SetPS_Title();

	// テクスチャ読み込み
	inline void Load(const char* name)
	{
		if (FAILED(m_pTexture->Create(name)))
		{
			MessageBox(NULL, name, "Error", MB_OK);
		}
	}

	//----セット関数----
	inline void SetCamera(GameObject* camObj, Camera* camera)
	{
		m_pCamObj = camObj;
		m_pCamera = camera;
	}
	inline void SetDraw(bool flg)
	{
		m_DrawFlg = flg;
	}

	// 頂点シェーダー設定
	void SetVertexShader(Shader* vs, const char* shaderFiles);

	// ピクセルシェーダー設定
	void SetPixelShader(Shader* ps, const char* shaderFiles);


	//----ゲット関数----
	inline Param* GetParam()
	{
		return &m_Param;
	}
	inline bool GetDraw()
	{
		return m_DrawFlg;
	}

private:

	// カメラ
	GameObject* m_pCamObj;
	Camera* m_pCamera;

	// シェーダー名
	const char* m_ShagerName[2];

	// 頂点シェーダー
	Shader* m_VS;

	// ピクセルシェーダー
	Shader* m_PS;

	// テクスチャ
	Texture* m_pTexture;

	// 描画パラメータ
	Param m_Param;

	// 描画フラグ
	bool m_DrawFlg;
};

#endif // __MODEL_RENDERER_2D_H__