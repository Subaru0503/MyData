//Player.h
#ifndef __PLAYER_H__
#define __PLAYER_H__

//=====インクルード部=====
#include <DirectXMath.h>
#include "ObjectManager.h"
#include "Model.h"
#include "Shader.h"
#include "Suction.h"		// 吸い込み機能クラス
#include "Value.h"
#include "Shop.h"
#include "UI.h"
#include "SoundManager.h"
#include "Effect.h"
#include "RunSmoke.h"
#include "ESuction.h"
#include "EStun.h"
#include "XController.h"
#include "Drill.h"
#include "Saw.h"
#include "Hammer.h"
//=====クラス=====
class CPlayer
{
public:
	CPlayer();
	~CPlayer();

	enum Direct
	{
		DIRECT_UP = 0,
		DIRECT_DOWN,
		DIRECT_LEFT,
		DIRECT_RIGHT,
		DIRECT_UPR,
		DIRECT_UPL,
		DIRECT_DOWNR,
		DIRECT_DOWNL,
	};

	void Update(float tick);														//更新処理
	void Draw();
	void MoveModel(float deltaX, float deltaZ);							//モデル移動

	DirectX::XMFLOAT3	GetPos();										//座標受け渡し
	DirectX::XMFLOAT3	GetMove();										//移動量受け渡し
	DirectX::XMFLOAT3	GetCameraPos();
	DirectX::XMFLOAT3	GetOldPos();									//過去座標受け渡し
	DirectX::XMFLOAT3	GetScale();										//サイズ受け渡し
	DirectX::XMFLOAT4X4 GetWorldMatrix();								//ワールド行列受け渡し
	DirectX::XMFLOAT4X4 GetViewMatrix();								//ビュー行列受け渡し
	DirectX::XMFLOAT4X4 GetProjectionMatrix();							//プロジェクション行列受け渡し
	DirectX::XMFLOAT4X4 GetNViewMatrix();								//転置なしビュー行列受け渡し
	DirectX::XMFLOAT4X4 GetNProjectionMatrix();							//転置なしプロジェクション行列受け渡し
	DirectX::XMFLOAT3 GetForwardVector();								//前方向ベクトル取得
	DirectX::XMFLOAT3 GetRightVector();									//横方向ベクトル取得
	DirectX::XMFLOAT3 GetUpRightVector();
	DirectX::XMFLOAT3 GetUpLeftVector();
	int GetRandKind();													// 今いる地面の種類を渡す
	int GetRandHeight();												// 今いる地面の高さを渡す
	bool GetRandSlope();												// 坂の上か
	bool GetRandBiscuit();												// ビスケットの上にいるか
	bool GetShop();														// 購入画面に移るフラグのゲット	// 変更点
	int* GetMoney();													// 所持金ゲット関数
	int* GetCustom();													// 所持カスタマイズパーツゲット関数
	float GetRadius();
	Suction* GetSuction();												// 吸い込みクラスゲット
	float GetRad();														// プレイヤーのラジアン角ゲット
	bool GetTrade();
	bool GetTutorial();													// チュートリアル画面表示フラグ

	void SetObjectMng(CObjectMng* pCObjectMng);							// オブジェクトMngのポインタを設定
	void SetPos(DirectX::XMFLOAT3 pos);									// プレイヤー座標を設定
	void SetMoney(int money);
	void SetPosX(float posx);
	void SetPosY(float posy);
	void SetPosZ(float posz);
	void SetCameraPosX(float camPosX);
	void SetCameraPosY(float camPosY);
	void SetCameraPosZ(float camPosZ);
	void SetCamRadius(float radius);
	void SetHorizon(float horizon);
	void SetTrade(bool trade);
	void SetShop(bool Shop);											// 購入画面フラグ操作 // 変更点
	void SetRandKind(int crntGround);									// 今いる地面の種類設定
	void SetRandHeight(int crntHeight);									// 今いる地面の高さ設定
	void SetRandSlope(bool slope);										// 坂の上にいるかフラグをセット
	void SetRandBiscuit(bool is);										// ビスケットの上にいるかフラグをセット
	void SetSoundMng(CSoundMng* soundMng);								// サウンド実体受け取り
	void SetItem(int drink, int nozzle);								// アイテムが使用されたか
	void SetUI(CUI* ui);	// 所持金データ取得
	void SetTutorial(bool, int);										// チュートリアル看板範囲内フラグ
	void SetSuction(bool suction);
	void SetTutorialDraw(bool);	// チュートリアル表示フラグ
	int GetTutorialNum();
	bool IsTutorial();
	void StopSound();//吸い込みse停止
	void LoadEffect();
	void SetDrill(bool* m_bDrill);										//カスタムパーツ
	void SetSaw(bool* m_bSaw);											//カスタムパーツ
	void SetHammer(bool* m_bHammer);									//カスタムパーツ
	void SetShopCustom(CShop* shop);									//カスタムパーツ
private:
	void Footsteps(XINPUT_STATE state);													// 地面の種類で足音分別
	DirectX::XMFLOAT3 m_pos, m_oldPos, m_scale, m_camPos, m_look, m_up;	// プレイヤー座標、プレイヤー過去座標、大きさ、カメラ座標、焦点、カメラ上方向
	DirectX::XMFLOAT3 m_move;											// 移動速度
	float m_fovy, m_aspect, m_near, m_far;								// 視野角、画面比率、近距離投影限界、遠距離限界
	float m_radius, m_horizon, m_vertical;								// プレイヤーまでの距離半径、カメラ平行移動ラジアン角、縦移動
	float m_angleHorizon, m_angleVertical;								// カメラ平行移動角度、縦移動角度
	float m_directRad, m_directAngle;									// プレイヤーラジアン角、角度(°)
	int m_direct;
	int m_nCustom[MAX_CUSTOM];											// カスタマイズパーツ装備
	int m_nMoney;														// 所持金
	char str[256];														// ウィンドウ文字列
	int  m_nTime;														// 経過時間
	float m_fTimeLimit;													// 制限時間
	bool m_trade;
	float m_gravity;
	bool m_bShop;														// 購入画面に移るフラグ
	int m_nCandleDemerit;												// ろうそくのデメリットフラグ
	int m_nDemelitFrame;												// デメリットの時間
	int m_randKind;														// 今いる地面の種類(草、砂、etc)
	int m_randHeight;													// 今いる地面の高さ
	bool m_randSlope;													// 坂の上か
	bool m_randBiscuit;													// ビスケットの上か
	bool m_tutorial, m_tutorialDraw;									// チュートリアル画面表示フラグ
	bool m_suction;
	bool* m_bDrill;														//カスタムパーツ
	bool* m_bSaw;														//カスタムパーツ
	bool* m_bHammer;
	CTutorialSignboard::textureKind m_tutorialKind;						// チュートリアル看板の種類
	Model::AnimeNo anime[5];
	DirectX::XMFLOAT3 m_oldPlayerForward;	// プレイヤー方向退避用

	CObjectMng* m_pObjectMng;
	Model* m_pModel;
	VertexShader* m_pVS;
	Suction* m_pSuction;					// 吸い込み機能クラスポインタ
	CUI* m_pUI_Money;						// UI(所持金)
	CSoundMng* m_pSoundMng;					// サウンド操作用

	Effect* m_pEffect;
	RunSmoke* m_pRunSmoke;
	ESuction* m_pESuction;
	EStun* m_pEStun;
	CDrill* m_pDrill;						//カスタムパーツ
	CSaw* m_pSaw;							//カスタムパーツ
	CHammer* m_pHammer;						//カスタムパーツ
	CShop* m_pshop;
	bool IsMove;//土煙エフェクト
	bool Pmove;
	bool Pvaccum;
	XINPUT_STATE state;
	XINPUT_KEYSTROKE stroke;
	//----アイテム使用確認用----
	int m_nDrink;							// ドリンクフラグ
	int m_nNozzle;							// ノズル強化フラグ

	Texture* m_pShadowTex;
};

#endif