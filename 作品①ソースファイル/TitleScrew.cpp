//////////////////////////////
//
// タイトルメッセージ
//
//////////////////////////////

// インクルード部
#include "TitleScrew.h"
#include "Input.h"

// マネージャー
#include "SoundManager.h"	// サウンドマネージャー

// コンストラクタ
TitleScrew::TitleScrew(std::string name)
	: GameObject(name)
{
	// コンポーネント追加
	AddComponent<ModelRenderer2D>();
	AddComponent<Move>();
	AddComponent<Move2DAnimation>();
	AddComponent<SpinAnimation>();

	// コンポーネント取得
	_modelRenderer2D = GetComponent<ModelRenderer2D>();
	_move = GetComponent<Move>();
	_move2DAnimation = GetComponent<Move2DAnimation>();
	_spinAnimation = GetComponent<SpinAnimation>();

	// 初期化
	m_TargetPos = float3(0.0f, 0.0f, 0.0f);
	m_SpinMaxPlayingSE = SoundState::CanPlay;

	// 値セット
	_move->SetMove(0.4f);
}

// デストラクタ
TitleScrew::~TitleScrew()
{
}

// 更新処理
void TitleScrew::Update()
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

		// ネジ回転
		ScrewSpin();

		return;
	}

	// 回転アニメーション中の処理
	ApplyRotationSettings();
}

// ネジを回す処理
void TitleScrew::ScrewSpin()
{
	// ネジを締める処理
	if (IsKeyPress('E') &&
		m_SpinMaxPlayingSE != SoundState::NotPlayMaxSE)
	{
		// 再生終了フラグを取得
		bool PlayEnd = SoundManager::GetInstance().CheckSoundEnd(SoundManager::ScrewSE::SpinMax);

		// 新しい移動範囲
		DirectX::XMFLOAT2 newMinPos = _move2DAnimation->GetMinPos();
		DirectX::XMFLOAT2 newMaxPos = _move2DAnimation->GetMaxPos();

		// 移動量
		DirectX::XMFLOAT3 movePos;

		// データ型を変換(計算しやすいように)
		float3 pos = float3::Tofloat3(m_pos);

		// ターゲット座標 - 現在の座標
		float3 N = m_TargetPos - pos;

		// ターゲット座標までの距離を計算
		float distance = float3::distance(m_TargetPos, pos);

		// 一定以下なら処理しない
		if (distance <= 5.0f)
		{
			// 最大まで回したSE
			SoundManager::GetInstance().playSound(SoundManager::ScrewSE::SpinMax);

			// 最大まで締めたSEを再生できない状態にする
			m_SpinMaxPlayingSE = SoundState::NotPlayMaxSE;
			return;
		}

		// 方向を正規化
		N = N.normalize();

		// 移動処理
		_move->DiagonalMove(N);

		// 新しい移動範囲を計算
		movePos = float3::ToXMFLOAT3(N * _move->GetMove());

		newMinPos.y += movePos.y;
		newMaxPos.y += movePos.y;

		// 移動範囲設定
		_move2DAnimation->SetMoveArea(newMinPos, newMaxPos);

		// 再生終了してるか確認
		PlayEnd = SoundManager::GetInstance().CheckSoundEnd(SoundManager::ScrewSE::Spin);

		// 再生終了していたら
		if (PlayEnd)
		{
			// 回転SE
			SoundManager::GetInstance().playSound(SoundManager::ScrewSE::Spin);
		}

		// 両方再生できる状態にする
		m_SpinMaxPlayingSE = SoundState::CanPlay;
	}
	// ネジを緩める
	else if (IsKeyPress('Q') &&
		m_SpinMaxPlayingSE != SoundState::NotPlayMinSE)
	{
		// 再生終了フラグを取得
		bool PlayEnd = SoundManager::GetInstance().CheckSoundEnd(SoundManager::ScrewSE::SpinMax);

		// 新しい移動範囲
		DirectX::XMFLOAT2 newMinPos = _move2DAnimation->GetMinPos();
		DirectX::XMFLOAT2 newMaxPos = _move2DAnimation->GetMaxPos();

		// 移動量
		DirectX::XMFLOAT3 movePos;

		// データ型を変換(計算しやすいように)
		float3 pos = float3::Tofloat3(m_pos);

		// ターゲット座標 - 現在の座標
		float3 N = m_TargetPos - pos;

		// ターゲット座標までの距離を計算
		float distance = float3::distance(m_TargetPos, pos);

		// 一定以下なら処理しない
		if (distance >= 20.0f)
		{
			// 最大まで回したSE
			SoundManager::GetInstance().playSound(SoundManager::ScrewSE::SpinMax);

			// 最大まで緩めたSEを再生できない状態にする
			m_SpinMaxPlayingSE = SoundState::NotPlayMinSE;
			return;
		}

		// 方向を正規化
		N = N.normalize() * -1.0f;

		// 移動処理
		_move->UPMove(false);

		// 新しい移動範囲を計算
		movePos = float3::ToXMFLOAT3(N * _move->GetMove());

		newMinPos.y += movePos.y;
		newMaxPos.y += movePos.y;

		// 移動範囲設定
		_move2DAnimation->SetMoveArea(newMinPos, newMaxPos);

		// 再生終了してるか確認
		PlayEnd = SoundManager::GetInstance().CheckSoundEnd(SoundManager::ScrewSE::Spin);

		// 再生終了していたら
		if (PlayEnd)
		{
			// 回転SE
			SoundManager::GetInstance().playSound(SoundManager::ScrewSE::Spin);
		}

		// 両方再生できる状態にする
		m_SpinMaxPlayingSE = SoundState::CanPlay;
	}
}

// アニメーションスピード設定
void TitleScrew::SetAnimationSpeed(DirectX::XMFLOAT2 speed)
{
	m_AnimationSpeed = speed;
}

// ネジが締めたときに向かう位置を設定
void TitleScrew::SetTargetPos(DirectX::XMFLOAT3 pos)
{
	m_TargetPos = float3::Tofloat3(pos);
}

// 回転アニメーション中にやる処理
void TitleScrew::ApplyRotationSettings()
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
