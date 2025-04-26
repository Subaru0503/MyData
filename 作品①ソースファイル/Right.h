// 右矢印UIクラス

// インクルードガード
#ifndef __RIGHT_H__
#define __RIGHT_H__

// インクルード部
#include "GameObject.hpp"
#include "ModelRenderer2D.h"

// クラス定義
class Right : public GameObject
{
public:
	Right(std::string name = "Right");	// コンストラクタ
	~Right();							// デストラクタ

	void Update();						// 更新処理

	void Blink();						// 色合い変化
private:
	// コンポーネント
	ModelRenderer2D* _modelRenderer2D;

	// モデルレンダラー2D描画パラメータ
	ModelRenderer2D::Param* _modelRenderer2D_param;

	bool m_MaxFlg;
};

#endif // __GAME_OVER_H__