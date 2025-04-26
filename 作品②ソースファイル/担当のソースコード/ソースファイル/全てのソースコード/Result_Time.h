#ifndef ___RESULT_TIME_H___
#define ___RESULT_TIME_H___

#include <DirectXMath.h>
#include "Defines.h"
#include "Sprite.h"
#include "Texture.h"

#define DIGIT_TIME (4)
#define ANIM_TIME_SPLIT_X	(4)		//画像分割数（横）
#define ANIM_TIME_SPLIT_Y	(3)		//画像分割数

class ResultTime
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
	}ST_RESULT_TIME_PARAM;

public:
	ResultTime(float PosX, float PosY, float PosZ, float radian);
	~ResultTime();
	void Update(int time);
	void Draw();
	void DrawTimeUp();

private:
	ST_RESULT_TIME_PARAM time[DIGIT_TIME];
	int m_ntemp;//制限時間退避用
	int m_nTimeMinutes;
	int m_nTimeSeconds;
	float m_Left, m_Right, m_Bottom, m_Top, m_near, m_far;
	float m_basePosX, m_basePosY;
	Texture* m_pTexture[2];
};


#endif // !___RESULT_TIME_H___

