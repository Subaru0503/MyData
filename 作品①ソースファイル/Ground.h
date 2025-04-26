///////////////////////////////////////
//
// 地面クラス
//
// ステージの床
//
///////////////////////////////////////

//----インクルードガード----
#ifndef __GROUND_H__
#define __GROUND_H__

//----インクルード部----
#include "GameObject.hpp"

//----コンポーネント----
#include "BoxCollider.h"		// 当たり判定
#include "ModelRenderer3D.h"	// 3Dモデル描画

// クラス定義
class Ground : public GameObject
{
public:

	// コンストラクタ
	Ground(std::string name = "Ground");

	// デストラクタ
	~Ground();


	// 更新処理
	void Update();

private:
	//----コンポーネント----

	// ボックスコライダーコンポーネント
	BoxCollider* _boxCollider;

	// 3D描画コンポーネント
	ModelRenderer3D* _modelRenderer3D;

};

#endif // __GROUND_H__