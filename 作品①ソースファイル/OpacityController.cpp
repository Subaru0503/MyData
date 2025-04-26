// インクルード部
#include "OpacityController.h"

// コンストラクタ
Opacity::Opacity()
{
	m_Alpha = 1.0f;
	m_ClearFlg = false;
}

// デストラクタ
Opacity::~Opacity()
{
}

// 更新処理
void Opacity::Execute()
{
	Blink();
}

// 透明度変化
void Opacity::Blink()
{
	// 透明になっていたら
	if (m_ClearFlg)
	{
		m_Alpha += m_Value;		// 透明度を下げる
		// 透明度がなくなったら
		if (m_Alpha >= 1.0f)
		{
			m_ClearFlg = false;	// フラグ下げ
		}
	}
	// 透明度がなくなっていたら
	else
	{
		m_Alpha -= m_Value;		// 透明度を上げる
		// 透明になったら
		if (m_Alpha <= 0.0f)
		{
			m_ClearFlg = true;	// フラグ上げ
		}
	}

	// 透明度更新
	m_Param->color.w = m_Alpha;
}
