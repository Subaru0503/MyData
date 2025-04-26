// インクルード部
#include "ScaleAnimation.h"

// コンストラクタ
ScaleAnimation::ScaleAnimation()
	: m_Frame(0)
{
}

// デストラクタ
ScaleAnimation::~ScaleAnimation()
{
}

void ScaleAnimation::Execute()
{
	Scale();

	// フレームカウント
	m_Frame++;
}

void ScaleAnimation::Scale()
{
	float rate = (float)m_Frame / 120;
	float angle = 360.0f * rate;
	float radian = angle * 3.141592f / 180.0f;
	// 1～-1の範囲で拡縮すると画像が反転してしまうので、
	// 0～1の範囲に収まるように変換する(*0.5+0.5)

	// 1から-1の範囲で-をなくすためには*0.5fと+0.5をすれば－がなくなる1*0.5+0.5=1, -1*0.5+0.5=0
	float sinScaleX = sinf(radian)  * 0.5f + 0.5f;
	float sinScaleZ = sinf(radian + 3.14f)  * 0.5f + 0.5f;	// 180°分(3.14f)sinの波をずらしてxとy軸での動きをずらしている															// -にしても同じ結果は得られる


	m_Scale.x = sinScaleX * m_ScaleRange + m_MinScale;
	m_Scale.z = sinScaleZ * m_ScaleRange + m_MinScale;

	// サイズセット
	transform->SetScale(m_Scale);
}
