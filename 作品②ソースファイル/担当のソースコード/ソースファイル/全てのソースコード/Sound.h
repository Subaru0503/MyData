/*
InitSound関数をLoadTexture関数より後に呼び出すとエラー
※内部でCOMオブジェクトを利用するため

リスナー
 音を聞くための「耳」に相当。3Dサウンド(音の方向・距離減衰有り)で必要。２Dではいらない。内部でやってくれるらしい
ソース
 音を発する「音源」に相当。スピーカー。XAudio2ではVoiceと呼ばれる。
バッファ
 音データを格納しておくバッファ。WAVファイル、OGGファイルなどからロード。
 */
#ifndef __SOUND_H__
#define __SOUND_H__

#include <xaudio2.h>

#pragma comment(lib, "xaudio2.lib")

//----------
// プロトタイプ宣言
//----------
HRESULT InitSound(void);
void UninitSound(void);

// サウンドの読み込み
XAUDIO2_BUFFER* LoadSound(const char *file, bool loop = false);
// サウンドの再生
#undef PlaySound
IXAudio2SourceVoice* PlaySound(XAUDIO2_BUFFER* pSound);

#endif // __SOUND_H__