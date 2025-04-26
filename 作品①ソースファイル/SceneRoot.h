///////////////////////////////////////
//
// シーン管理クラス
//
// シーンの管理をする
//
///////////////////////////////////////

//----インクルードガード----
#ifndef __SCENE_ROOT_H__
#define __SCENE_ROOT_H__

//----インクルード部----
#include "SceneBase.hpp"
#include <DirectXMath.h>

// クラス定義
class SceneRoot : public SceneBase
{
public:
	// コンストラクタ
	SceneRoot() : SceneBase("Root") {}

	// 初期化
	void Init();

	// 終了処理
	void Uninit();

	// 更新処理
	void Update(float tick);

	// 描画処理
	void Draw();

	// シーン切り替え
	void SceneChange();


	//----セット関数----

	// シーン操作関数
	static void SetNextScene(SceneBase::Scene next);


	//----ゲット関数----

	// 次のシーンを取得
	static SceneBase::Scene GetNextScene();

	// 現在のシーンを取得
	static SceneBase::Scene GetCurrentScene();

private:
	//----シーンに関するもの----

	// 次のシーン情報
	static Scene m_NextScene;

	// 現在のシーン情報
	static Scene m_CurrentScene;

#ifdef _DEBUG
	DirectX::XMFLOAT3 m_camPos;
	DirectX::XMFLOAT3 m_camLook;
	DirectX::XMFLOAT3 m_camUp;
#endif
};

#endif // __SCENE_ROOT_H__

