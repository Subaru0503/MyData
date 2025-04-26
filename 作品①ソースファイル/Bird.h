// 鳥クラス

// インクルードガード
#ifndef __BIRD_H__
#define __BIRD_H__

// インクルード部
#include "GameObject.hpp"
// コンポーネント
#include "ModelRenderer2D.h"

#include "float3.h"

// クラス定義
class Bird : public GameObject
{
public:
	Bird(std::string name = "Bird");			// コンストラクタ
	~Bird();									// デストラクタ

	void Update();								// 更新処理

	void fly();									// 飛行

	// セット関数
	void SetVelocity(float velocity);			// 速度設定

	void SetAcceleration(float acceleration);	// 加速度設定
private:
	// コンポーネント
	ModelRenderer2D* _modelRenderer2D;

	float m_Velocity;		// 速度
	float m_Acceleration;	// 加速度
	float m_Time;			// 時間
};

#endif // __BIRD_H__