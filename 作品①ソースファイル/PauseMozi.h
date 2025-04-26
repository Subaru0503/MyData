// ポーズメッセージクラス

// インクルードガード
#ifndef __PAUSE_MOZI_H__
#define __PAUSE_MOZI_H__

// インクルード部
#include "GameObject.hpp"
// コンポーネント
#include "ModelRenderer2D.h"
#include "OpacityController.h"

// クラス定義
class PauseMozi : public GameObject
{
public:
	PauseMozi(std::string name = "PauseMozi");	// コンストラクタ
	~PauseMozi();							// デストラクタ

	void Update();						// 更新処理

private:
	// コンポーネント
	ModelRenderer2D* _modelRenderer2D;
	Opacity* _opacity;

	// モデルレンダラー2D描画パラメータ
	ModelRenderer2D::Param* _modelRenderer2D_param;
};

#endif // __GAME_OVER_H__