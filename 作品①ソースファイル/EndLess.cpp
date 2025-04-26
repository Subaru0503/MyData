///////////////////////////////////////
//
//  一生回せるネジクラス
//
///////////////////////////////////////

// インクルード部
#include "EndLess.h"

//----マネージャー----
#include "SoundManager.h"	// サウンドマネージャー

// コンストラクタ
EndLess::EndLess(std::string name)
	: Screw(name)
{

}

// デストラクタ
EndLess::~EndLess()
{
}

// 回転関数
void EndLess::ObjRightSpin(bool Right)
{
	//----変数宣言----

	// 再生終了フラグ
	bool PlayEnd;

	// 実態確認
	if (!m_Nut)
	{
		MessageBox(NULL, "ナットの設定がされてない", "Screw.cpp", MB_OK);
	}

	// 回転フラグ上げ
	m_SpinFlg = true;

	// 再生終了フラグを取得
	PlayEnd = SoundManager::GetInstance().CheckSoundEnd(SoundManager::ScrewSE::Spin);

	// 右回転
	if (m_Nut->GetPos().y <= m_pos.y && Right)
	{
		// Y軸右回転
		_spin->YSpin();

		// 再生してなかったら
		if (PlayEnd)
		{
			// 回転SE
			SoundManager::GetInstance().playSound(SoundManager::ScrewSE::Spin);
		}

		// 回し切ったSE再生済フラグを下げる
		m_SpinMaxPlayingSE = false;
	}
	// 左回転
	else if (m_Nut->GetPos().y + 0.5f >= m_pos.y && !Right)
	{
		// Y軸左回転
		_spin->YSpin(false);

		// 再生してなかったら
		if (PlayEnd)
		{
			// 回転SE
			SoundManager::GetInstance().playSound(SoundManager::ScrewSE::Spin);
		}

		// 回し切ったSE再生済フラグを下げる
		m_SpinMaxPlayingSE = false;
	}
}
