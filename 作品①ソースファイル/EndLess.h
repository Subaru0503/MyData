///////////////////////////////////////
//
// 一生回せるネジクラス
//
///////////////////////////////////////

// インクルードガード
#ifndef __ENDLESS_H__
#define __ENDLESS_H__

// インクルード部
#include "Screw.h"


// クラス定義
class EndLess : public Screw
{
public:

	// コンストラクタ
	EndLess(std::string name = "EndLess");

	// デストラクタ
	~EndLess();

	// 回転関数
	virtual void ObjRightSpin(bool Right = true);


};

#endif // __ENDLESS_H__