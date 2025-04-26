#ifndef ___RESULT_PLAYER_H___
#define ___RESULT_PLAYER_H___

#include <DirectXMath.h>
#include "Defines.h"
#include "Sprite.h"
#include "Texture.h"

class ResultPlayer
{
public:
	ResultPlayer(float PosX, float PosY, float PosZ);
	~ResultPlayer();
	void DrawEval0();
	void DrawEval1();
	void DrawEval2();
	void DrawEval3();

private:
	float m_Left, m_Right, m_Bottom, m_Top, m_near, m_far;
	float m_basePosX, m_basePosY;
	Texture* m_pTexture[4];
};

#endif // !___RESULT_PLAYER_H___
