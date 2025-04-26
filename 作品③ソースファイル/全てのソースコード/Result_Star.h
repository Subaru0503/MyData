#ifndef ___RESULT_STAR_H___
#define ___RESULT_STAR_H___

#include <DirectXMath.h>
#include "Defines.h"
#include "Sprite.h"
#include "Texture.h"

class ResultStar
{
public:
	typedef struct
	{
		DirectX::XMFLOAT3 pos;										// 中心座標
		DirectX::XMFLOAT2 size;										// 横縦サイズ
		//DirectX::XMFLOAT2 posTexCoord;								// テクスチャ座標（左上）
		//DirectX::XMFLOAT2 sizeTexCoord;
		float radian;
	}ST_RESULT_STAR_PARAM;
public:
	ResultStar(float PosX, float PosY, float PosZ, float radian);
	~ResultStar();
	void Update();
	void Draw();

private:
	ST_RESULT_STAR_PARAM star;
	float m_Left, m_Right, m_Bottom, m_Top, m_near, m_far;
	float m_basePosX, m_basePosY;
	Texture* m_pTexture;

};




#endif // !___RESULT_STAR_H___

