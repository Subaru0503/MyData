#ifndef ___RESULT_STAMP_H___
#define ___RESULT_STAMP_H___

#include <DirectXMath.h>
#include "Defines.h"
#include "Sprite.h"
#include "Texture.h"

class ResultStamp
{
public:
	ResultStamp(float PosX, float PosY, float PosZ, float radian);
	~ResultStamp();
	void Update();
	void DrawEval3();
	void DrawEval2();
	void DrawEval1();

private:

	float m_Left, m_Right, m_Bottom, m_Top, m_near, m_far;
	float m_basePosX, m_basePosY;
	float m_fradian;
	DirectX::XMFLOAT2 m_fsize;
	Texture* m_pTexture;
	float m_fAlpha;
	float m_fRatio;
};


#endif // !___RESULT_MESSAGE_H___


