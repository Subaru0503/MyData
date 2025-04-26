// ゲームスタート文字クラス

// インクルードガード
#ifndef __START_H__
#define __START_H__

// インクルード部
#include "GameObject.hpp"
// コンポーネント
#include "ModelRenderer2D.h"
#include "OpacityController.h"

// クラス定義
class Start : public GameObject
{
public:
	Start(std::string name = "Start");	// コンストラクタ
	~Start();							// デストラクタ

	void Update();						// 更新処理

private:
	// コンポーネント
	ModelRenderer2D* _modelRenderer2D;
	Opacity* _opacity;

	// モデルレンダラー2D描画パラメータ
	ModelRenderer2D::Param* _modelRenderer2D_param;
};

#endif // __GAME_OVER_H__