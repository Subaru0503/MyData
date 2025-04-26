#ifndef ___UI_H___
#define ___UI_H___

#include <DirectXMath.h>
#include "Defines.h"
#include "Sprite.h"
#include "Texture.h"

#define MAX_UI (5)
#define DIGIT_SCORE			(6)	//エフェクトの数（配列の数）
#define ANIM_SCORE_FRAME	(2)		//アニメーション一コマフレーム数
#define ANIM_SCORE_SPLIT_X	(4)		//画像分割数（横）
#define ANIM_SCORE_SPLIT_Y	(4)		//画像分割数（縦）

class CUI
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
	}ST_SCORE_PARAM;		//パラメータの構造体

	typedef struct
	{

		DirectX::XMFLOAT3 pos;			//中心座標
		DirectX::XMFLOAT2 size;			//横縦サイズ
		DirectX::XMFLOAT2 posTexCoord;	//テクスチャ座標（左上）
		DirectX::XMFLOAT2 sizeTexCoord;	//テクスチャサイズ（右下）
		int		currentAnimNo;	//アニメーションコマ番号（左上から０～）
	}ST_ADDMANEY_PARAM;		//パラメータの構造体

public:
	CUI();
	~CUI();
	void Update();
	void Draw();
	void DrawResult(int resultMoney);
	void AddMoney(int num);
	void UpdateScoretexCoord();
	int  GetMoney();
	void DrawAdd();
	void SetAdd(bool Add);
	bool GetAdd();

	CUI(int money);

private:
	ST_SCORE_PARAM m_score[DIGIT_SCORE + 1];
	ST_ADDMANEY_PARAM m_add[DIGIT_SCORE + 1];
	unsigned int m_TextureScore;
	int m_nScore;
	int m_nAddMoney;
	float m_Left, m_Right, m_Bottom, m_Top, m_near, m_far;
	float m_basePosX, m_basePosY;
	bool m_bAdd;//表示フラグ
	float m_fAlpha;
	Texture* m_pTexture[MAX_UI];

	
	int m_temp;
	int m_temp2;


};


#endif // !___UI_H___