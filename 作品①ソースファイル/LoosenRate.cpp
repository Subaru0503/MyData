///////////////////////////////////////
//
// 締めてあるネジが段々緩んでいくクラス
//
///////////////////////////////////////

// インクルード部
#include "LoosenRate.h"

// コンストラクタ
LoosenRate::LoosenRate(std::string name)
	: Screw(name)
{

}

// デストラクタ
LoosenRate::~LoosenRate()
{
}

// 更新処理
void LoosenRate::Update()
{
	// ネジが緩む物で
	// プレイヤーが回してる最中じゃなくて
	// ネジが最大まで緩んでなかったら
	if (!m_SpinFlg &&
		m_Nut->GetPos().y + 0.5f > m_pos.y)
	{
		LoosenRateLoosenRate();
	}


}

// 緩む処理
void LoosenRate::LoosenRateLoosenRate()
{
	_spin->YSpin(false, 0.3f);					// Y軸左回転
	_move->SetMove(_spin->GetScrewTravel());	// 移動量セット
	_move->UPMove();							// 上方向移動
}
