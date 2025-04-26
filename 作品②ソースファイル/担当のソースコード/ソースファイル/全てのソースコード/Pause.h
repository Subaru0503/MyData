#ifndef ___PAUSE_H___
#define ___PAUSE_H___

#include <DirectXMath.h>
#include "Defines.h"
#include "Sprite.h"
#include "Texture.h"

class Pause
{
public:
	Pause();
	~Pause();
	void Update(int select);
	void Draw();


private:
	float m_Left, m_Right, m_Bottom, m_Top, m_near, m_far;
	DirectX::XMFLOAT2 m_WindowPos;
	DirectX::XMFLOAT2 m_WindowSize;
	DirectX::XMFLOAT2 m_ButtonPos[3];
	DirectX::XMFLOAT2 m_ButtonSize[3];
	DirectX::XMFLOAT2 m_BGPos;
	DirectX::XMFLOAT2 m_BGSize;
	DirectX::XMFLOAT2 m_ButtonPosTexCoord[3];
	DirectX::XMFLOAT2 m_ButtonIconPos;
	DirectX::XMFLOAT2 m_ButtonIconSize;
	Texture* m_pTexture[6];
	int m_nCorsor;
	int m_nMAXRatio;
	float m_fRatio0;
	float m_fRatio1;
	float m_fRatio2;
};



#endif // !___PAUSE_H___

