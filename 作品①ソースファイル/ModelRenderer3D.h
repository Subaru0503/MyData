///////////////////////////////////////
//
// モデル描画クラス
//
// 描画に必要なシェーダーの設定等をする
//
///////////////////////////////////////

// インクルードガード
#ifndef __MODEL_RENDERER_3D_H__
#define __MODEL_RENDERER_3D_H__

// インクルード部
#include "Component.h"
#include "Model.h"
#include "Camera.h"

// シェーダーマネージャー
#include "ShaderManager.h"

// クラス指定
class ModelRenderer3D : public Component
{
public:

	// コンストラクタ
	ModelRenderer3D();

	// デストラクタ
	~ModelRenderer3D();

	// 更新
	void Execute() final;

	// 描画
	void Draw();

	// シェーダーによってバッファに渡す情報を変える
	void CallByName();

	// 行列情報を渡す
	void SetVS_Default();

	// 空の色を変えるピクセルシェーダー
	void SetPS_Sky();

	// パス指定
	void SetPath(std::string name);

	//----セット関数----

	// カメラセット
	inline void SetCamera(Camera* camera)
	{
		m_pCamera = camera;
	}
	
	// シェーダーセット
	void SetShader(const char** shaderFiles);

	// 描画フラグをセット
	void SetDrawFlg(bool flg);

	//----ゲット関数----

	// 描画フラグを返す
	bool GetDrawFlg();

private:

	// カメラ
	Camera* m_pCamera;

	// パス
	char m_ModelName[MAX_PATH];

	// モデル
	Model* m_pModel;

	// モデル大きさ
	float m_Scale;

	// シェーダー名
	const char* m_ShagerName[2];

	// モデルに適用するシェーダー
	Shader* m_Shader[2];

	// 時間
	float m_Time;

	// 描画フラグ
	bool m_DrawFlg;
};

#endif // __MODEL_RENDERER_3D_H__