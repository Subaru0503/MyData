//////////////////////////////
//
// スタート準備UI
//
//////////////////////////////

// インクルード部
#include "Ready.h"

// マネージャー
#include "ShaderManager.h"	// シェーダーマネージャー
#include "SoundManager.h"	// サウンドマネージャー

// 定数・マクロ定義
#define SPIN_NUM (5)			 // 回転数
#define DELTA_SPIN (30.0f)		 // 回転量
#define FIRST_DELAY_TIME (1.0f)  // アニメーション開始を遅らせる時間
#define SECOND_DELAY_TIME (0.1f) // 回転アニメーション～拡縮アニメーションまでの時間
#define THIRD_DELAY_TIME (0.1f)  // 拡縮アニメーション～ゲームスタートまでの時間

// コンストラクタ
Ready::Ready(std::string name)
	: GameObject(name)
{
	// コンポーネント追加
	AddComponent<ModelRenderer2D>();
	AddComponent<Move>();
	AddComponent<SpinAnimation>();

	// コンポーネント取得
	_modelRenderer2D = GetComponent<ModelRenderer2D>();
	_move = GetComponent<Move>();
	_spinAnimation = GetComponent<SpinAnimation>();

	// メンバ変数初期化
	_modelRenderer2D_param = _modelRenderer2D->GetParam();

	_modelRenderer2D->Load("Assets/Texture/Ready.png");

	// 値セット
	m_pos.x = 640.0f;
	m_pos.y = 120.0f;
	m_scale.x = 300.0f;
	m_scale.y = 200.0f;
	m_quat = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	animKind = AnimKind::Before;
	m_Delay = FIRST_DELAY_TIME;
	m_Start = false;
	m_ScaleAnimFlg = false;

	_move->SetMove(2.0f);
	// 回転軸設定
	DirectX::XMFLOAT4 axis = DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 0.0f);
	_spinAnimation->SetAxis(axis);
	_spinAnimation->SetDeltaRot(DELTA_SPIN);
	//_spinAnimation->SetSpinNum(SPIN_NUM);
}

// デストラクタ
Ready::~Ready()
{

}

// 更新処理
void Ready::Update()
{
	// アニメーション処理
	switch (animKind)
	{
	// 回転アニメーション前にやる処理
	case AnimKind::Before:
		BeforeSpinAnimation();
		break;
	// 移動アニメーション+テクスチャ変更
	case AnimKind::Change:
		MoveAndTextureChangeAnimation();
		break;
	// 拡縮アニメーション
	case AnimKind::Scale:
		ScaleAnimation();
		break;
	case AnimKind::Start:
		m_Start = true;
		_modelRenderer2D->SetDraw(false);
		animKind = AnimKind::None;
		break;
	}
}

// 回転移動アニメーション前にやる処理
void Ready::BeforeSpinAnimation()
{
	// ディレイ分経過処理
	if (m_Delay > 0.0f)
	{
		m_Delay -= 1.0f / 60.0f;
		// 0なら回転アニメーション開始
		if (m_Delay <= 0.0f)
		{
			m_Delay = 0.0f;
			_spinAnimation->SetSpinNum(SPIN_NUM);
			animKind = AnimKind::Change;	// 移動アニメーション+テクスチャ変更に移る
		}
	}
}

// 回転移動アニメーション+テクスチャ変更
void Ready::MoveAndTextureChangeAnimation()
{
	bool PlayEnd = SoundManager::GetInstance().CheckSoundEnd(SoundManager::ScrewSE::Spin);
	_move->UPMove();
	// ラスト一回転になったらテクスチャを変更する
	int spin = _spinAnimation->GetCurrentSpinNum();	// 現在の回転数取得
	if (spin == SPIN_NUM - 1)
	{
		_modelRenderer2D->Load("Assets/Texture/Go.png");
		animKind = AnimKind::Scale;	// 拡縮アニメーションに移る
		m_Delay = SECOND_DELAY_TIME;
	}

	if (PlayEnd)
	{
		// 回転SE
		SoundManager::GetInstance().playSound(SoundManager::ScrewSE::Spin);
	}
}

// 拡縮アニメーション
void Ready::ScaleAnimation()
{
	int rot = _spinAnimation->GetCurrentSpinNum();	// 現在の回転数取得
	if (!m_ScaleAnimFlg && m_Delay <= 0.0f && rot == SPIN_NUM)
	{
		m_scale.x += 40.0f;
		m_scale.y += 26.6f;
		if (m_scale.x >= 350.0f)
		{
			m_ScaleAnimFlg = true;
			m_Delay = THIRD_DELAY_TIME;
			// ゲームスタートSE
			SoundManager::GetInstance().playSound(SoundManager::SystemSE::Gstart);
		}
	}

	// ディレイ時間がなくなったら
	if (m_ScaleAnimFlg && m_Delay <= 0.0f)
	{
		m_Delay = 0.0f;
		// ゲームスタート
		animKind = AnimKind::Start;
	}

	if (rot == SPIN_NUM)
	{
		m_Delay -= 1.0f / 60.0f;
	}
}
