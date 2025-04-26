///////////////////////////////////////
//
// 締めてあるネジが段々緩んでいくクラス
//
///////////////////////////////////////

// インクルードガード
#ifndef __LOOSENRATE_H__
#define __LOOSENRATE_H__

// インクルード部
#include "Screw.h"


// クラス定義
class LoosenRate : public Screw
{
public:

	// コンストラクタ
	LoosenRate(std::string name = "LoosenRate");

	// デストラクタ
	~LoosenRate();

	// 更新処理
	void Update();

	// 緩む処理
	void LoosenRateLoosenRate();


};

#endif // __LOOSENRATE_H__