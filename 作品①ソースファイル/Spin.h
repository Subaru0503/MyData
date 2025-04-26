// 回転機能クラス

// インクルードガード
#ifndef __SPIN_H__
#define __SPIN_H__

// インクルード部
#include "Component.h"

// クラス定義
class Spin : public Component
{
public:

	void XSpin(bool Right = true, float time = 0.7f);	// trueなら右回転、falseなら左回転
	void YSpin(bool Right = true, float time = 0.7f);	// trueなら右回転、falseなら左回転
	void ZSpin(bool Right = true, float time = 0.7f);	// trueなら右回転、falseなら左回転

	// セット関数
	inline void SetTorque(float torque)
	{
		m_Torque = torque;
	}
	inline void SetMoment(float moment)
	{
		m_MomentOfInertia = moment;
	}

	// ゲット関数
	inline float GetTorque()
	{
		return m_Torque;
	}
	inline float GetMoment()
	{
		return m_MomentOfInertia;
	}
	inline float GetScrewTravel()
	{
		return m_ScrewTravel;
	}

private:
	float AngularAcceleration();	// 角加速度を求める
private:
	float m_ScrewTravel;		// ネジの進んだ距離
	float m_Torque;				// トルク
	float m_MomentOfInertia;	// 慣性モーメント
};

#endif // __SPIN_H__