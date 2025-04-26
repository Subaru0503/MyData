// インクルード部
#include "Gravity.h"

// 定数・マクロ定義
#define GRAVITY (0.21f)

// 更新処理
void Gravity::Execute()
{
	DirectX::XMFLOAT3 pos = transform->GetPos();

	pos.y -= GRAVITY;	// 重力計算

	transform->SetPos(pos);	// 値更新
}
