// プレイヤークラス

// インクルードガード
#ifndef __PLAYER_H__
#define __PLAYER_H__

// インクルード部
#include "GameObject.hpp"

// コンポーネント
#include "Move.h"				// 移動
#include "Jump.h"				// ジャンプ
#include "BoxCollider.h"		// 当たり判定
#include "Scanner.h"			// オブジェクトスキャナ
#include "ModelRenderer3D.h"	// 3D描画
#include "ScaleAnimation.h"		// スケールアニメーション

// クラス定義
class Player : public GameObject
{
public:
	Player(std::string name = "Player");// コンストラクタ
	~Player();							// デストラクタ

	// 初期状態に戻す
	void ResetState();

	void Update();						// 更新処理

	void OnCollision(GameObject* obj);	// 当たったオブジェクトのあとの処理
	void OnScanner(GameObject* obj);	// 検知したオブジェクトのあとの処理

	void MoveAfterGoal(GameObject* obj);// ゴール後の移動処理

private:
	void InputCheck();					// 入力されているキーをチェック
	void Rotate();						// プレイヤー回転

protected:
	//----コンポーネント----

	// 移動コンポーネント
	Move* _move;

	// ジャンプコンポーネント
	Jump* _jump;

	// ボックスコライダーコンポーネント
	BoxCollider* _boxCollider;

	// オブジェクトスキャナコンポーネント
	Scanner* _scanner;

	// 3Dモデルレンダラー
	ModelRenderer3D* _modelRenderer3D;

	// スケールアニメーションコンポーネント
	ScaleAnimation* _scaleAnimation;


	//----変数----

	// リセット位置
	DirectX::XMFLOAT3 m_ResetPos;

	// 回転経過時間
	float m_SpinTime;

	// ジャンプ可能フラグ
	bool m_Jump;
};

#endif // __PLAYER_H__