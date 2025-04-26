#ifndef ___SELECT_H___
#define ___SELECT_H___


#include <DirectXMath.h>
#include "Defines.h"
#include "Sprite.h"
#include "Texture.h"

class Select
{
public:
	Select();
	~Select();
	void Update(int select);
	void Draw();
	void UpdateNewRequest();
	void DrawNewRequest();

private:
	/*int m_nclearTime;
	int m_nTimeMinutes;
	int m_nTimeSeconds;
	int m_nper;*/
	float m_Left, m_Right, m_Bottom, m_Top, m_near, m_far;

	Texture* m_pTexture[7];
	DirectX::XMFLOAT2 m_RequenstPos;
	DirectX::XMFLOAT2 m_RequenstSize;
	DirectX::XMFLOAT2 m_BackButtonPos;
	DirectX::XMFLOAT2 m_BackButtonSize;
	DirectX::XMFLOAT2 m_NewRequestPos;
	DirectX::XMFLOAT2  m_NewRequestSize;
	DirectX::XMFLOAT2 m_PlayButtonPos;
	DirectX::XMFLOAT2 m_PlayButtonSize;
	DirectX::XMFLOAT2 m_ShopButtonPos;
	DirectX::XMFLOAT2 m_ShopButtonSize;
	DirectX::XMFLOAT2 m_RequestPosTexCoord;


	int m_nMAXRatio;
	float m_fRatio;
	float m_fRatio2;
	float m_falPha;
	float m_falPha2;
	int m_nCnt;


};

#endif // !___SELECT_H___




