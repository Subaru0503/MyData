//////////////////////////////
//
// タイトルメッセージ
//
//////////////////////////////

// インクルード部
#include "Title.h"
#include "Input.h"

// マネージャー
#include "ShaderManager.h"	// シェーダーマネージャー
#include "SoundManager.h"	// サウンドマネージャー

// コンストラクタ
Title::Title(std::string name)
	: GameObject(name)
{
	// コンポーネント追加
	AddComponent<ModelRenderer2D>();
	AddComponent<Move2DAnimation>();
	AddComponent<SpinAnimation>();

	// コンポーネント取得
	_modelRenderer2D = GetComponent<ModelRenderer2D>();
	_move2DAnimation = GetComponent<Move2DAnimation>();
	_spinAnimation = GetComponent<SpinAnimation>();
}

// デストラクタ
Title::~Title()
{
}

// 更新処理
void Title::Update()
{
	DirectX::XMFLOAT2 speed = _move2DAnimation->GetSpeed();

	// 回転アニメーションが終わってたら
	if (_spinAnimation->GetStop())
	{
		// 移動スピードが変わってなかったら変える
		if (speed.y != m_AnimationSpeed.y)
		{
			speed = m_AnimationSpeed;
			_move2DAnimation->SetSpeed(speed);
		}
		return;
	}

	// 回転アニメーション中の処理
	ApplyRotationSettings();
}

// アニメーションスピード設定
void Title::SetAnimationSpeed(DirectX::XMFLOAT2 speed)
{
	m_AnimationSpeed = speed;
}

// 回転アニメーション中にやる処理
void Title::ApplyRotationSettings()
{
	// 現在の回転数取得
	float spin = _spinAnimation->GetCurrentSpinNum();
	// 設定した回転数取得
	float spinNum = _spinAnimation->GetSpinNum();
	// 再生状況取得(trueなら再生してない)
	bool PlayEnd = SoundManager::GetInstance().CheckSoundEnd(SoundManager::ScrewSE::Spin);

	// 回転中で再生中じゃないとき
	if (spin < spinNum && PlayEnd)
	{
		// 回転SE再生
		SoundManager::GetInstance().playSound(SoundManager::ScrewSE::Spin);
	}
}
