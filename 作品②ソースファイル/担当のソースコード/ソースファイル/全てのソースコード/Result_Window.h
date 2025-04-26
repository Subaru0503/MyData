#ifndef ___RESULT_WINDOW_H___
#define ___RESULT_WINDOW_H___

#include <DirectXMath.h>
#include "Defines.h"
#include "Sprite.h"
#include "Texture.h"

class ResultWindow
{
public:
	ResultWindow();
	~ResultWindow();
	void Update();
	void Draw();
	void SetSelect();
	void SetRestart();

private:
	float m_Left, m_Right, m_Bottom, m_Top, m_near, m_far;
	DirectX::XMFLOAT2 m_WindowPos;
	DirectX::XMFLOAT2 m_WindowSize;
	DirectX::XMFLOAT2 m_ButtonPos[2];
	DirectX::XMFLOAT2 m_ButtonSize[2];
	DirectX::XMFLOAT2 m_ButtonIconPos;
	DirectX::XMFLOAT2 m_ButtonIconSize;
	DirectX::XMFLOAT2 m_ButtonPosTexCoord[2];
	Texture* m_pTexture[4];
	int m_nCorsor;
	int m_nMAXRatio;
	float m_fRatio0;

};


#endif // !___RESULT_WINDOW_H___

