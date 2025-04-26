///////////////////////////////////////
//
// ネジ基底クラス
//
///////////////////////////////////////

// インクルード部
#include "Screw.h"

//----マネージャー----
#include "SoundManager.h"	// サウンドマネージャー

// コンストラクタ
Screw::Screw(std::string name)
	: GameObject(name)
	, m_Multiplier(1)
	, m_SpinFlg(false)
	, m_SpinMaxPlayingSE(false)
{

	// タグ設定
	m_tag = "Screw";

	// メンバ変数初期化
	m_Nut = nullptr;

	//----コンポーネント追加----

	// 移動
	AddComponent<Move>();

	// 回転
	AddComponent<Spin>();

	// 当たり判定
	AddComponent<BoxCollider>();

	// 3D描画
	AddComponent<ModelRenderer3D>();

	//----コンポーネント取得----

	// 移動
	_move = GetComponent<Move>();

	// 回転
	_spin = GetComponent<Spin>();

	// 当たり判定
	_boxCollider = GetComponent<BoxCollider>();

	// 3D描画
	_modelRenderer3D = GetComponent<ModelRenderer3D>();

	// シェーダーファイル
	const char* file[] = {
		"VS_Object",
		"PS_TexColor",
	};

	// シェーダーセット
	_modelRenderer3D->SetShader(file);
	
	// 値セット
	_boxCollider->SetScale(float3(0.4f, 0.4f, 0.4f));
}

// デストラクタ
Screw::~Screw()
{
}

// 更新処理
void Screw::Update()
{

}

// 初期状態に戻す
// オブジェクトをシーンが始まったときの状態に戻す
void Screw::ResetState()
{
	// 初期座標に戻す
	m_pos = m_InitPos;

	// 角度初期化
	m_quat = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
}

// 回転関数
void Screw::ObjRightSpin(bool Right)
{
	//----変数宣言----

	// 再生終了フラグ
	bool PlayEnd;

	// 実態確認
	if (!m_Nut)
	{
		MessageBox(NULL, "ナットの設定がされてない", "Screw.cpp", MB_OK);
	}

	// 回転フラグ上げ
	m_SpinFlg = true;

	// 再生終了フラグを取得
	PlayEnd = SoundManager::GetInstance().CheckSoundEnd(SoundManager::ScrewSE::Spin);

	// 右回転
	if (m_Nut->GetPos().y <= m_pos.y && Right)
	{
		// Y軸右回転
		_spin->YSpin();

		// 移動量セット
		_move->SetMove(_spin->GetScrewTravel());

		// 下方向移動
		_move->UPMove(false);
		
		// 再生してなかったら
		if (PlayEnd)
		{
			// 回転SE
			SoundManager::GetInstance().playSound(SoundManager::ScrewSE::Spin);
		}

		// 回し切ったSE再生済フラグを下げる
		m_SpinMaxPlayingSE = false;
	}
	// 左回転
	else if(m_Nut->GetPos().y + 0.5f >= m_pos.y && !Right)
	{
		// Y軸左回転
		_spin->YSpin(false);

		// 移動量セット
		_move->SetMove(_spin->GetScrewTravel());

		// 上方向移動
		_move->UPMove();

		// 再生してなかったら
		if (PlayEnd)
		{
			// 回転SE
			SoundManager::GetInstance().playSound(SoundManager::ScrewSE::Spin);
		}

		// 回し切ったSE再生済フラグを下げる
		m_SpinMaxPlayingSE = false;
	}
	// 再生フラグが下がってたら
	else if (!m_SpinMaxPlayingSE)
	{
		// 最大まで回したSE
		SoundManager::GetInstance().playSound(SoundManager::ScrewSE::SpinMax);

		// 回し切ったSE再生済フラグを上げる
		m_SpinMaxPlayingSE = true;
	}
}
