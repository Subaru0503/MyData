// CustomEquipment

//----インクルードガード----
#ifndef ___CUSTOM_EQUIPMENT_H___
#define ___CUSTOM_EQUIPMENT_H___

//----インクルード部----
#include <DirectXMath.h>
#include "Value.h"
#include "Sprite.h"
#include "Texture.h"

//----定数・マクロ定義----
#define ANIM_CUSTOM_EQUIPMENT_SPLIT_X	(3)		//画像分割数（横）
#define ANIM_CUSTOM_EQUIPMENT_SPLIT_Y	(6)		//画像分割数（縦）

//----定数・マクロ定義----
class CCustomEquipment
{

public:
	typedef struct
	{
		DirectX::XMFLOAT3 pos;			//中心座標
		DirectX::XMFLOAT2 size;			//横縦サイズ
		DirectX::XMFLOAT2 posTexCoord;	//テクスチャ座標（左上）
		DirectX::XMFLOAT2 sizeTexCoord;	//テクスチャサイズ（右下）
		int		frame;			//アニメーション管理フレーム
		int		currentAnimNo;	//アニメーションコマ番号（左上から０～）
	}ST_CUSTOM_EQUIPMENT_PARAM;		//パラメータの構造体

public:
	CCustomEquipment();
	~CCustomEquipment();
	void Update();
	void Draw();

	void SetCustom(int* Custom);
private:
	ST_CUSTOM_EQUIPMENT_PARAM m_Custom[MAX_CUSTOM];
	int m_nCustom[MAX_CUSTOM];
	float m_Left, m_Right, m_Bottom, m_Top, m_near, m_far;
	float m_basePosX, m_basePosY;
	Texture* m_pTexture;

	DirectX::XMFLOAT3 m_pos[4];

};


#endif // !___CustomEquipment_H___