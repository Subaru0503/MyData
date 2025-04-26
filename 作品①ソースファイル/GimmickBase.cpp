// ギミック基底クラス

// インクルード部
#include "GimmickBase.h"

// システム
#include "Input.h"

// コンストラクタ
GimmickBase::GimmickBase(std::string name)
	: GameObject(name)
	, m_PairGimmick(nullptr)
	, m_invertEffectFlg(false)
	, m_CollisionUpdate(false)
	, m_GroundCollision(false)
{
	m_tag = "Gimmick";

	// コンポーネント追加
	AddComponent<BoxCollider>();		// 当たり判定
	AddComponent<ModelRenderer3D>();	// 3D描画

	// コンポーネント取得
	_boxCollider = GetComponent<BoxCollider>();
	_modelRenderer3D = GetComponent<ModelRenderer3D>();

	// シェーダーセット
	const char* file[] = {
		"VS_Object",
		"PS_TexColor",
	};

	_modelRenderer3D->SetShader(file);
}

// デストラクタ
GimmickBase::~GimmickBase()
{
}

// 更新処理
void GimmickBase::Update()
{
	for (int i = 0; i < m_TargetScrew.size(); i++)
	{
		// 現在の角度取得
		float rotY;
		DirectX::XMVECTOR qRotate = DirectX::XMLoadFloat4(&m_TargetScrew[i]->GetQuat());
		DirectX::XMMATRIX quaternionM = DirectX::XMMatrixRotationQuaternion(qRotate);
		// Yaw (Y軸回転)
		rotY = DirectX::XMConvertToDegrees(atan2(quaternionM.r[0].m128_f32[2], quaternionM.r[2].m128_f32[2]));


		// 変わってなかったら処理をしない
		// プレイヤーが回転をさせてなかったら処理しない
		if (m_OldRotY[i] == rotY) continue;

		// 効果反転フラグが下がっていたら
		// 過去角度より値が小さくなっていたらd
		if ((m_OldRotY[i] < rotY && !m_invertEffectFlg) ||
			(m_OldRotY[i] > rotY && m_invertEffectFlg))
		{
			float rot = abs(rotY - m_OldRotY[i]);
			// ギミック処理
			Gimmick(i, rot);
		}
		else
		{
			float rot = abs(rotY - m_OldRotY[i]);

			InvertGimmick(i, rot);
		}

		m_OldRotY[i] = rotY;	// 角度情報更新
	}


	m_CollisionUpdate = false;
}

// ターゲットオブジェクト処理
void GimmickBase::Gimmick(int index, float rotY)
{
}

// 通常のネジを回す方向と逆方向に回されたときに呼ぶ
void GimmickBase::InvertGimmick(int index, float rotY)
{
}

 // 衝突したオブジェクト
void GimmickBase::OnCollision(GameObject* obj)
{
	// 当たってなかったら処理しない
	if (!obj)
	{
		// フラグリセット
		m_GroundCollision = false;
		return;
	}
	string tag = obj->GetTag();
	if (tag == "Ground")
	{
		m_GroundCollision = true;
		m_CollisionUpdate = true;
	}
	else if(!m_CollisionUpdate)
	{
		// フラグリセット
		m_GroundCollision = false;
	}
}