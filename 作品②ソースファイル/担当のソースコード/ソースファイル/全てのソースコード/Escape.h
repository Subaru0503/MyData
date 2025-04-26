#ifndef ___ESCAPE_H___
#define ___ESCAPE_H___

#include <DirectXMath.h>
#include "Defines.h"
#include "Sprite.h"
#include "Texture.h"

class EscapeUI
{
public:
	EscapeUI();
	~EscapeUI();
	void Update();
	void Draw();
	void SetYes();
	void SetNo();
	void SetWindowAnime();

private:
	float m_Left, m_Right, m_Bottom, m_Top, m_near, m_far;
	DirectX::XMFLOAT2 m_WindowPos;
	DirectX::XMFLOAT2 m_WindowSize;
	DirectX::XMFLOAT2 m_ButtonPos[2];
	DirectX::XMFLOAT2 m_ButtonSize[2];
	DirectX::XMFLOAT2 m_EscapeBGPos;
	DirectX::XMFLOAT2 m_EscapeBGSize;
	DirectX::XMFLOAT2 m_ButtonPosTexCoord[2];
	Texture* m_pTexture[4];
	bool m_bIsEscape;
	int m_nCorsor;
	int m_nMAXRatio;
	int m_nMAXRatio2;
	float m_fRatio0;
	float m_fRatio1;
	float m_fRatio2;
	bool m_bRatio;
	float m_nCnt;
	float m_nCnt2;
	float m_nCnt3;
	DirectX::XMFLOAT2 m_fBSTemp[2];
};
#endif // !___ESCAPE_H___

