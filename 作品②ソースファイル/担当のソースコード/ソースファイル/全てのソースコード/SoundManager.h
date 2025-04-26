//=================================================================
//
//	SoundManager.h
//	サウンドを一元管理する
//
//=================================================================

#ifndef __SOUND_MANAGER_H__
#define __SOUND_MANAGER_H__

// ========== インクルード部 ==========
#include "Sound.h"
#include <stdio.h>
#include <iostream>
#include <map>
#include <list>
using namespace std;

// ========== クラス ==========
class CSoundMng
{
public:	// 列挙型 外部呼出し用
	// =-=-= BGM =-=-=
	enum BGM {
		title,
		game,
		game2,
		game3,
		Select,
		Op,
		Ed
	};

	// =-=-= SE =-=-=
	// ----- システム音 -----
	enum SystemSE {
		decision,		// 決定
		cancel,			// キャンセル
		select,			// 選択
		Tstrat,			//ゲーム開始(タイトル)
		swap,			//ステージチェンジ
		Fpon,			//リザルトSE
	};

	// ----- プレイヤー -----
	enum PlayerSE {
		walkGrass,		// 草：歩く
		ranGrass,		// 草：走る
		walkGround,		// 土：歩く
		ranGround,		// 土：走る
		walkCream,		//クリーム:歩く
		runCream,		//クリーム:走る
		walkSponge,		//スポンジ:歩く
		runSponge,		//スポンジ:走る

	};

	// ----- リザルト -----
	enum ResultSE {
		gameOver,		// ゲームオーバー
		gameClear,		// ゲームクリア
		stamp,			// ハンコ
		star,			// 星
	};

	// ----- 吸い込み -----
	enum SuctionSE {
		wind,			// 吸い込み中
		wind2,			// 吸い込み中(中)
		wind3,			// 吸い込み中(強)
		suctionHigh,	// 吸い込み完了(ポンッ)：高い音
		suctionLow,		// 吸い込み完了(ポンッ)：低い音
		money,			// お金チャリン
	};

	// ----- 時間 -----
	enum TimeSE {
		countDown1,		// ぽ・ぽ・ぱーー(2カウント)
		countDown1_pi,	// ぱーー
		countDown2,		// ぽ・ぽ・ぽ・ぱーー(３カウント)
		timeUp1,		// 時計じりりり
		timeUp2,		// ベル
		watchSlow,		// 秒針：ゆっくり
		watchEaly,		// 秒針：速い
	};

	// ----- 破壊 -----
	enum DestroySE
	{
		wood,			// 木破壊中
		woodBreak,		// 木破壊完了
		rock,			// 岩破壊中
		rockBreak,		// 岩破壊完了
		woodHouse,		// 木の家破壊中
		woodHouseBreak,	// 木の家破壊完了
		rocklHouse,		// 石の家破壊中
		rocklHouseBreak,// 石の家破壊完了
	};

	// ----- 買い物 -----
	enum ShopSE
	{
		buy,			// 購入完了(レジ音)
		text,			// テキストのプルプル音
	};

	//------ギミック------
	enum GimmickSE
	{
		cookie,			//クッキー
		cookieBreak,	//クッキー破壊
		fire,			//消火
		aokinoko		//アオキノコ
	};

public:	// 関数
	CSoundMng();
	~CSoundMng();
	void DeleteSpeaker();							// 再生終了したSEスピーカーを削除
	void AllDeleteSpeaker();						// 再生中のスピーカーを全削除

	// =-=-= 再生 =-=-=
	// ----- BGM -----
	void playSound(BGM kind);						// BGM

	// ----- SE -----
	void playSound(SystemSE kind);					// システム音
	void playSound(PlayerSE kind);					// プレイヤー
	void playSound(ResultSE kind);					// リザルト
	void playSound(SuctionSE kind);					// 吸い込み
	void playSound(TimeSE kind);					// 時間
	void playSound(DestroySE kind);					// 破壊
	void playSound(ShopSE kind);					// 買い物
	void playSound(GimmickSE kind);					// ギミック

	// =-=-= 再生終了チェック =-=-=
	// ----- BGM -----
	bool CheckSoundEnd(BGM kind);

	// ----- SE -----
	bool CheckSoundEnd(SystemSE kind);				// システム指定のSEが再生終了したかチェック
	bool CheckSoundEnd(PlayerSE kind);				// プレイヤー
	//bool CheckSoundEnd(ResultSE kind);			// リザルト
	bool CheckSoundEnd(SuctionSE kind);				// 吸い込み
	bool CheckSoundEnd(TimeSE kind);				// 時間
	//bool CheckSoundEnd(DestroySE kind);			// 破壊
	bool CheckSoundEnd(ShopSE kind);				// 買い物
	bool CheckSoundEnd(GimmickSE kind);				// ギミック

	// =-=-= 再生停止 =-=-=
	// ----- BGM -----
	void StopSound(BGM kind);						// BGM

	// ----- SE -----
	void StopSound(SystemSE kind);				// システム音SE再生停止
	void StopSound(PlayerSE kind);					// プレイヤー
	//void StopSound(ResultSE kind);				// リザルト
	void StopSound(SuctionSE kind);					// 吸い込み
	//void StopSound(TimeSE kind);					// 時間
	//void StopSound(DestroySE kind);				// 破壊
	void StopSound(ShopSE kind);					// 買い物
	//void StopSound(GimmickSE kind);				// ギミック


private: // 列挙型　内部処理用
	enum SpeakerKind
	{
		bTitle,			// タイトルBGM
		bGame,			// ゲームBGM
		bGame2,			// ゲーム2BGM
		bGame3,			// ゲーム3BGM
		bSelect,		//ステージセレクト
		bOp,
		bEd,
		sDecision,		// 決定
		sCancel,		// キャンセル
		sSelect,		// 選択
		sTStrat,		//ゲーム開始(タイトル)
		sSwap,			//ステージチェンジ
		sFpon,			//リザルトSE
		sWalkGrass,		// 草：歩く
		sRanGrass,		// 草：走る
		sWalkGround,	// 土：歩く
		sRanGround,		// 土：走る
		sWalkCream,		// クリーム:歩く
		sRunCream,		// クリーム:走る
		sWalkSponge,	// スポンジ:歩く
		sRunSponge,		// スポンジ:走る
		sGameOver,		// ゲームオーバー
		sGameClear,		// ゲームクリア
		sStamp,			// ハンコ
		sStar,			// 星
		sWind,			// 吸い込み中
		sWind2,			// 吸い込み中(中)
		sWind3,			// 吸い込み中(強)
		sSuctionHigh,	// 吸い込み完了(ポンッ)：高い音
		sSuctionLow,	// 吸い込み完了(ポンッ)：低い音
		sMoney,			// お金チャリン
		sCountDown1,	// スタートカウントダウン１
		sCountDown1_pi,	// スタートカウントダウン・スタート
		sCountDown2,	// スタートカウントダウン２
		sTimeUp1,		// タイムアップ
		sTimeUp2,		// ベル
		sWatchSlow,		// 秒針：ゆっくり
		sWatchEaly,		// 秒針：速い
		sWood,			// 木破壊中
		sWoodBreak,		// 木破壊完了
		sRock,			// 岩破壊中
		sRockBreak,		// 岩破壊完了
		sWoodHouse,		// 木の家破壊中
		sWoodHouseBreak,// 木の家破壊完了
		sRocklHouse,	// 石の家破壊中
		sRocklHouseBreak,// 石の家破壊完了
		sBuy,			// 購入完了(レジ音)
		sText,			// テキストのプルプル音
		sCookie,		// クッキー
		sCookieBreak,	// クッキー破壊
		sFire,			// 消火
		sAokinoko,		// アオキノコ
	};

	typedef struct		// スピーカー
	{
		IXAudio2SourceVoice*	m_Speaker;		// スピーカー
		SpeakerKind				m_Kind;				// スピーカーの種類
	}Speaker;

private:

	map<string, XAUDIO2_BUFFER*> m_pSoundMap;		// 音源用map
	list<Speaker*> m_pSpeakerList;					// スピーカー用list
};
#endif // !__SOUND_MANAGER_H__