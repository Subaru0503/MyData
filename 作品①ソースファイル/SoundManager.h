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
#include <string>

// ========== クラス ==========
class SoundManager
{
public:	// 列挙型 外部呼出し用
	// BGM種類
	enum BGM {
		Title,
		Stage,
		Clear,
	};

	//----SE----
	// システム音
	enum SystemSE {
		Tstrat,			// ゲーム開始(タイトル)
		Gstart,			// ゲームスタート
		Pause,			// ポーズ画面を開く
		PauseClose,		// ポーズ画面を閉じる
		TimeOver,		// 時間切れ
		Select,			// 選択
		Decision,		// 決定
	};

	// ネジ音
	enum ScrewSE {
		Spin,			// ネジ回転
		SpinMax,		// ネジを最大まで回した
	};
public:	// 関数
	inline static SoundManager& GetInstance()
	{
		static SoundManager instance;
		return instance;
	}
	void DeleteSpeaker();							// 再生終了したSEスピーカーを削除
	void AllDeleteSpeaker();						// 再生中のスピーカーを全削除

	// BGM,SE読み込み
	void SoundLoad();

	//----再生----
	// BGM再生
	void playSound(BGM kind);						// BGM

	// SE再生
	void playSound(SystemSE kind);					// システム音
	void playSound(ScrewSE kind);					// ネジ音
	//----再生停止----
	// BGM停止
	//void StopSound(BGM kind);						// BGM

	// SE停止
	//void StopSound(SystemSE kind);				// システム音SE再生停止

	// SEが再生中か確認
	bool CheckSoundEnd(ScrewSE kind);

private: // 列挙型　内部処理用

	SoundManager()
	{
		InitSound();
	};
	~SoundManager();

	// 音の種類
	enum SpeakerKind
	{
		//----BGM----
		bTitle,			// タイトル
		bGame,			// ゲーム
		bClear,			// ゲームクリア
		//----SE----
		bTstrat,		// ゲーム開始(タイトル)
		bGstart,		// ゲームスタート
		bPause,			// ポーズ画面を開く
		bPauseClose,	// ポーズ画面を閉じる
		bTimeOver,		// 時間切れ
		bSelect,		// 選択
		bDecision,		// 決定
		bSpin,			// ネジ回転
		bSpinMax,		// ネジを最大まで回した
	};

	typedef struct		// スピーカー
	{
		IXAudio2SourceVoice*	m_Speaker;		// スピーカー
		SpeakerKind				m_Kind;			// スピーカーの種類
	}Speaker;

private:

	std::map<std::string, XAUDIO2_BUFFER*> m_pSoundMap;	// 音源用map
	std::list<Speaker*> m_pSpeakerList;					// スピーカー用list
};
#endif // !__SOUND_MANAGER_H__