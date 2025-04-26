// Object.h
#ifndef __OBJECT_H__
#define __OBJECT_H__

//=====インクルード=====
#include <DirectXMath.h>
#include "Shader.h"
#include "MeshBuffer.h"
#include "Model.h"
#include "ModelManager.h"
#include "SoundManager.h"
#include "DustCloud.h"
#include "TrailEffect.h"
#include "Defines.h"
#include "Sprite.h"
#include "Texture.h"
/******************************
*@brief	オブジェクト基底クラス
******************************/
class Object
{
public:
	// オブジェクトの種類
	enum Kind
	{
		NONE,
		TREE,			// 木
		ROCK,			// 岩
		HOUSE,			// 家
		BURNINGOBJECT,	//燃えてるオブジェクト
		FENCE,			// フェンス
		SIGNBOARD,		// 看板
		TUTORIALSIGNBOARD,	// チュートリアル看板
		MUSHROOM,		// キノコ
		MUSHROOMCAT,	// ねこきのこ
		RUBBISH,		// ゴミ
		STONE,			// 小石
		WOOD,			// 木材
		METAL,			// 鋼材
		// STAGE 3
		DONUTS,			// ドーナツ 
		CAKEPIECE,		// ８等分ケーキ
		STRAWBERRY,		// いちご
		APOLO,			// アポロ
		COOKIE,			// クッキー
		CHOCOLATETREE,	// チョコの木
		CANDYROCK,		// キャンディー岩
		CHOCOLATEFENCE,	// チョコプレート（フェンス）
		CHOCOLATEPIECE,	// チョコのかけら
		CANDYPIECE,		// キャンディーのかけら
		CANDLE,			// ろうそく
		SWEETSHOUSE,	// お菓子の家
		// ギミック
		BLUE_MUSHROOM,			// 青キノコ
		BLUE_MUSHROOM_NEMOTO,	// 青キノコの根本
		BISCUIT,				// ビスケット
		BISCUITPIECE,			// ビスケットのかけら
	};
private:
	// 線分を描画する際の頂点情報構造体
	struct LineVertex
	{
		float pos[3];
		float color[4];
	};
	// ポリゴンを描画する際の頂点情報構造体
	struct Vertex
	{
		float pos[3];
		float uv[2];
	};
public:
	// 描画初期位置、スケール、アングルを引数に持つコンストラクタ
	Object(float posX, float posY, float posZ);
	virtual ~Object();					// デストラクタ

	void Init();				// 初期化処理
	void Uninit();				// 終了処理
	virtual void Update(float tick);	// 更新処理

	void SetWorld(DirectX::XMFLOAT4X4 world);		// 定数バッファへ送るデータにワールド座標変換行列をセット
	void SetView(DirectX::XMFLOAT4X4 view);			// 定数バッファへ送るデータにビュー座標変換行列をセット
	void SetProjection(DirectX::XMFLOAT4X4 proj);	// 定数バッファへ送るデータにプロジェクション座標変換行列をセット
	void SetBoxMove(float x = 0.0f, float y = 0.0f, float z = 0.0f);		// Box移動処理
	void SetSphereMove(float x = 0.0f, float y = 0.0f, float z = 0.0f);		// Sphere移動処理

	void AddLine(DirectX::XMFLOAT3 start, DirectX::XMFLOAT3 end,
		DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));	// 描画する線分を追加する処理
	void DrawLines();	// 線分を描画する処理

	void DrawBox(DirectX::XMFLOAT4X4*);			// Box描画処理
	void DrawCylinder(DirectX::XMFLOAT4X4*);	// Cylinder描画処理
	void DrawSphere(DirectX::XMFLOAT4X4*);		// Sphere描画処理

	int GetKind();					// オブジェクトの種類番号を返す
	DirectX::XMFLOAT3 GetScale();	// スケールを返す
	bool GetDelete();				// 削除フラグを返す
	void SetDelete();				// 削除フラグを立てる
	int GetMoney();					// 吸い込んだお金の価値を返す
	bool IsDrop();					// ドロップアニメーション中か返す
	DirectX::XMFLOAT3 GetAngle();	// 回転角度

	void SetDropFlg(bool isDrop);	// ドロップ中フラグをセット
	void SetSound(CSoundMng* sound);

private:
	void MakeVS();			// 頂点シェーダ作成
	void MakePS();			// ピクセルシェーダ作成
	void MakeLineShader();	// 線分用シェーダ作成

private:
	void MakeLine();		// 線分の頂点バッファ作成 
	void MakeBox();			// Boxの頂点バッファ作成
	void MakeCylinder();	// Cylinderの頂点バッファ作成
	void MakeSphere();		// Sphereの頂点バッファ作成
	const int MAX_LINE_NUM = 1000;	// shiran
	const int CIRCLE_DETAIL = 16;	// shiran

private:
	MeshBuffer* m_pBox;			// Boxの頂点バッファへのポインタ
	MeshBuffer* m_pCylinder;	// Cylinderの頂点バッファへのポインタ
	MeshBuffer* m_pSphere;		// Sphereの頂点バッファへのポインタ
	MeshBuffer* m_pLines;		// 線分の頂点バッファへのポインタ
	Shader* m_pVS;				// 頂点シェーダのポインタ
	Shader* m_pPS;				// ピクセルシェーダのポインタ
	Shader* m_pLineShader[2];		// 線分用シェーダのポインタ
	DirectX::XMFLOAT4X4 m_WVP[3];	// 定数バッファへ書き込むデータのポインタ
	void* m_pLineVtx;				// shiran
	int m_lineCnt;					// shiran

public:
	DirectX::XMFLOAT3 GetPos();				// オブジェクトの座標を返す
	DirectX::XMFLOAT3 GetOldPos();			// 1フレーム前の座標を返す
	DirectX::XMFLOAT3 GetDownVector();		// 下方向へのベクトルを返す
	void SetPos(DirectX::XMFLOAT3);			// 座標をセット
	void SetAngle(DirectX::XMFLOAT3 angle);	// 回転をセット
	void SetScale(DirectX::XMFLOAT3 scale);	// サイズをセット
	void SetMat(DirectX::XMFLOAT4X4*);		// 定数バッファポインタ指定用
	void SetVelocity(float);				// 移動速度をセット
	void SetDirection(DirectX::XMVECTOR);	// 移動方向ベクトルをセット
	bool IsSuction();						// 吸い込まれ中フラグを返す
	void SetSuctionFlg(bool);				// 吸い込まれ中フラグセット
	int GetCreateNum();						// 破壊された時に生成するオブジェクトの個数
	void SetPosX(float posx);				// X座標セット
	void SetPosY(float posy);				// Y座標セット
	void SetPosZ(float posz);				// Z座標セット
	void SetPlayerPosY(float posY);			// プレイヤーY座標セット
	float GetMass();						// 質量を返す
	void SetModelManager(ModelManager* modelManager);	// モデルマネージャーをメンバにセット
	void SetModelData();								// オブジェクトの種類に応じてモデルデータを取得 
	void SetRandHeight(int crntHeight);		// 今いる地面の高さ設定
	void SetRandSlope(bool slope);			// 坂の上にいるかフラグをセット

	bool GetGimmick();						// ギミックかどうかの受け渡し
	bool GetPlayGimmick();					// ギミック実行状態受け渡し
	void SetPlayGimmick(bool play);			// ギミック再生のセット
	bool GetSuctionGimmick();				// ギミック吸い込まれ状態受け渡し
	void SetSuctionGimmick(bool suction);	// ギミック吸い込まれ状態セット
	float GetAmplitude();					// ギミックスピード計算用サイン振れ幅受け渡し
	void SetAmplitude(float amplitude);
	float GetTime();						// ギミックタイム受け渡し
	void SetTime(float time);
	float GetWeight();						// ギミックスピード調整数値受け渡し
	void SetWeight(float weight);
	float GetRadius();						// ギミック伸びる範囲受け渡し
	void SetRadius(float radius);
	float GetSuctionDis();					// ギミック吸い込み限界座標との比率受け渡し
	void SetSuctionDis(float dis);
	DirectX::XMFLOAT3 GetEndPos();			// ギミック目標座標受け渡し
	void SetEndPos(DirectX::XMFLOAT3 endPos);
	DirectX::XMFLOAT3 GetGimmickOldPos();	// ギミック初期座標受け渡し

	virtual void DrawModel(DirectX::XMFLOAT4X4* mat, VertexShader* vs);	// モデルの描画
	Model* GetModel();						// モデルデータのポインタを返す
	int GetLevel();							// レベルを返す
	bool IsShake();							// 揺れフラグを返す
	void SetShake(bool OnOff);				// 揺れフラグをセット
	bool IsMove();							// 移動フラグ取得
	void SetAngleToPlayer(float angle);		// 角度セット
	float GetAngleToPlayer();				// 角度ゲット
	bool GetDraw();
	void SetDraw(bool draw);
	void SetTime(int time);					// 時間情報セット
	std::string GetModelKey();
	void SetTouch(bool touch);				// player接触中フラグセット
	bool IsGetMoney();
	void SetGetMoney(bool getMoney);
	void SetPlayerPos(DirectX::XMFLOAT3 playerPos);
	int GetTutorialKind();					// 表示チュートリアル画像の種類渡し
	void SetDust(Dust * pDust);

	bool GetEfkDestory();					//破壊エフェクトゲット
	void SetEfkDestory(bool pEDestoy);
	int GetRandHeight();					// 今いる地面の高さを渡す
	bool GetRandSlope();					// 坂の上か
	void DrawIcon(DirectX::XMFLOAT3 pos, int kind, int level,CPlayer* pPlayer);
	int GetDefCnt();						//ビスケット耐久値ゲット
protected:
	DirectX::XMFLOAT4X4* m_mat;
	DirectX::XMFLOAT3 m_pos, m_scale, m_rotate;
	float m_PlayerPosY;					// プレイヤーの座標Y
	DirectX::XMFLOAT3 m_oldPos;
	DirectX::XMFLOAT3 m_oldSize;		// Boxサイズ退避用変数
	DirectX::XMFLOAT3 m_oldScale;		// サイズ退避用変数
	DirectX::XMVECTOR m_moveDirection;	// 移動方向ベクトル
	int m_randHeight;					// 今いる地面の高さ
	bool m_randSlope;					// 坂の上か
	float m_velocity;					// 速度
	float m_lastVel;					// 最後にSuctionでセットされた速度
	float m_gravity;					// 重力
	bool m_bSuction;					// 吸い込まれ中フラグ
	bool m_bGimmickSuction;				// ギミック吸い込まれフラグ
	int m_nKind;						// オブジェクトの種類
	bool m_bDelete;						// 削除フラグ
	int m_nMoney;						// ゲットできるお金
	int m_createNum = 0;				// 破壊された時に生成するオブジェクトの個数
	float m_mass;						// 質量
	bool m_draw;
	bool m_bDrop;						// ドロップ中の無敵タイムフラグ
	bool m_EfkDestory;					// 破壊エフェクトフラグ
	DirectX::XMVECTOR m_dropDirection;
	float dropTime;						// ドロップアニメーションの経過時間
	float dropJump;						// ドロップ時のジャンプ量
	bool m_bDropJump;					// ドロップ時のジャンプフラグ
	bool m_bTutorial;					// チュートリアル会話UI表示フラグ
	bool m_bTutorialTrigger;			// チュートリル開始フラグ
	int m_nTuturoalKind;					// 表示するチュートリアル画像の種類

	Model* m_pModel;				// モデルデータ格納用
	ModelManager* m_pModelManager;	// モデルデータ取得用
	std::string m_modelKey;			// モデルマップのキー

	float m_modelRatio;	// モデルの拡縮率
	int m_nLevel;		// オブジェクトのレベル
	bool m_bShake;		// 揺れフラグ
	bool m_bMove;		// 移動フラグ
	float m_angleToPlayer;	// プレイヤーの正面と、自分とプレイヤーをつないだ線分との間の角度
	int m_noldTime;		// 30秒経ったか計算するための値退避
	int m_nTime;		// 現在の時間
	int m_nLevelDown;	// レベルダウンフラグ
	int m_nDefCnt;		// 耐久回数(ビスケット)
	float m_fOnTime;	// オブジェクトの上にいる経過時間
	bool m_bTouch;		// プレイヤーと接触中か
	bool m_bOldTouch;	// 前回の↑の値の退避用
	bool m_bGetMoney;	// 所持金を増やすかどうかのフラグ
	bool m_bGimmick;	// ギミックオブジェクトかどうか
	bool m_bPlayGimmick;		// ギミック実行フラグ
	bool m_bSuctionGimmick;		// 吸い込まれたか
	float m_amplitude;			// 移動速度振れ幅
	float m_time;				// サイン用タイマー
	float m_weight;				// 移動速度増減用
	float m_radius;				// 移動可能範囲の半径
	float m_suctionDis;			// ギミック吸い込み限界座標との比率
	float m_fallTime;			// 落下時間
	DirectX::XMFLOAT3 m_playerPos;
	DirectX::XMFLOAT3 m_gimmickOldPos;	// ギミック用過去座標
	DirectX::XMFLOAT3 m_endPos;	// 移動先座標

	DirectX::XMFLOAT3 m_shakePos;	// 揺れアクション時の座標情報
	Dust* m_pDust;
	CSoundMng* m_pSoundMng;
	TrailEffect* m_pTrail;	// 軌跡エフェクト
	bool m_bTrailSet;			// 
	Texture* m_pTexture;
	int m_nMaxRatio;
	float m_fRatio;
};

#endif // __OBJECT_H__
