// 回転アニメーション機能クラス

// インクルードガード
#ifndef __SPIN_ANIMATION_H__
#define __SPIN_ANIMATION_H__

// インクルード部
#include "Component.h"

// クラス定義
class SpinAnimation : public Component
{
public:
	SpinAnimation();	// コンストラクタ
	~SpinAnimation();	// デストラクタ

	void Execute();		// 更新処理

	void Spin();		// 回転アニメーション

	// セット関数
	// 回転数セット
	void SetSpinNum(int num);

	// 回転軸設定
	void SetAxis(DirectX::XMFLOAT4 axis);

	// 回転量設定
	void SetDeltaRot(float rot);


	// ゲット関数
	// 回転数取得
	int GetSpinNum();
	// 現在の回転数取得
	int GetCurrentSpinNum();

	// 回転が止まってるか取得
	bool GetStop();
	
private:
	int m_CurrentSpinNum;		// 現在回転数
	int m_SpinNum;				// 回転数
	float m_Rot;				// 合計回転量
	float m_DeltaRot;			// 回転量
	DirectX::XMFLOAT4 m_Axis;	// 回転軸
	bool m_SpinStop;			// 回転ストップ
};

#endif // __SPIN_ANIMATION_H__