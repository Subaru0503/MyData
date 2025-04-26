///////////////////////////////////////
//
// スカイドームクラス
//
// 背景モデルの処理をする
//
///////////////////////////////////////

//----インクルードガード----
#ifndef __SKY_DOME_H__
#define __SKY_DOME_H__

//----インクルード部----
#include "GameObject.hpp"

//----コンポーネント----
#include "ModelRenderer3D.h"	// 3Dモデル描画

// クラス定義
class SkyDome : public GameObject
{
public:

	// コンストラクタ
	SkyDome(std::string name = "SkyDome");

	// デストラクタ
	~SkyDome();

	// 更新処理
	void Update();

	// 回転
	void Rot();

	// セット関数
	inline void SetCamera(GameObject* cam)
	{
		pCamObj = cam;
		SetPos(pCamObj->GetPos());	// 座標も一緒にセット
	}

private:
	//----コンポーネント----

	// 3D描画コンポーネント
	ModelRenderer3D* _modelRenderer3D;

	// カメラオブジェクト
	GameObject* pCamObj;
};

#endif // __SKY_DOME_H__