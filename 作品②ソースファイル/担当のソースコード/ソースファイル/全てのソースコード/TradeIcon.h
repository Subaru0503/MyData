#ifndef ___TRADE_ICON_H___
#define ___TRADE_ICON_H___

#include <DirectXMath.h>
#include "Defines.h"
#include "Sprite.h"
#include "Texture.h"
#include "Player.h"



class TradeIcon
{
public:
	TradeIcon();
	~TradeIcon();
	void Update();
	void Draw();
	void SetPos(DirectX::XMFLOAT3 pos);
	void SetPlayer(CPlayer* player);

private:
	DirectX::XMFLOAT3 m_pos;
	Texture* m_pTex;
	CPlayer* m_pPlayer;
	int m_nMaxRatio;
	float m_fRatio;
	
};





#endif // !___TRADE_ICON_H___

