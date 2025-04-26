#ifndef ___TIMER_H___
#define ___TIMER_H___

#include <DirectXMath.h>
#include "Value.h"
#include "Sprite.h"
#include "Texture.h"

#define DIGIT_TIME			(4)	//エフェクトの数（配列の数）
#define ANIM_TIME_FRAME	(2)		//アニメーション一コマフレーム数
#define ANIM_TIME_SPLIT_X	(4)		//画像分割数（横）
#define ANIM_TIME_SPLIT_Y	(4)		//画像分割数（縦）

class CTimer
{
public:
	typedef struct
	{

		DirectX::XMFLOAT3 pos;			//中心座標
		DirectX::XMFLOAT2 size;			//横縦サイズ
		DirectX::XMFLOAT2 posTexCoord;	//テクスチャ座標（左上）
		DirectX::XMFLOAT2 sizeTexCoord;	//テクスチャサイズ（右下）
		//Float4	color;			//カラー
		//float	angle;			//回転角度
		//bool	use;			//使用中フラグ
		int		frame;			//アニメーション管理フレーム
		int		currentAnimNo;	//アニメーションコマ番号（左上から０～）
	}ST_TIME_PARAM;		//爆発を管理するパラメータの構造体

public:
	CTimer(int TimeLimit);
	~CTimer();
	void Update();
	void Draw();
	int GetTime();
	void SetItem(int item);		// アイテムが使用されたか
	int GetMaxTime();

private:
	//----アイテム使用確認用----
	int m_nTimer;				// 時間延長アイテムフラグ

	ST_TIME_PARAM m_time[DIGIT_TIME];//タイマー（数字）
	ST_TIME_PARAM m_timer;
	unsigned int m_TextureTime;
	int m_nTime;
	int m_nTimeLimit;
	float m_ftemp;//制限時間退避用
	int m_nTimeMinutes;
	int m_nTimeSeconds;
	float m_Left, m_Right, m_Bottom, m_Top, m_near, m_far;
	float m_basePosX[2], m_basePosY[2];
	float m_fRadian;
	bool m_bResult;
	Texture* m_pTexture[2];
	int m_nMaxTime;

};





#endif // !___TIMER_H___

