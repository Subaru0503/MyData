// 重力クラス

// インクルードガード
#ifndef __GRAVITY_H__
#define __GRAVITY_H__

// インクルード部
#include "Component.h"

// クラス定義
class Gravity : public Component
{
public:
	
	void Execute();			// 更新
private:
	float m_Gravity;		// 重力
};

#endif // __GRAVITY_H__