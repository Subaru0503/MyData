#ifndef ___RESULT_PERCENT_H___
#define ___RESULT_PERCENT_H___

#include <DirectXMath.h>
#include "Defines.h"
#include "Sprite.h"
#include "Texture.h"

#define DIGIT_NUMBER (4)
#define ANIM_NUMBER_SPLIT_X	(4)		//画像分割数（横）
#define ANIM_NUMBER_SPLIT_Y	(3)		//画像分割数

class ResultPer
{
public:
	typedef struct
	{
		DirectX::XMFLOAT3 pos;			//中心座標
		DirectX::XMFLOAT2 size;			//横縦サイズ
		DirectX::XMFLOAT2 posTexCoord;	//テクスチャ座標（左上）
		DirectX::XMFLOAT2 sizeTexCoord;	//テクスチャサイズ（右下）
		int		currentAnimNo;	//アニメーションコマ番号（左上から０～）
		float radian;
	}ST_RESULT_PERCENT_PARAM;

public:
	ResultPer(float PosX, float PosY, float PosZ, float radian, int Per);
	~ResultPer();
	void Update(int per);
	void Draw();

private:
	ST_RESULT_PERCENT_PARAM per[DIGIT_NUMBER];
	float m_Left, m_Right, m_Bottom, m_Top, m_near, m_far;
	Texture* m_pTexture;
	int m_nper;
	int m_ntemp;
};



#endif // !___RESULT_PERCENT_H___

