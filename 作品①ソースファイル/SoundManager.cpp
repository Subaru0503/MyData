//=================================================================
//
//	SoundManager.cpp
//	サウンドを一元管理する
//
//=================================================================

//----インクルード部----
#include "SoundManager.h"

//----ファイル読み込みに使用----
#include <iostream>
#include <fstream>
#include <string>

//----定数・マクロ定義-----
// BGM
#define TITLE_BGM_VOL			(0.15f)	// タイトルBGM
#define GAEM_BGM_VOL			(0.15f)	// ゲームBGM
#define CLEAR_BGM_VOL			(0.15f)	// クリアBGM

// SE
#define TSTRAT_VOL				(1.0f)	//ゲーム開始(タイトル)
#define GSTRAT_VOL				(1.0f)	//ゲームスタート(ステージ)
#define PAUSE_VOL				(0.8f)	// ポーズ画面を開く
#define PAUSE_CLOSE_VOL			(0.8f)	// ポーズ画面を閉じる
#define TIME_OVER_VOL			(0.7f)	// 時間切れ
#define SELECT_VOL				(1.0f)	// 選択
#define DECSION_VOL				(0.5f)	// 決定
#define SPIN_VOL				(1.0f)	// ネジ回転音
#define SPIN_MAX_VOL 			(0.4f)	// ネジ最大回した音

#define STR(var) #var   //引数にした変数を変数名を示す文字列として返すマクロ関数

using namespace std;

// デストラクタ
SoundManager::~SoundManager()
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

	UninitSound();
}


// 再生終了スピーカー破棄
void SoundManager::DeleteSpeaker()
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

// 再生中スピーカー全破棄
void SoundManager::AllDeleteSpeaker()
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

// BGM,SE読み込み
void SoundManager::SoundLoad()
{
	// BGM読み込み
	ifstream file("Assets/Sound/BGM/BGM.csv");	// ファイルオープン
	string cell;	// セルごとの読み込み先
	int MaxLine;	// 行数格納用
	string cellData;	// セルデータ格納用
	string path;	// 読み込みパス

	if (!file)
	{
		MessageBox(NULL, "BGM.csvファイルが読み込めませんでした", "SoundManager.cpp", MB_OK);
		return;
	}

	getline(file, cell, ',');	// 行数抽出
	MaxLine = stoi(cell);		// 行数格納

	// 3行目まで移動
	getline(file, cell);
	getline(file, cell);

	// ファイルからデータを読み込む
	for (int i = 0; i < MaxLine; i++)
	{
		getline(file, cell, ',');	// セル抽出(1列目)
		getline(file, cell, ',');	// セル抽出(2列目)

		// パス設定
		path = "Assets/Sound/BGM/" + cell + ".wav";

		if (cell == "Title")
		{
			m_pSoundMap[STR(SoundManager::BGM::Title)] = LoadSound(path.c_str(), true);
		}
		else if (cell == "Stage")
		{
			m_pSoundMap[STR(SoundManager::BGM::Stage)] = LoadSound(path.c_str(), true);
		}
		else if (cell == "Clear")
		{
			m_pSoundMap[STR(SoundManager::BGM::Clear)] = LoadSound(path.c_str(), true);
		}
		getline(file, cell);		// 次の行へ
	}
	file.close();	// ファイルを閉じる



	// SE読み込み
	file.open("Assets/Sound/SE/SE.csv");	// ファイルオープン

	if (!file)
	{
		MessageBox(NULL, "SE.csvファイルが読み込めませんでした", "SoundManager.cpp", MB_OK);
		return;
	}

	getline(file, cell, ',');	// 行数抽出
	MaxLine = stoi(cell);		// 行数格納

	// 3行目まで移動
	getline(file, cell);
	getline(file, cell);

	// ファイルからデータを読み込む
	for (int i = 0; i < MaxLine; i++)
	{
		getline(file, cell, ',');	// セル抽出(1列目)
		getline(file, cell, ',');	// セル抽出(2列目)

		// パス設定
		path = "Assets/Sound/SE/" + cell + ".wav";

		if (cell == "TitleTouch")
		{			
			m_pSoundMap[STR(SoundManager::SystemSE::Tstrat)] = LoadSound(path.c_str());
		}
		else if (cell == "GameStart")
		{
			m_pSoundMap[STR(SoundManager::SystemSE::Gstart)] = LoadSound(path.c_str());
		}
		else if (cell == "Pause")
		{
			m_pSoundMap[STR(SoundManager::SystemSE::Pause)] = LoadSound(path.c_str());
		}
		else if (cell == "PauseClose")
		{
			m_pSoundMap[STR(SoundManager::SystemSE::PauseClose)] = LoadSound(path.c_str());
		}
		else if (cell == "TimeOver")
		{
			m_pSoundMap[STR(SoundManager::SystemSE::TimeOver)] = LoadSound(path.c_str());
		}
		else if (cell == "Select")
		{
			m_pSoundMap[STR(SoundManager::SystemSE::Select)] = LoadSound(path.c_str());
		}
		else if (cell == "Decision")
		{
			m_pSoundMap[STR(SoundManager::SystemSE::Decision)] = LoadSound(path.c_str());
		}
		else if (cell == "ScrewSpin")
		{
			m_pSoundMap[STR(SoundManager::ScrewSE::Spin)] = LoadSound(path.c_str());
		}
		else if (cell == "ScrewMax")
		{
			m_pSoundMap[STR(SoundManager::ScrewSE::SpinMax)] = LoadSound(path.c_str());
		}
		getline(file, cell);		// 次の行へ
	}
	file.close();	// ファイルを閉じる
}

// BGM再生
void SoundManager::playSound(BGM kind)
{
	switch (kind)
	{
	case SoundManager::BGM::Title:	// タイトルBGM
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(SoundManager::BGM::Title)]), SpeakerKind::bTitle });
		m_pSpeakerList.back()->m_Speaker->SetVolume(TITLE_BGM_VOL);
		break;
	case SoundManager::BGM::Stage:	// ゲームBGM
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(SoundManager::BGM::Stage)]), SpeakerKind::bGame });
		m_pSpeakerList.back()->m_Speaker->SetVolume(GAEM_BGM_VOL);
		break;
	case SoundManager::BGM::Clear:	// クリアBGM
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(SoundManager::BGM::Clear)]), SpeakerKind::bClear });
		m_pSpeakerList.back()->m_Speaker->SetVolume(CLEAR_BGM_VOL);
		break;
	}
}

// システムSE再生
void SoundManager::playSound(SystemSE kind)
{
	switch (kind)
	{
	case SoundManager::SystemSE::Tstrat:
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(SoundManager::SystemSE::Tstrat)]), SpeakerKind::bTitle });	// スピーカー生成
		m_pSpeakerList.back()->m_Speaker->SetVolume(TSTRAT_VOL);	// 音量設定
		break;
	case SoundManager::SystemSE::Gstart:
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(SoundManager::SystemSE::Gstart)]), SpeakerKind::bGstart });	// スピーカー生成
		m_pSpeakerList.back()->m_Speaker->SetVolume(GSTRAT_VOL);	// 音量設定
		break;
	case SoundManager::SystemSE::Pause:
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(SoundManager::SystemSE::Pause)]), SpeakerKind::bPause });	// スピーカー生成
		m_pSpeakerList.back()->m_Speaker->SetVolume(PAUSE_VOL);	// 音量設定
		break;
	case SoundManager::SystemSE::PauseClose:
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(SoundManager::SystemSE::PauseClose)]), SpeakerKind::bPauseClose });	// スピーカー生成
		m_pSpeakerList.back()->m_Speaker->SetVolume(PAUSE_CLOSE_VOL);	// 音量設定
		break;
	case SoundManager::SystemSE::TimeOver:
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(SoundManager::SystemSE::TimeOver)]), SpeakerKind::bTimeOver });	// スピーカー生成
		m_pSpeakerList.back()->m_Speaker->SetVolume(TIME_OVER_VOL);	// 音量設定
		break;
	case SoundManager::SystemSE::Select:
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(SoundManager::SystemSE::Select)]), SpeakerKind::bSelect });	// スピーカー生成
		m_pSpeakerList.back()->m_Speaker->SetVolume(SELECT_VOL);	// 音量設定
		break;
	case SoundManager::SystemSE::Decision:
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(SoundManager::SystemSE::Decision)]), SpeakerKind::bDecision });	// スピーカー生成
		m_pSpeakerList.back()->m_Speaker->SetVolume(DECSION_VOL);	// 音量設定
		break;
	}
}


// ネジSE再生
void SoundManager::playSound(ScrewSE kind)
{
	switch (kind)
	{
	case SoundManager::ScrewSE::Spin:
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(SoundManager::ScrewSE::Spin)]), SpeakerKind::bSpin });	// スピーカー生成
		m_pSpeakerList.back()->m_Speaker->SetVolume(SPIN_VOL);	// 音量設定
		break;
	case SoundManager::ScrewSE::SpinMax:
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(SoundManager::ScrewSE::SpinMax)]), SpeakerKind::bSpinMax });	// スピーカー生成
		m_pSpeakerList.back()->m_Speaker->SetVolume(SPIN_MAX_VOL);	// 音量設定
		break;
	}
}

// SEが再生中か確認(再生してなかったらtrue)
bool SoundManager::CheckSoundEnd(ScrewSE kind)
{
	for (Speaker* pSpeaker : m_pSpeakerList)
	{
		switch (kind)
		{
		case SoundManager::ScrewSE::Spin:
			if (pSpeaker->m_Kind == bSpin) return false;
			break;
		case SoundManager::ScrewSE::SpinMax:
			if (pSpeaker->m_Kind == bSpinMax) return false;
			break;
		}
	}

	return true;
}

// 再生されているかを返す
//bool SoundManager::GetPlayingState(BGM kind)
//{
//	for (auto it = m_pSpeakerList.begin(); it != m_pSpeakerList.end(); it++)
//	{
//		switch (kind)
//		{
//		case SoundManager::BGM::Clear:
//			if ((*it)->m_Kind == BGM::Clear)
//			{
//				// 再生中
//				return true;
//			}
//			break;
//		}
//	}
//	// 再生してない
//	return false;
//}


//bool SoundManager::CheckSoundEnd(GetSE kind)
//{
//	for (Speaker* pSpeaker : m_pSpeakerList)
//	{
//		switch (kind)
//		{
//		case SoundManager::GetSE::fruits:
//			if (pSpeaker->m_Kind == bFruits) return false;
//			break;
//		}
//	}
//
//	return true;
//}


//// ========== BGM再生停止 ==========
//// 引　数：
//// BGM 停止したいBGM番号
//// 戻り値：なし
//// 指定のBGMの再生を停止し、スピーカーを破棄する
//// ==========================================
//void SoundManager::StopSound(BGM kind)
//{
//	bool flg = false;	// 再生中
//
//	for (auto it = m_pSpeakerList.begin(); it != m_pSpeakerList.end(); it++)	// 全再生中SEの中から指定のSEを探す
//	{
//		switch (kind)
//		{
//		case SoundManager::BGM::title:
//			if ((*it)->m_Kind == bTitle) flg = true;
//			break;
//		case SoundManager::BGM::game:
//			if ((*it)->m_Kind == bGame) flg = true;
//			break;
//		case SoundManager::clear:
//			if ((*it)->m_Kind == bClear) flg = true;
//			break;
//		}
//
//		if (flg)	// 再生中の指定SEを見つけたらそれを破棄
//		{
//			(*it)->m_Speaker->Stop();
//			(*it)->m_Speaker->DestroyVoice();
//			delete (*it);
//			m_pSpeakerList.erase(it);
//			break;
//		}
//	}
//}
//
//void SoundManager::StopSound(SystemSE kind)
//{
//	bool flg = false;	// 再生中
//	for (auto it = m_pSpeakerList.begin(); it != m_pSpeakerList.end(); it++)
//	{
//		//switch (kind)
//		//{
//		//case SoundManager::SystemSE::Fpon:
//		//	if ((*it)->m_Kind == sFpon) flg = true;
//		//	break;
//		//}
//		if (flg)	// 再生中の指定SEを見つけたらそれを破棄
//		{
//			(*it)->m_Speaker->Stop();
//			(*it)->m_Speaker->DestroyVoice();
//			delete (*it);
//			m_pSpeakerList.erase(it);
//			break;
//		}
//	}
//}