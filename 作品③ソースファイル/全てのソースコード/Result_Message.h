#ifndef ___RESULT_MESSAGE_H___
#define ___RESULT_MESSAGE_H___

#include <DirectXMath.h>
#include "Defines.h"
#include "Sprite.h"
#include "Texture.h"

class ResultMsg
{
public:
	ResultMsg(float PosX, float PosY, float PosZ, float radian);
	~ResultMsg();
	void Update();
	void DrawEval3();
	void DrawEval2();
	void DrawEval1();
	void DrawEval0();
	
private:
	
	float m_Left, m_Right, m_Bottom, m_Top, m_near, m_far;
	float m_basePosX, m_basePosY;
	float m_fradian;
	DirectX::XMFLOAT2 m_fsize;
	Texture* m_pTexture[4];
};


#endif // !___RESULT_MESSAGE_H___

