// 左矢印UIクラス

// インクルードガード
#ifndef __LEFT_H__
#define __LEFT_H__

// インクルード部
#include "GameObject.hpp"
#include "ModelRenderer2D.h"

// クラス定義
class Left : public GameObject
{
public:
	Left(std::string name = "Left");	// コンストラクタ
	~Left();							// デストラクタ

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