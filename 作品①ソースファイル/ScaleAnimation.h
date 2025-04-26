// 拡縮アニメーション機能クラス

// インクルードガード
#ifndef __SCALE_ANIMATION_H__
#define __SCALE_ANIMATION_H__

// インクルード部
#include "Component.h"

// クラス定義
class ScaleAnimation : public Component
{
public:
	ScaleAnimation();	// コンストラクタ
	~ScaleAnimation();	// デストラクタ

	void Execute();		// 更新処理

	void Scale();		// 拡縮アニメーション

	// セット関数
	inline void SetScaleRange(float range)
	{
		m_Scale = transform->GetScale();
		m_ScaleRange = range;
	}
	inline void SetMinScale(float min)
	{
		m_MinScale = min;
	}
private:
	DirectX::XMFLOAT3 m_Scale;
	float m_ScaleRange;		// 拡縮の幅
	float m_MinScale;		// 最小スケール
	int m_Frame;			// フレームカウント
};

#endif // __SCALE_ANIMATION_H__