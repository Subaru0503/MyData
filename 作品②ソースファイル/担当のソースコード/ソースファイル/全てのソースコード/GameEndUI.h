#ifndef ___GAME_END_UI_H___
#define ___GAME_END_UI_H___
#include <DirectXMath.h>
#include "Defines.h"
#include "Sprite.h"
#include "Texture.h"

#define RATIO (0.025f)

class GameEndUI
{
public:
	GameEndUI(float PosX, float PosY, float PosZ);
	~GameEndUI();
	void Update(float SizeX, float SizeY);
	void DrawTimeUp();
	void DrawClear();

private:
	enum kind {
		TimeUp,
		Clear,
	};

private:
	float m_Left, m_Right, m_Bottom, m_Top, m_near, m_far;
	float m_fsizeTimeUpX, m_fsizeTimeUpY;
	float m_fsizeClearX, m_fsizeClearY;
	Texture* m_pTexture[2];
	DirectX::XMFLOAT2 m_textureSize[2];
	float m_basePosX , m_basePosY;
	int m_nMAXRatio;
	float m_fRatio;
	bool m_bRatio;
	int m_nCnt;

};




#endif // !___GAME_END_UI_H___

