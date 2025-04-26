//=================================================================
//
//	SoundManager.cpp
//	SEを一元管理する
//
//=================================================================

// ========== インクルード部 ==========
#include "SoundManager.h"

// ========== 定数・マクロ定義 ==========
// ----- 定数 -----
#define TITLE_BGM_VOL			(0.1f)	// タイトルBGM
#define GAEM_BGM_VOL			(0.5f)	// ゲームBGM
#define GAEM2_BGM_VOL			(0.2f)	// ゲーム2BGM
#define GAEM3_BGM_VOL			(0.2f)	// ゲーム3BGM
#define SELECT_BGM_VOL			(1.0f)	//ステージセレクトBGM
#define DECSION_VOL				(0.2f)	// 決定 
#define CANCEL_VOL				(1.0f)	// キャンセル 
#define SELECT_VOL				(1.0f)	// 選択 
#define TSTRAT_VOL				(1.0f)	//ゲーム開始(タイトル)
#define SWAP_VOL				(0.5f)	//ステージチェンジ
#define OP_BGM_VOL				(1.0f)	//オープニング
#define ED_BGM_VOL				(1.0f)	//エンディング
#define RPON_VOL				(1.0f)	// リザルトSE
#define WALK_GRASS_VOL			(1.0f)	// 草：歩く 
#define RAN_GRASS_VOL			(1.0f)	// 草：走る 
#define WALK_GROUND_VOL			(1.0f)	// 土：歩く 
#define RAN_GROUND_VOL			(1.0f)	// 土：走る 
#define WALK_CREAM_VOL			(1.0f)	// クリーム：歩く 
#define RAN_CREAM_VOL			(0.7f)	// クリーム：走る 
#define WALK_SPONGE_VOL			(1.0f)	// スポンジ：歩く 
#define RAN_SPONGE_VOL			(1.0f)	// スポンジ：走る 
#define GAMEOVER_VOL			(1.0f)	// ゲームオーバー 
#define GAMECLEAR_VOL			(1.0f)	// ゲームクリア 
#define STAMP_VOL				(1.0f)	// ハンコ 
#define STAR_VOL				(1.0f)	// 星 
#define WIND_VOL				(0.8f)	// 吸い込み中 
#define WIND2_VOL				(0.8f)	// 吸い込み中(中)
#define WIND3_VOL				(0.8f)	// 吸い込み中(強)
#define SUCTION_HIGH_VOL		(1.0f)	// 吸い込み完了(ポンッ)：高い音 
#define SUCTION_LOW_VOL			(1.0f)	// 吸い込み完了(ポンッ)：低い音 
#define MONEY_VOL				(1.0f)	// お金チャリン 
#define COUNTDOWN_1_VOL			(1.0f)	// スタートカウントダウン１ 
#define COUNTDOWN_1_PI_VOL		(1.0f)	// スタートカウントダウン１ ぴー
#define COUNTDOWN_2_VOL			(1.0f)	// スタートカウントダウン２ 
#define TIMEUP_1_VOL			(1.0f)	// タイムアップ 
#define TIMEUP_2_VOL			(1.0f)	// ベル 
#define WATCH_SLOW_VOL			(1.0f)	// 秒針：ゆっくり 
#define WATCH_EALY_VOL			(1.0f)	// 秒針：速い 
#define WOOD_VOL				(1.0f)	// 木破壊中 
#define WOOD_BREAK_VOL			(1.0f)	// 木破壊完了 
#define ROCK_VOL				(1.0f)	// 岩破壊中 
#define ROCK_BREAK_VOL			(1.0f)	// 岩破壊完了 
#define WOOD_HOUSE_VOL			(1.0f)	// 木の家破壊中 
#define WOOD_HOUSE_BREAK_VOL	(0.1f)	// 木の家破壊完了 
#define ROCK_HOUSE_VOL			(1.0f)	// 石の家破壊中 
#define ROCK_HOUSE_BREAK_VOL	(0.5f)	// 石の家破壊完了 
#define BUY_VOL					(1.0f)	// 購入完了(レジ音) 
#define TEXT_VOL				(1.0f)	// テキストのプルプル音 
#define COOKIE_VOL				(1.0f)	// クッキー
#define COOKIEBREAK_VOL				(1.0f)	// クッキー破壊
#define FIRE_VOL				(1.0f)	// 消火
#define AOKINOKO_VOL			(1.0f)	// アオキノコ

// ----- マクロ -----
#define STR(var) #var   //引数にした変数を変数名を示す文字列として返すマクロ関数

// ========== コンストラクタ ==========
CSoundMng::CSoundMng()
{
	// =-=-= 各BGM読み込み =-=-=
	m_pSoundMap[STR(CSoundMng::BGM::title)] = LoadSound("Assets/BGM/タイトル.mp3", true);
	m_pSoundMap[STR(CSoundMng::BGM::game)] = LoadSound("Assets/BGM/ステージ１.mp3", true);
	m_pSoundMap[STR(CSoundMng::BGM::Select)] = LoadSound("Assets/BGM/ステージセレクト.mp3", true);
	m_pSoundMap[STR(CSoundMng::BGM::game2)] = LoadSound("Assets/BGM/ステージ2.mp3", true);
	m_pSoundMap[STR(CSoundMng::BGM::game3)] = LoadSound("Assets/BGM/ステージ3.mp3", true);
	m_pSoundMap[STR(CSoundMng::BGM::Op)] = LoadSound("Assets/BGM/op.mp3", true);
	m_pSoundMap[STR(CSoundMng::BGM::Ed)] = LoadSound("Assets/BGM/ed.mp3", true);

	// =-=-= 各SEを読み込み =-=-=
	// ----- システム -----
	m_pSoundMap[STR(CSoundMng::SystemSE::decision)] = LoadSound("Assets/SE/システム音/決定.mp3");
	m_pSoundMap[STR(CSoundMng::SystemSE::cancel)] = LoadSound("Assets/SE/システム音/キャンセル.mp3");
	m_pSoundMap[STR(CSoundMng::SystemSE::select)] = LoadSound("Assets/SE/システム音/選択.mp3");
	m_pSoundMap[STR(CSoundMng::SystemSE::Tstrat)] = LoadSound("Assets/SE/システム音/ゲーム開始(タイトル).mp3");
	m_pSoundMap[STR(CSoundMng::SystemSE::swap)] = LoadSound("Assets/SE/システム音/ステージチェンジ.mp3");
	m_pSoundMap[STR(CSoundMng::SystemSE::Fpon)] = LoadSound("Assets/SE/システム音/Fileopen.mp3");
	// ----- プレイヤー -----
	m_pSoundMap[STR(CSoundMng::PlayerSE::walkGrass)] = LoadSound("Assets/SE/プレイヤー/芝生を歩く.mp3"); // 草：歩く
	m_pSoundMap[STR(CSoundMng::PlayerSE::ranGrass)] = LoadSound("Assets/SE/プレイヤー/芝生を走る.mp3"); // 草:走る
	m_pSoundMap[STR(CSoundMng::PlayerSE::walkGround)] = LoadSound("Assets/SE/プレイヤー/土を歩く.mp3"); // 土：歩く
	m_pSoundMap[STR(CSoundMng::PlayerSE::ranGround)] = LoadSound("Assets/SE/プレイヤー/土を走る.mp3"); // 土:走る
	m_pSoundMap[STR(CSoundMng::PlayerSE::walkCream)] = LoadSound("Assets/SE/プレイヤー/クリームを歩く.mp3"); // クリーム：歩く
	m_pSoundMap[STR(CSoundMng::PlayerSE::runCream)] = LoadSound("Assets/SE/プレイヤー/クリーム走る.mp3"); // クリーム:走る
	m_pSoundMap[STR(CSoundMng::PlayerSE::walkSponge)] = LoadSound("Assets/SE/プレイヤー/スポンジを歩く.mp3"); // スポンジ：歩く
	m_pSoundMap[STR(CSoundMng::PlayerSE::runSponge)] = LoadSound("Assets/SE/プレイヤー/スポンジを走る.mp3"); // スポンジ:走る

	// ------リザルト--------
	m_pSoundMap[STR(CSoundMng::ResultSE::gameClear)] = LoadSound("Assets/BGM/ゲームクリア.mp3");
	m_pSoundMap[STR(CSoundMng::ResultSE::gameOver)] = LoadSound("Assets/BGM/ゲームオーバー.mp3");
	m_pSoundMap[STR(CSoundMng::ResultSE::stamp)] = LoadSound("Assets/SE/リザルト/リザルトハンコ音.mp3");
	m_pSoundMap[STR(CSoundMng::ResultSE::star)] = LoadSound("Assets/SE/リザルト/リザルト星.mp3");

	//-------吸い込み--------
	m_pSoundMap[STR(CSoundMng::SuctionSE::wind)] = LoadSound("Assets/SE/吸い込み/Suction1.mp3");
	m_pSoundMap[STR(CSoundMng::SuctionSE::suctionLow)] = LoadSound("Assets/SE/吸い込み/pon1.mp3");
	m_pSoundMap[STR(CSoundMng::SuctionSE::suctionHigh)] = LoadSound("Assets/SE/吸い込み/pon2.mp3");
	m_pSoundMap[STR(CSoundMng::SuctionSE::money)] = LoadSound("Assets/SE/吸い込み/coin_03.mp3");
	m_pSoundMap[STR(CSoundMng::SuctionSE::wind2)] = LoadSound("Assets/SE/吸い込み/Suction2.mp3");
	m_pSoundMap[STR(CSoundMng::SuctionSE::wind3)] = LoadSound("Assets/SE/吸い込み/Suction3.mp3");

	//------時間-------
	m_pSoundMap[STR(CSoundMng::TimeSE::countDown1)] = LoadSound("Assets/SE/時間/カウントダウン2.mp3");
	m_pSoundMap[STR(CSoundMng::TimeSE::countDown1_pi)] = LoadSound("Assets/SE/時間/カウントダウン1_ぴ.mp3");
	m_pSoundMap[STR(CSoundMng::TimeSE::timeUp1)] = LoadSound("Assets/SE/時間/タイマーストップ.mp3");
	m_pSoundMap[STR(CSoundMng::TimeSE::timeUp2)] = LoadSound("Assets/SE/時間/タイマーストップ2.mp3");
	m_pSoundMap[STR(CSoundMng::TimeSE::watchSlow)] = LoadSound("Assets/SE/時間/制限時間１(遅め).mp3");
	m_pSoundMap[STR(CSoundMng::TimeSE::watchEaly)] = LoadSound("Assets/SE/時間/制限時間２(早め).mp3");

	//------破壊--------
	m_pSoundMap[STR(CSoundMng::DestroySE::woodBreak)] = LoadSound("Assets/SE/破壊/木破壊.mp3");
	m_pSoundMap[STR(CSoundMng::DestroySE::wood)] = LoadSound("Assets/SE/破壊/チョコ木.mp3");
	m_pSoundMap[STR(CSoundMng::DestroySE::rockBreak)] = LoadSound("Assets/SE/破壊/石破壊.mp3");
	m_pSoundMap[STR(CSoundMng::DestroySE::rock)] = LoadSound("Assets/SE/破壊/石破壊中.mp3");
	m_pSoundMap[STR(CSoundMng::DestroySE::woodHouseBreak)] = LoadSound("Assets/SE/破壊/建築物破壊(木).mp3");
	m_pSoundMap[STR(CSoundMng::DestroySE::rocklHouseBreak)] = LoadSound("Assets/SE/破壊/鉄破壊.mp3");
	//------買い物------
	m_pSoundMap[STR(CSoundMng::ShopSE::buy)] = LoadSound("Assets/SE/買い物/レジ音.mp3");
	m_pSoundMap[STR(CSoundMng::ShopSE::text)] = LoadSound("Assets/SE/買い物/テキスト.mp3");

	//------ギミック----
	m_pSoundMap[STR(CSoundMng::GimmickSE::cookie)] = LoadSound("Assets/SE/ギミック/クッキー.mp3");
	m_pSoundMap[STR(CSoundMng::GimmickSE::cookieBreak)] = LoadSound("Assets/SE/ギミック/クッキー破壊.mp3");
	m_pSoundMap[STR(CSoundMng::GimmickSE::fire)] = LoadSound("Assets/SE/ギミック/消火.mp3");
	m_pSoundMap[STR(CSoundMng::GimmickSE::aokinoko)] = LoadSound("Assets/SE/ギミック/アオキノコ.mp3");

}

// ========== デストラクタ ==========
CSoundMng::~CSoundMng()
{
	// =-=-= 解放 =-=-=
	// ----- 音源map -----
	for (auto it = m_pSoundMap.begin(); it != m_pSoundMap.end();) {	// 全サウンドデータを解放
		//delete it->second->pAudioData;						// サウンドデータを解放 Sound.hがやってくれるので省略
		it = m_pSoundMap.erase(it);								// ポインタを開放
	}

	// ----- スピーカーlist -----
	for (auto it = m_pSpeakerList.begin(); it != m_pSpeakerList.end();) {	// 全スピーカーデータを解放
		if ((*it)) {
			(*it)->m_Speaker->Stop();						// 再生停止(不要？)
			(*it)->m_Speaker->DestroyVoice();				// 音を破棄
			delete (*it);									// 必要？不要？？これ書くと参照エラー出る。	Destroyで動的データ消えてる？
			it = m_pSpeakerList.erase(it);				// ポインタを開放
		}
	}
}


// ========== 再生終了スピーカー破棄 ==========
// 引　数：なし
// 戻り値：なし
// 再生が終わったSEスピーカーを破棄する
// ==========================================
void CSoundMng::DeleteSpeaker()
{
	for (auto it = m_pSpeakerList.begin(); it != m_pSpeakerList.end();)	// 全てのSEスピーカーをみる
	{
		XAUDIO2_VOICE_STATE state{ 0 };
		(*it)->m_Speaker->GetState(&state);					// 再生状況取得
		if (state.BuffersQueued == 0)						// 再生が終わっていたら破棄
		{
			// ----- スピーカー削除 -----
			(*it)->m_Speaker->Stop();						// 再生停止(不要？)
			(*it)->m_Speaker->DestroyVoice();				// 音を破棄
			delete (*it);									// スピーカー構造体の実体解放
			it = m_pSpeakerList.erase(it);				// ポインタを開放
		}
		else
		{
			it++;								// 次の要素へ
		}
	}
}

// ========== 再生中スピーカー全破棄 ==========
// 引　数：なし
// 戻り値：なし
// 再生中の全てのスピーカーを破棄する
// ==========================================
void CSoundMng::AllDeleteSpeaker()
{
	for (auto it = m_pSpeakerList.begin(); it != m_pSpeakerList.end();)	// 全てのSEスピーカーをみる
	{
		// ----- スピーカー削除 -----
		(*it)->m_Speaker->Stop();						// 再生停止(不要？)
		(*it)->m_Speaker->DestroyVoice();				// 音を破棄
		delete (*it);									// スピーカー構造体の実体解放
		it = m_pSpeakerList.erase(it);					// ポインタを開放
	}
}

// ========== BGM再生 ==========
// 引　数：
// BGM 鳴らしたいBGM番号
// 戻り値：なし
// 指定のBGMを鳴らす
// =====================================
void CSoundMng::playSound(BGM kind)
{
	switch (kind)
	{
	case CSoundMng::BGM::title:	// タイトルBGM
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::BGM::title)]), SpeakerKind::bTitle });
		m_pSpeakerList.back()->m_Speaker->SetVolume(TITLE_BGM_VOL);
		break;
	case CSoundMng::BGM::game:	// テキスト表示(プルプル)
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::BGM::game)]), SpeakerKind::bGame });
		m_pSpeakerList.back()->m_Speaker->SetVolume(GAEM_BGM_VOL);
		break;
	case CSoundMng::BGM::game2:	// ゲーム2
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::BGM::game2)]), SpeakerKind::bGame2 });
		m_pSpeakerList.back()->m_Speaker->SetVolume(GAEM2_BGM_VOL);
		break;
	case CSoundMng::BGM::game3:	// ゲーム3
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::BGM::game3)]), SpeakerKind::bGame });
		m_pSpeakerList.back()->m_Speaker->SetVolume(GAEM3_BGM_VOL);
		break;
	case CSoundMng::BGM::Select:	// ステージセレクト
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::BGM::Select)]), SpeakerKind::bSelect });
		m_pSpeakerList.back()->m_Speaker->SetVolume(SELECT_BGM_VOL);
		break;
	case CSoundMng::BGM::Op:	// オープニング
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::BGM::Op)]), SpeakerKind::bOp });
		m_pSpeakerList.back()->m_Speaker->SetVolume(OP_BGM_VOL);
		break;
	case CSoundMng::BGM::Ed:	// エンディング
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::BGM::Ed)]), SpeakerKind::bEd });
		m_pSpeakerList.back()->m_Speaker->SetVolume(ED_BGM_VOL);
		break;
	}
}

// ========== システムSE再生 ==========
// 引　数：
// SystemSE 鳴らしたいSE番号
// 戻り値：なし
// 指定のシステムSEを鳴らす
// ===================================
void CSoundMng::playSound(SystemSE kind)
{
	switch (kind)
	{
	case CSoundMng::decision:	// 決定
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::SystemSE::decision)]), SpeakerKind::sDecision });	// スピーカー生成
		m_pSpeakerList.back()->m_Speaker->SetVolume(DECSION_VOL);	// ここに小数いれる(たぶん0.0/*最小*/ ~ 1.0/*最大*/)
		break;
	case CSoundMng::cancel:		// キャンセル
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::SystemSE::cancel)]), SpeakerKind::sCancel });
		m_pSpeakerList.back()->m_Speaker->SetVolume(CANCEL_VOL);
		break;
	case CSoundMng::select:		// 選択
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::SystemSE::select)]), SpeakerKind::sSelect });
		m_pSpeakerList.back()->m_Speaker->SetVolume(SELECT_VOL);
		break;
	case CSoundMng::Tstrat:		// ゲーム開始
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::SystemSE::Tstrat)]), SpeakerKind::sTStrat });
		m_pSpeakerList.back()->m_Speaker->SetVolume(TSTRAT_VOL);
		break;
	case CSoundMng::swap:		// ステージチェンジ
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::SystemSE::swap)]), SpeakerKind::sSwap });
		m_pSpeakerList.back()->m_Speaker->SetVolume(SWAP_VOL);
	case CSoundMng::Fpon:		// リザルト
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::SystemSE::Fpon)]), SpeakerKind::sFpon });
		m_pSpeakerList.back()->m_Speaker->SetVolume(RPON_VOL);
		break;
		break;
	}
}

// ========== プレイヤーSE再生 ==========
// 引　数：
// PlayerSE 鳴らしたいSE番号
// 戻り値：なし
// 指定のプレイヤーSEを鳴らす
// =====================================
void CSoundMng::playSound(PlayerSE kind)
{
	switch (kind)
	{
	case CSoundMng::walkGrass:	// 草：歩く
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::PlayerSE::walkGrass)]), SpeakerKind::sWalkGrass });
		m_pSpeakerList.back()->m_Speaker->SetVolume(WALK_GRASS_VOL);
		break;
	case CSoundMng::ranGrass:	// 草：走る
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::PlayerSE::ranGrass)]), SpeakerKind::sRanGrass });
		m_pSpeakerList.back()->m_Speaker->SetVolume(RAN_GRASS_VOL);
		break;
	case CSoundMng::walkGround:	// 土：歩く
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::PlayerSE::walkGround)]), SpeakerKind::sWalkGround });
		m_pSpeakerList.back()->m_Speaker->SetVolume(WALK_GROUND_VOL);
		break;
	case CSoundMng::ranGround:	// 土：走る
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::PlayerSE::ranGround)]), SpeakerKind::sRanGround });
		m_pSpeakerList.back()->m_Speaker->SetVolume(RAN_GROUND_VOL);
		break;
	case CSoundMng::walkCream:	// クリーム：歩く
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::PlayerSE::walkCream)]), SpeakerKind::sWalkCream });
		m_pSpeakerList.back()->m_Speaker->SetVolume(WALK_CREAM_VOL);
		break;
	case CSoundMng::runCream:	//	クリーム：走る
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::PlayerSE::runCream)]), SpeakerKind::sRunCream });
		m_pSpeakerList.back()->m_Speaker->SetVolume(RAN_CREAM_VOL);
		break;
	case CSoundMng::walkSponge:	// スポンジ：歩く
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::PlayerSE::walkSponge)]), SpeakerKind::sWalkSponge });
		m_pSpeakerList.back()->m_Speaker->SetVolume(WALK_SPONGE_VOL);
		break;
	case CSoundMng::runSponge:	// スポンジ：走る
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::PlayerSE::runSponge)]), SpeakerKind::sRunSponge });
		m_pSpeakerList.back()->m_Speaker->SetVolume(RAN_SPONGE_VOL);
		break;
	}
}

// ========== リザルトSE再生 ==========
// 引　数：
// ResultSE 鳴らしたいSE番号
// 戻り値：なし
// 指定のリザルトSEを鳴らす
// =====================================
void CSoundMng::playSound(ResultSE kind)
{
	switch (kind)
	{
	case CSoundMng::gameOver:	// ゲームオーバー
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::ResultSE::gameOver)]), SpeakerKind::sGameOver });
		m_pSpeakerList.back()->m_Speaker->SetVolume(GAMEOVER_VOL);
		break;
	case CSoundMng::gameClear:	// ゲームクリア
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::ResultSE::gameClear)]), SpeakerKind::sGameClear });
		m_pSpeakerList.back()->m_Speaker->SetVolume(GAMECLEAR_VOL);
		break;
	case CSoundMng::stamp:		// ハンコ
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::ResultSE::stamp)]), SpeakerKind::sStamp });
		m_pSpeakerList.back()->m_Speaker->SetVolume(STAMP_VOL);
		break;
	case CSoundMng::star:		// 星
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::ResultSE::star)]), SpeakerKind::sStar });
		m_pSpeakerList.back()->m_Speaker->SetVolume(STAR_VOL);
		break;
	}
}

// ========== 吸い込みSE再生 ==========
// 引　数：
// SuctionSE 鳴らしたいSE番号
// 戻り値：なし
// 指定の吸い込みSEを鳴らす
// =====================================
void CSoundMng::playSound(SuctionSE kind)
{
	switch (kind)
	{
	case CSoundMng::wind:		// 吸い込み中
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::SuctionSE::wind)]), SpeakerKind::sWind });
		m_pSpeakerList.back()->m_Speaker->SetVolume(WIND_VOL);
		break;
	case CSoundMng::wind2:		// 吸い込み中
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::SuctionSE::wind2)]), SpeakerKind::sWind2 });
		m_pSpeakerList.back()->m_Speaker->SetVolume(WIND2_VOL);
		break;
	case CSoundMng::wind3:		// 吸い込み中
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::SuctionSE::wind3)]), SpeakerKind::sWind3 });
		m_pSpeakerList.back()->m_Speaker->SetVolume(WIND3_VOL);
		break;
	case CSoundMng::suctionHigh:// 吸い込み完了：高い音
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::SuctionSE::suctionHigh)]), SpeakerKind::sSuctionHigh });
		m_pSpeakerList.back()->m_Speaker->SetVolume(SUCTION_HIGH_VOL);
		break;
	case CSoundMng::suctionLow:	// 吸い込み完了：低い音
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::SuctionSE::suctionLow)]), SpeakerKind::sSuctionLow });
		m_pSpeakerList.back()->m_Speaker->SetVolume(SUCTION_LOW_VOL);
		break;
	case CSoundMng::money:		// お金獲得
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::SuctionSE::money)]), SpeakerKind::sMoney });
		m_pSpeakerList.back()->m_Speaker->SetVolume(MONEY_VOL);
		break;
	}
}

// ========== 時間SE再生 ==========
// 引　数：
// TimeSE 鳴らしたいSE番号
// 戻り値：なし
// 指定の時間SEを鳴らす
// =====================================
void CSoundMng::playSound(TimeSE kind)
{
	switch (kind)
	{
	case CSoundMng::countDown1:	// カウントダウン１
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::TimeSE::countDown1)]), SpeakerKind::sCountDown1 });
		m_pSpeakerList.back()->m_Speaker->SetVolume(COUNTDOWN_1_VOL);
		break;
	case CSoundMng::countDown1_pi:	// カウントダウン１・ぴー
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::TimeSE::countDown1_pi)]), SpeakerKind::sCountDown1_pi });
		m_pSpeakerList.back()->m_Speaker->SetVolume(COUNTDOWN_1_PI_VOL);
		break;
	case CSoundMng::countDown2:	// カウントダウン２
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::TimeSE::countDown2)]), SpeakerKind::sCountDown2 });
		m_pSpeakerList.back()->m_Speaker->SetVolume(COUNTDOWN_2_VOL);
		break;
	case CSoundMng::timeUp1:	// 時間切れ
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::TimeSE::timeUp1)]), SpeakerKind::sTimeUp1 });
		m_pSpeakerList.back()->m_Speaker->SetVolume(TIMEUP_1_VOL);
		break;
	case CSoundMng::timeUp2:	// １００ぱー達成（ベル）
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::TimeSE::timeUp2)]), SpeakerKind::sTimeUp2 });
		m_pSpeakerList.back()->m_Speaker->SetVolume(TIMEUP_2_VOL);
		break;
	case CSoundMng::watchSlow:	// 秒針：遅い
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::TimeSE::watchSlow)]), SpeakerKind::sWatchSlow });
		m_pSpeakerList.back()->m_Speaker->SetVolume(WATCH_SLOW_VOL);
		break;
	case CSoundMng::watchEaly:	// 秒針：速い
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::TimeSE::watchEaly)]), SpeakerKind::sWatchEaly });
		m_pSpeakerList.back()->m_Speaker->SetVolume(WATCH_EALY_VOL);
		break;
	}
}

// ========== 破壊SE再生 ==========
// 引　数：
// DestroySE 鳴らしたいSE番号
// 戻り値：なし
// 指定の破壊SEを鳴らす
// =====================================
void CSoundMng::playSound(DestroySE kind)
{
	switch (kind)
	{
	case CSoundMng::wood:			// 木破壊中
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::DestroySE::wood)]), SpeakerKind::sWood });
		m_pSpeakerList.back()->m_Speaker->SetVolume(WOOD_VOL);
		break;
	case CSoundMng::woodBreak:		// 木破壊完了
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::DestroySE::woodBreak)]), SpeakerKind::sWoodBreak });
		m_pSpeakerList.back()->m_Speaker->SetVolume(WOOD_BREAK_VOL);
		break;
	case CSoundMng::rock:			// 岩破壊中
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::DestroySE::rock)]), SpeakerKind::sRock });
		m_pSpeakerList.back()->m_Speaker->SetVolume(ROCK_VOL);
		break;
	case CSoundMng::rockBreak:		// 岩破壊完了
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::DestroySE::rockBreak)]), SpeakerKind::sRockBreak });
		m_pSpeakerList.back()->m_Speaker->SetVolume(ROCK_BREAK_VOL);
		break;
	case CSoundMng::woodHouse:		// 木製の家破壊中
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::DestroySE::woodHouse)]), SpeakerKind::sWoodHouse });
		m_pSpeakerList.back()->m_Speaker->SetVolume(WOOD_HOUSE_VOL);
		break;
	case CSoundMng::woodHouseBreak:	// 木製の家破壊完了
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::DestroySE::woodHouseBreak)]), SpeakerKind::sWoodHouseBreak });
		m_pSpeakerList.back()->m_Speaker->SetVolume(WOOD_HOUSE_BREAK_VOL);
		break;
	case CSoundMng::rocklHouse:		// 石製の家破壊中
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::DestroySE::rocklHouse)]), SpeakerKind::sRocklHouse });
		m_pSpeakerList.back()->m_Speaker->SetVolume(ROCK_HOUSE_VOL);
		break;
	case CSoundMng::rocklHouseBreak:// 石製の家破壊完了
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::DestroySE::rocklHouseBreak)]), SpeakerKind::sRocklHouseBreak });
		m_pSpeakerList.back()->m_Speaker->SetVolume(ROCK_HOUSE_BREAK_VOL);
		break;
	}
}

// ========== 買い物SE再生 ==========
// 引　数：
// ShopSE 鳴らしたいSE番号
// 戻り値：なし
// 指定の買い物SEを鳴らす
// =====================================
void CSoundMng::playSound(ShopSE kind)
{
	switch (kind)
	{
	case CSoundMng::buy:		// 購入
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::ShopSE::buy)]), SpeakerKind::sBuy });
		m_pSpeakerList.back()->m_Speaker->SetVolume(BUY_VOL);
		break;
	case CSoundMng::text:		// テキスト表示(プルプル)
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::ShopSE::text)]), SpeakerKind::sText });
		m_pSpeakerList.back()->m_Speaker->SetVolume(TEXT_VOL);
		break;
	}
}
// ========== ギミックSE再生 ==========
// 引　数：
// ShopSE 鳴らしたいSE番号
// 戻り値：なし
// 指定のギミックSEを鳴らす
// =====================================
void CSoundMng::playSound(GimmickSE kind)
{
	switch (kind)
	{
	case CSoundMng::cookie:		// 購入
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::GimmickSE::cookie)]), SpeakerKind::sCookie });
		m_pSpeakerList.back()->m_Speaker->SetVolume(COOKIE_VOL);
		break;
	case CSoundMng::cookieBreak:		// テキスト表示(プルプル)
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::GimmickSE::cookieBreak)]), SpeakerKind::sCookieBreak });
		m_pSpeakerList.back()->m_Speaker->SetVolume(COOKIEBREAK_VOL);
		break;
	case CSoundMng::fire:		// テキスト表示(プルプル)
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::GimmickSE::fire)]), SpeakerKind::sFire });
		m_pSpeakerList.back()->m_Speaker->SetVolume(FIRE_VOL);
		break;
	case CSoundMng::aokinoko:		// テキスト表示(プルプル)
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::GimmickSE::aokinoko)]), SpeakerKind::sAokinoko });
		m_pSpeakerList.back()->m_Speaker->SetVolume(AOKINOKO_VOL);
		break;
	}
}

// ========== BGM再生チェック ===============
// 引　数：
// BGM 調べたいBGM番号
// 戻り値：再生終了(or 再生してない) → true
// 指定のBGMが再生中かチェック
// ==========================================
bool CSoundMng::CheckSoundEnd(BGM kind)
{
	for (Speaker* pSpeaker : m_pSpeakerList)
	{
		switch (kind)
		{
		case CSoundMng::BGM::title:
			if (pSpeaker->m_Kind == bTitle) return false;
			break;
		case CSoundMng::BGM::game:
			if (pSpeaker->m_Kind == bGame) return false;
			break;
		case CSoundMng::BGM::game2:
			if (pSpeaker->m_Kind == bGame2) return false;
			break;
		case CSoundMng::BGM::game3:
			if (pSpeaker->m_Kind == bGame3) return false;
			break;
		case CSoundMng::BGM::Select:
			if (pSpeaker->m_Kind == bSelect) return false;
			break;
		case CSoundMng::BGM::Op:
			if (pSpeaker->m_Kind == bOp) return false;
			break;
		case CSoundMng::BGM::Ed:
			if (pSpeaker->m_Kind == bEd) return false;
			break;
		}
	}

	return true;
}


// ========== システムSE再生終了チェック ===============
// 引　数：
// SystemSE 調べたいSE番号
// 戻り値：再生終了(or 再生してない) → true
// 指定のシステムSEが再生終了したかチェック
// ==========================================
bool CSoundMng::CheckSoundEnd(SystemSE kind)
{
	for (Speaker* pSpeaker : m_pSpeakerList)
	{
		switch (kind)
		{
		case CSoundMng::SystemSE::decision:
			if (pSpeaker->m_Kind == sDecision) return false;
			break;
		case CSoundMng::SystemSE::cancel:
			if (pSpeaker->m_Kind == sCancel) return false;
			break;
		case CSoundMng::SystemSE::select:
			if (pSpeaker->m_Kind == sSelect) return false;
			break;
		case CSoundMng::SystemSE::swap:
			if (pSpeaker->m_Kind == sSwap) return false;
			break;
		case CSoundMng::SystemSE::Fpon:
			if (pSpeaker->m_Kind == sFpon) return false;
			break;
		}
	}

	return true;
}

// ========== プレイヤーSE再生終了チェック ===============
// 引　数：
// PlayerSE 調べたいSE番号
// 戻り値：再生終了(or 再生してない) → true
// 指定のプレイヤーSEが再生終了したかチェック
// ==========================================
bool CSoundMng::CheckSoundEnd(PlayerSE kind)
{
	for (Speaker* pSpeaker : m_pSpeakerList)
	{
		switch (kind)
		{
		case CSoundMng::PlayerSE::walkGrass:
			if (pSpeaker->m_Kind == sWalkGrass) return false;
			break;
		case CSoundMng::PlayerSE::ranGrass:
			if (pSpeaker->m_Kind == sRanGrass) return false;
			break;
		case CSoundMng::PlayerSE::walkGround:
			if (pSpeaker->m_Kind == sWalkGround) return false;
			break;
		case CSoundMng::PlayerSE::ranGround:
			if (pSpeaker->m_Kind == sRanGround) return false;
			break;
		case CSoundMng::PlayerSE::walkCream:
			if (pSpeaker->m_Kind == sWalkCream) return false;
			break;
		case CSoundMng::PlayerSE::runCream:
			if (pSpeaker->m_Kind == sRunCream) return false;
			break;
		case CSoundMng::PlayerSE::walkSponge:
			if (pSpeaker->m_Kind == sWalkSponge) return false;
			break;
		case CSoundMng::PlayerSE::runSponge:
			if (pSpeaker->m_Kind == sRunSponge) return false;
			break;
		}
	}

	return true;
}



// ========== 吸い込み再生終了チェック ===============
// 引　数：
// SuctionSE 調べたいSE番号
// 戻り値：再生終了(or 再生してない) → true
// 指定の吸い込みSEが再生終了したかチェック
// ==========================================
bool CSoundMng::CheckSoundEnd(SuctionSE kind)
{
	for (Speaker* pSpeaker : m_pSpeakerList)
	{
		switch (kind)
		{
		case CSoundMng::SuctionSE::wind:
			if (pSpeaker->m_Kind == sWind) return false;
			break;
		case CSoundMng::SuctionSE::wind2:
			if (pSpeaker->m_Kind == sWind2) return false;
			break;
		case CSoundMng::SuctionSE::wind3:
			if (pSpeaker->m_Kind == sWind3) return false;
			break;
		}
	}

	return true;
}

// ========== 時間再生終了チェック ===============
// 引　数：
// TimeSE 調べたいSE番号
// 戻り値：再生終了(or 再生してない) → true
// 指定の時間SEが再生終了したかチェック
// ==========================================
bool CSoundMng::CheckSoundEnd(TimeSE kind)
{
	for (Speaker* pSpeaker : m_pSpeakerList)
	{
		switch (kind)
		{
		case CSoundMng::TimeSE::countDown1:
			if (pSpeaker->m_Kind == sCountDown1) return false;
			break;
		case CSoundMng::TimeSE::countDown1_pi:
			if (pSpeaker->m_Kind == sCountDown1_pi) return false;
			break;
		case CSoundMng::TimeSE::countDown2:
			if (pSpeaker->m_Kind == sCountDown2) return false;
			break;
		case CSoundMng::TimeSE::timeUp1:
			if (pSpeaker->m_Kind == sTimeUp1) return false;
			break;
		case CSoundMng::TimeSE::timeUp2:
			if (pSpeaker->m_Kind == sTimeUp2) return false;
			break;
		}
	}

	return true;
}
// ========== 時間再生終了チェック ===============
// 引　数：
// TimeSE 調べたいSE番号
// 戻り値：再生終了(or 再生してない) → true
// 指定の時間SEが再生終了したかチェック
// ==========================================
bool CSoundMng::CheckSoundEnd(ShopSE kind)
{
	for (Speaker* pSpeaker : m_pSpeakerList)
	{
		switch (kind)
		{
		case CSoundMng::ShopSE::buy:
			if (pSpeaker->m_Kind == sBuy) return false;
			break;
		case CSoundMng::ShopSE::text:
			if (pSpeaker->m_Kind == sText) return false;
			break;
		}
	}

	return true;
}

bool CSoundMng::CheckSoundEnd(GimmickSE kind)
{
	for (Speaker* pSpeaker : m_pSpeakerList)
	{
		switch (kind)
		{
		case CSoundMng::GimmickSE::cookie:
			if (pSpeaker->m_Kind == sCookie) return false;
			break;
		case CSoundMng::GimmickSE::cookieBreak:
			if (pSpeaker->m_Kind == sCookieBreak) return false;
			break;
		case CSoundMng::GimmickSE::fire:
			if (pSpeaker->m_Kind == sFire) return false;
			break;
		case CSoundMng::GimmickSE::aokinoko:
			if (pSpeaker->m_Kind == sAokinoko) return false;
			break;
		}
	}

	return true;
}

// ========== BGM再生停止 ==========
// 引　数：
// BGM 停止したいBGM番号
// 戻り値：なし
// 指定のBGMの再生を停止し、スピーカーを破棄する
// ==========================================
void CSoundMng::StopSound(BGM kind)
{
	bool flg = false;	// 再生中

	for (auto it = m_pSpeakerList.begin(); it != m_pSpeakerList.end(); it++)	// 全再生中SEの中から指定のSEを探す
	{
		switch (kind)
		{
		case CSoundMng::BGM::title:
			if ((*it)->m_Kind == bTitle) flg = true;
			break;
		case CSoundMng::BGM::game:
			if ((*it)->m_Kind == bGame) flg = true;
			break;
		case CSoundMng::BGM::game2:
			if ((*it)->m_Kind == bGame2) flg = true;
			break;
		case CSoundMng::BGM::game3:
			if ((*it)->m_Kind == bGame3) flg = true;
			break;
		case CSoundMng::BGM::Select:
			if ((*it)->m_Kind == bSelect) flg = true;
			break;
		}

		if (flg)	// 再生中の指定SEを見つけたらそれを破棄
		{
			(*it)->m_Speaker->Stop();
			(*it)->m_Speaker->DestroyVoice();
			delete (*it);
			m_pSpeakerList.erase(it);
			break;
		}
	}
}

void CSoundMng::StopSound(SystemSE kind)
{
	bool flg = false;	// 再生中
	for (auto it = m_pSpeakerList.begin(); it != m_pSpeakerList.end(); it++)
	{
		switch (kind)
		{
		case CSoundMng::SystemSE::Fpon:
			if ((*it)->m_Kind == sFpon) flg = true;
			break;
		}
		if (flg)	// 再生中の指定SEを見つけたらそれを破棄
		{
			(*it)->m_Speaker->Stop();
			(*it)->m_Speaker->DestroyVoice();
			delete (*it);
			m_pSpeakerList.erase(it);
			break;
		}
	}
}
// ========== プレイヤーSE再生停止 ==========
// 引　数：
// PlayerSE 停止したい
// 戻り値：なし
// 指定のシステムSEの再生を停止し、スピーカーを破棄する
// ==========================================
void CSoundMng::StopSound(PlayerSE kind)
{
	bool flg = false;	// 再生中
	for (auto it = m_pSpeakerList.begin(); it != m_pSpeakerList.end(); it++)
	{
		switch (kind)
		{
		case CSoundMng::PlayerSE::walkGrass:
			if ((*it)->m_Kind == sWalkGrass) flg = true;
			break;
		case CSoundMng::PlayerSE::ranGrass:
			if ((*it)->m_Kind == sRanGrass) flg = true;
			break;
		case CSoundMng::PlayerSE::walkGround:
			if ((*it)->m_Kind == sWalkGround) flg = true;
			break;
		case CSoundMng::PlayerSE::ranGround:
			if ((*it)->m_Kind == sRanGround) flg = true;
			break;
		case CSoundMng::PlayerSE::walkCream:
			if ((*it)->m_Kind == sWalkCream) flg = true;
			break;
		case CSoundMng::PlayerSE::runCream:
			if ((*it)->m_Kind == sRunCream) flg = true;
			break;
		case CSoundMng::PlayerSE::walkSponge:
			if ((*it)->m_Kind == sWalkSponge) flg = true;
			break;
		case CSoundMng::PlayerSE::runSponge:
			if ((*it)->m_Kind == sRunSponge) flg = true;
			break;
		}

		if (flg)	// 再生中の指定SEを見つけたらそれを破棄
		{
			(*it)->m_Speaker->Stop();
			(*it)->m_Speaker->DestroyVoice();
			delete (*it);
			m_pSpeakerList.erase(it);
			break;
		}
	}
}

// ========== 吸い込みSE再生停止 ==========
// 引　数：
// SuctionSE 停止したい
// 戻り値：なし
// 指定の吸い込みSEの再生を停止し、スピーカーを破棄する
// ==========================================
void CSoundMng::StopSound(SuctionSE kind)
{
	bool flg = false;	// 再生中

	for (auto it = m_pSpeakerList.begin(); it != m_pSpeakerList.end(); it++)	// 全再生中SEの中から指定のSEを探す
	{
		switch (kind)
		{
		case CSoundMng::SuctionSE::wind:
			if ((*it)->m_Kind == sWind) flg = true;
			break;
		case CSoundMng::SuctionSE::wind2:
				if ((*it)->m_Kind == sWind2) flg = true;
				break;
		case CSoundMng::SuctionSE::wind3:
				if ((*it)->m_Kind == sWind3) flg = true;
				break;


		}

		if (flg)	// 再生中の指定SEを見つけたらそれを破棄
		{
			(*it)->m_Speaker->Stop();
			(*it)->m_Speaker->DestroyVoice();
			delete (*it);
			m_pSpeakerList.erase(it);
			break;
		}
	}
	
}

void CSoundMng::StopSound(ShopSE kind)
{
	bool flg = false;	// 再生中

	for (auto it = m_pSpeakerList.begin(); it != m_pSpeakerList.end(); it++)	// 全再生中SEの中から指定のSEを探す
	{
		switch (kind)
		{
		case CSoundMng::ShopSE::text:
			if ((*it)->m_Kind == sWind) flg = true;
			break;
		}

		if (flg)	// 再生中の指定SEを見つけたらそれを破棄
		{
			(*it)->m_Speaker->Stop();
			(*it)->m_Speaker->DestroyVoice();
			delete (*it);
			m_pSpeakerList.erase(it);
			break;
		}
	}
}
