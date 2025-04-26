// インクルード部
#include "Player.h"

// システム
#include "Input.h"

// コンポーネント
#include "Gravity.h"

// オブジェクト
#include "Screw.h"

// 定数・マクロ定義
#define DEFAULT_SPEED (0.1f)	// 通常スピード
#define DIAGONAL_SPEED (0.07f)	// 斜めスピード

// コンストラクタ
Player::Player(std::string name)
	: GameObject(name)
	, m_ResetPos{0.0f, 2.0, 0.0f}
	, m_SpinTime(0.0f)
	, m_Jump(false)
{
	// タグ設定
	m_tag = "Player";

	m_pCollisionObj = nullptr;

	// コンポーネント追加。
	AddComponent<Gravity>();			// 重力
	AddComponent<Move>();				// 移動
	AddComponent<Jump>();				// ジャンプ
	//AddComponent<Spin>();				// 回転
	AddComponent<BoxCollider>();		// 当たり判定
	AddComponent<Scanner>();			// オブジェクトスキャナ
	AddComponent<ModelRenderer3D>();	// 3D描画
	AddComponent<ScaleAnimation>();		// スケールアニメーション

	// コンポーネント取得
	_move = GetComponent<Move>();
	_jump = GetComponent<Jump>();
	//_spin = GetComponent<Spin>();
	_boxCollider = GetComponent<BoxCollider>();
	_scanner = GetComponent<Scanner>();
	_modelRenderer3D = GetComponent<ModelRenderer3D>();
	_scaleAnimation = GetComponent<ScaleAnimation>();

	// シェーダーセット
	const char* file[] = {
		"VS_Object",
		"PS_TexColor",
	};

	_modelRenderer3D->SetShader(file);

	// 値セット
	m_quat = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	_move->SetMove(DEFAULT_SPEED);
	_scanner->SetScale(float3(0.8f, 0.5f, 0.8f));
	_scaleAnimation->SetScaleRange(0.15f);
	_scaleAnimation->SetMinScale(0.85f);

}

// デストラクタ
Player::~Player()
{

}

// 初期状態に戻す
void Player::ResetState()
{
	if (m_ResetPos.x == 0.0f &&
		m_ResetPos.y == 0.0f &&
		m_ResetPos.z == 0.0f)
	{
		return;
	}
	// 座標リセット
	m_pos = m_ResetPos;
}

// 更新処理
void Player::Update()
{

	// 入力されてるキーの数をチェック
	InputCheck();

	// 移動処理
	if (IsKeyPress('W'))
	{
		_move->FrontMove();
	}
	if (IsKeyPress('S'))
	{
		_move->FrontMove(false);
	}
	if (IsKeyPress('A'))
	{
		_move->RightMove(false);
	}
	if (IsKeyPress('D'))
	{
		_move->RightMove(); 
	}

	// ジャンプ
	if (!m_Jump && IsKeyTrigger(VK_SPACE))
	{
		_jump->SetJump();
		m_Jump = true;
	}

	// プレイヤー回転
	//Rotate();

	// ネジが近くにあるか
	if (!m_pCollisionObj)
		return;

	// ネジクラスにダウンキャスト
	Screw* screw = dynamic_cast<Screw*>(m_pCollisionObj);

	// 回転処理
	if (IsKeyPress('E'))
	{
		screw->ObjRightSpin();		// 右回転
	}
	// 左回転
	else if (IsKeyPress('Q'))
	{
		screw->ObjRightSpin(false);	// 左回転
	}
	else
	{
		screw->ResetTime();			// 経過時間リセット
	}

	// 初期化
	m_pCollisionObj = nullptr;
}

// ネジの付近にいるか判定チェック
void Player::OnScanner(GameObject* obj)
{
	// 実体なし
	if (!obj)
	{
		m_pCollisionObj = nullptr;
		return;
	}

	// タグ取得
	string tag = obj->GetTag();
	// ネジなら実体取得
	if (tag == "Screw")
	{
		// オブジェクトセット
		m_pCollisionObj = obj;
	}
	else if (tag == "PlayerCheckPoint")
	{
		// 座標設定
		m_ResetPos = obj->GetPos();
	}

}

// 当たり判定判定チェック
void Player::OnCollision(GameObject* obj)
{
	if (!obj)
	{
		m_Jump = true;
		return;
	}

	// タグ取得
	string tag = obj->GetTag();
	if (_jump->GetJump() && (tag == "Ground" || tag == "Gimmick" || tag == "MoveGimmick" || tag == "CheckPointPath"))
	{
		m_Jump = false;	// ジャンプフラグを下げる
	}
}

// ゴール後の移動処理
void Player::MoveAfterGoal(GameObject* obj)
{
	//_move->FrontMove(false);

	// データ型を変換(計算しやすいように)
	float3 pos = float3::Tofloat3(m_pos);
	float3 goalPos = float3::Tofloat3(obj->GetPos());

	// プレイヤーの高さに合わせる
	goalPos.y = pos.y;

	// 次のチェックポイント - 現在の座標
	float3 N = goalPos - pos;

	// 方向を正規化
	N = N.normalize();

	// 移動処理
	_move->DiagonalMove(N);
}

// 入力されているキーをチェック
void Player::InputCheck()
{
	int count = 0;

	// 何個押されてるか確認
	if (IsKeyPress('W'))
	{
		count++;
	}
	if (IsKeyPress('S'))
	{
		count++;
	}
	if (IsKeyPress('A'))
	{
		count++;
	}
	if (IsKeyPress('D'))
	{
		count++;
	}

	// 2つ以上押されてたら移動速度を下げる
	if (count >= 2)
	{
		_move->SetMove(DIAGONAL_SPEED);
	}
	else
	{
		_move->SetMove(DEFAULT_SPEED);
	}
}

// プレイヤー回転
void Player::Rotate()
{
	DirectX::XMFLOAT3 move = m_pos;
	move.x -= m_oldpos.x;
	move.y -= m_oldpos.y;
	move.z -= m_oldpos.z;

	//---プレイヤーの回転角度を計算
	float rotationAngle = atan2(-move.x, -move.z);

	//---プレイヤーの回転行列を更新
	//m_DirectRad = rotationAngle;

	
	// 回転取得
	//DirectX::XMVECTOR qRotate = DirectX::XMLoadFloat4(&m_quat);
	//
	//DirectX::XMMATRIX RotMat = DirectX::XMMatrixRotationQuaternion(qRotate);
	//
	//// 軸に合わせて回転
	//DirectX::XMVECTOR quat = DirectX::XMQuaternionRotationAxis(
	//	DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), DirectX::XMConvertToRadians(m_DirectRad)
	//);
	//
	//// クォータニオン掛け算
	//qRotate = DirectX::XMQuaternionMultiply(qRotate, quat);
	//
	//// 角度更新
	//DirectX::XMStoreFloat4(&m_quat, qRotate);
}

