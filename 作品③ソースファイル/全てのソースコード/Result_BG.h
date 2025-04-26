
#ifndef ___RESULT_BG_H___
#define ___RESULT_BG_H___

#include <DirectXMath.h>
#include "Defines.h"
#include "Sprite.h"
#include "Texture.h"

class ResultBG
{
public:
	ResultBG();
	~ResultBG();
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
	Texture* m_pTexture;
	int m_animeNo;
	int m_frame;
	int m_totalFrame;
	DirectX::XMFLOAT2 m_uvPos;
	DirectX::XMFLOAT2 m_uvSize;
	bool m_bEndAnime;


};







#endif // !___RESULT_BG_H___
