//----インクルードガード----
#ifndef __OBJECT_MANAGER__
#define __OBJECT_MANAGER__

//----インクルード部----
#include <DirectXMath.h>
#include "Defines.h"
#include "SoundManager.h"
#include "Suction.h"
#include "Model.h"
#include "ModelManager.h"		// モデルマネージャー
// ----- ステージ１ -----
#include "Signboard.h"			// 看板
#include "Tree.h"				// 木
#include "Rubbish.h"			// ゴミ
#include "Wood.h"				// 木材
#include "WoodRoyal.h"			// 木材(レベル4用)
#include "Rock.h"				// 岩
#include "Stone.h"				// 石
#include "StoneRoyal.h"				// 石(レベル４用)
#include "House.h"				// 家
#include "Fence.h"				// 柵
// ----- ステージ２ -----
#include "Mushroom.h"			// きのこ
// ----- ステージ3 -----
#include "ChocolateTree.h"		// チョコの木
#include "CandyRock.h"			// キャンディ岩
#include "SweetsHouse.h"		// お菓子の家
#include "ChocolatePiece.h"		// チョコの破片
#include "ChocolatePieceRoyal.h"		// チョコの破片(レベル４用)
#include "CandyPiece.h"			// キャンディの破片
#include "CandyPieceRoyal.h"			// キャンディの破片(レベル４用)
#include "ChocolateFence.h"		// チョコのフェンス
#include "Candle.h"				// ろうそく
#include "Donuts.h"				// ドーナツ
#include "CakePiece.h"			// ケーキ
#include "Strawberry.h"			// イチゴ
#include "Apolo.h"				// アポロ
#include "Cookie.h"				// クッキー
#include "BiscuitPiece.h"		// ビスケットのかけら
// ----- ギミック -----
#include "BlueMushroom.h"		// 青キノコ
#include "Biscuit.h"			// ビスケット
#include "TutorialSignboard.h"	// チュートリアル看板
// ------エフェクト-----
#include "DustCloud.h"
#include "leaf.h"
#include "Bag.h"
// オブジェクトリスト用
#include <list>
using namespace std;

// 前方宣言
class CPlayer;

//----クラス定義----
class CObjectMng
{
public:
	typedef struct {	// 吸い込みフラグ
		int tree1;
		int tree2;
		int tree3;
		int rock1;
		int rock2;
		int rock3;
		int fence;
		int signBoard;
	}FirstSuction;

public:
	CObjectMng();							// コンストラクタ	
	~CObjectMng();							// デストラクタ

	void Update(float tick);				// 更新
	void Draw(DirectX::XMFLOAT4X4 *mat);	// 描画

	void CreateObject(Object* pObj);		// オブジェクト作成

	list<Object*>* GetObjectList();			// オブジェクトリストのポインタを渡す

	int GetTotalObjNum();					// ステージ開始時の吸い込めるオブジェクトの総数を返す
	//void AddSuctionedObjNum();			// 吸い込んだオブジェクトのカウントを行う
	int GetSuctionedObjNum();				// 現在までに吸い込んだオブジェクトの数を返す
	FirstSuction* GetFirstSuctionFlg();		// 初吸い込みフラグを取得

	void SetTotalObjNum(int totalObjNum);	// 吸い込めるオブジェクトの総数を設定
	void ModelSetting();					// オブジェクトにモデルをセットする
	void SetSuction(Suction* suction);
	void SetSound(CSoundMng* sound);
	void SetTime(int time);					// 時間セット
	void SetPlayer(CPlayer* pPlayer);
	void SetDust(Dust* pDust);
	void SetLeaf(Leaf* pLeaf);
	void SetBag(EBag * pBag);
private:
	list<Object*> m_ObjectList;				// オブジェクトリスト

	int m_totalObjNum;						// ステージ開始時の吸い込めるオブジェクトの総数
	int m_sucionedObjNum;					// 現在までに吸い込んだオブジェクトの数
	FirstSuction m_firstSuccsion;			// 初吸い込みフラグ

	CSoundMng* m_pSoundMng;
	Suction* m_pSuction;
	ModelManager* m_pModelManager;			// モデルマネージャー
	VertexShader* m_pVS;

	Model* m_pModel;
	CPlayer* m_pPlayer;
	//エフェクト
	Dust* m_pDust;
	Leaf* m_pLeaf;
	EBag* m_pEBag;
	int m_nTime;							// 制限時間
};

#endif