//=================================================================
//
//	SceneSelect.h
//	ステージ選択シーン
//
//=================================================================
#ifndef __SCENE_SELECT_H__
#define __SCENE_SELECT_H__

// ========== インクルード部 ==========
#include "SceneManager.h"	// シーン遷移処理用
#include "SoundManager.h"	// サウンド再生用
#include "CameraBase.h"
#include "CameraSelect.h"	// セレクトシーンカメラ
#include "ShopMenu.h"
#include "Select.h"
#include "ShopBG.h"
#include "Planet.h"			// 惑星クラス管理用
#include "Select_Score.h"
#include "UI.h"
#include "Model.h"
#include "Shader.h"
#include "Value.h"
#include "Fade.h"

// ========== クラス ==========
class CSceneSelect
{
public:
	CSceneSelect(CSceneMng* pSceneMng, CSoundMng* pSoundMng, Fade* pFade, int OldPlayStage);
	~CSceneSelect();
	void Update(float tick);
	void Draw();
	void DrawSelect(DirectX::XMFLOAT4X4 * mat, VertexShader * vs);	// 宇宙描画
	int* GetItem();			// アイテム使用情報ゲット
	Planet* GetPlanet(int num);

private:
	void StageSawpLeft();
	void StageSawpRight();

private:
	// ----- シーン状態管理 -----
	bool m_bShop;			// ショップフラグ
	bool m_camMove;			// カメラ移動中フラグ
	int  m_select;			// 選択状況
	bool m_openStage;		// ステージ開放中か
	int  m_openFrame;		// ステージ開放UI表示フレーム
	bool m_openUI;			// 「新しい依頼」UI表示中か
	int m_nMoney;			// 所持金仮変数
	bool m_sceneSwap;		// シーン遷移開始したか

	// 他シーンへ引継ぎ用
	int m_nItem[MAX_ITEM];	// アイテム使用格納変数

	// ----- シーンデータ -----
	CSceneMng* m_pSceneMng;
	CSoundMng* m_pSoundMng;
	CCameraSelect* m_pCamera;

	CShopMenu* m_pShopMenu;	// ショップメニュー
	ShopBG* m_pShopBG;
	Planet* m_pPlanets[CSceneMng::SceneKind::MAX_STAGE];	// 惑星まとめ
	Select* m_pSelect;
	SelectScore* m_pScore;
	CUI* m_pMoney;
	VertexShader* m_pVS;	// シェーダー
	Model* m_pSelectModel;	// 背景モデル
	Fade* m_pFade;
};

#endif // !__SCENE_SELECT_H__