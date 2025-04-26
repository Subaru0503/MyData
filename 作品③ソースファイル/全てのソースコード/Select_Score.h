#ifndef ___SELECT_SCORE_H___
#define ___SELECT_SCORE_H___

#include <DirectXMath.h>
#include "Defines.h"
#include "Sprite.h"
#include "Texture.h"

#define ANIM_TIME_SPLIT_X	(4)		//画像分割数（横）
#define ANIM_TIME_SPLIT_Y	(3)		//画像分割数

class SelectScore
{
public:
	typedef struct
	{
		DirectX::XMFLOAT3 pos;			//中心座標
		DirectX::XMFLOAT2 size;			//横縦サイズ
		DirectX::XMFLOAT2 posTexCoord;	//テクスチャ座標（左上）
		DirectX::XMFLOAT2 sizeTexCoord;	//テクスチャサイズ（右下）
		int		currentAnimNo;	//アニメーションコマ番号（左上から０～）
	}ST_SELECT_TIME_PARAM;

	typedef struct
	{
		DirectX::XMFLOAT3 pos;			//中心座標
		DirectX::XMFLOAT2 size;			//横縦サイズ
		DirectX::XMFLOAT2 posTexCoord;	//テクスチャ座標（左上）
		DirectX::XMFLOAT2 sizeTexCoord;	//テクスチャサイズ（右下）
		int		currentAnimNo;	//アニメーションコマ番号（左上から０～）
		float radian;
	}ST_SELECT_PERCENT_PARAM;
public:
	SelectScore();
	~SelectScore();
	void Update(int* score, int* time, int select);
	void Draw();

private:
	float m_Left, m_Right, m_Bottom, m_Top, m_near, m_far;
	Texture* m_pTexture[4];
	DirectX::XMFLOAT3 m_starPos[3];
	DirectX::XMFLOAT2 m_starSize[3];
	DirectX::XMFLOAT2 m_hyphenPos;
	DirectX::XMFLOAT2 m_hyphenSize;
	ST_SELECT_TIME_PARAM m_time[4];
	ST_SELECT_PERCENT_PARAM m_per[3];
	int m_nTimeMinutes;
	int m_nTimeSeconds;
	int m_cleartime;
	int m_starNum;
	int m_nper;
};




#endif // !___SELECT_SCORE_H___

