#ifndef ___ENDING_H___
#define ___ENDING_H___

#include <DirectXMath.h>
#include "Defines.h"
#include "Sprite.h"
#include "Texture.h"
#include "XController.h"

class Ending
{
public:
	Ending();
	~Ending();
	void Update();
	void Draw();
	bool IsEndAnime();

private:
	/*int m_nclearTime;
	int m_nTimeMinutes;
	int m_nTimeSeconds;
	int m_nper;*/
	float m_Left, m_Right, m_Bottom, m_Top, m_near, m_far;
	float m_basePosX, m_basePosY;
	Texture* m_pTexture[4];
	int m_animeNo;
	int m_frame;
	int m_totalFrame;
	DirectX::XMFLOAT2 m_uvPos;
	DirectX::XMFLOAT2 m_uvSize;
	bool m_bEndAnime;
	int m_nTexNo;
	XINPUT_STATE state;
	XINPUT_KEYSTROKE stroke;

};
#endif // !___RESULT_BG_H___
