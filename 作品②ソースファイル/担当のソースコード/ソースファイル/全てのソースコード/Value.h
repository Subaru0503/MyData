// ===========================================
//
// いろんなパロメータのデファイン
// ※Define.hだとコンパイルに時間かかるのでこっちに移動しました。
//
// ===========================================

#ifndef __VALUE_H__
#define __VALUE_H__

// 各ステージの地面の高さ
#define STAGE1_HT0	(0.0f)	// ステージ１　地面の高さ
#define STAGE1_HT1	(1.0f)
#define STAGE1_HT2	(2.0f)
#define STAGE2_HT0	(0.0f)	// ステージ2　地面の高さ
#define STAGE2_HT1	(1.0f)
#define STAGE2_HT2	(2.0f)
#define STAGE3_HT0	(0.0f)	// ステージ3　地面の高さ
#define STAGE3_HT1	(3.0f)
#define STAGE3_HT2	(4.0f)

// オブジェクト情報
#define MAX_CUSTOM			(6)		// カスタム最大数
#define MAX_ITEM			(4)		// アイテム最大数

// ゲーム情報
#define MAX_TIME			(300)	// 制限時間(秒)
#define WAIT_SCENE_SWAP		(240)	// ゲーム終了からシーン遷移までの猶予時間(秒)	
#define ENDUNG_WAIT_TIME	(520)	// リザルト表示からエンディング再生までの猶予

// デバッグ用
#define DEBUG_KEY	(0)		// デバッグコマンド（１：有効　０：無効）



#endif // !__VALUE_H__
