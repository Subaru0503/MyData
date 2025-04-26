// 時間クラス

// インクルードガード
#ifndef __TIME_H__
#define __TIME_H__

// インクルード部
#include "GameObject.hpp"
// コンポーネント
#include "ModelRenderer2D.h"

#include "float3.h"

// クラス定義
class Time : public GameObject
{
public:
	Time(std::string name = "Time");		// コンストラクタ
	~Time();								// デストラクタ

	void Update();							// 更新処理

	void AlphaUpdate();						// 透明度処理

	// セット関数
	inline void SetAnimeNo(int no)
	{
		_modelRenderer2D_param->animeNo = no;
	}

private:
	// コンポーネント
	ModelRenderer2D* _modelRenderer2D;

	// モデルレンダラー2D描画パラメータ
	ModelRenderer2D::Param* _modelRenderer2D_param;

	float m_Time;				// 経過時間
	float m_Alpha;				// アルファ値
};

#endif // __TIME_H__