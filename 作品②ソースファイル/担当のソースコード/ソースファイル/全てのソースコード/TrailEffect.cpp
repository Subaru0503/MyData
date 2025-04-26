#include "TrailEffect.h"
#include "Player.h"


TrailEffect::TrailEffect(Object* pObject)
	: m_pObject(pObject)
{
//	m_oldPos = m_pObject->GetPos();
}

TrailEffect::~TrailEffect()
{
}

void TrailEffect::Init()
{
	m_oldPos = m_pObject->GetPos();
}

void TrailEffect::UpdateControlPoints(LineID id, ControlPoints & controlPoints)
{
	//毎フレーム、ポリラインの幅を少しずつ小さくする
	ControlPoints::iterator it = controlPoints.begin();
	while (it != controlPoints.end())
	{
		it->bold *= 0.9f;
		it->color.x *= 0.9f;
		it->color.y *= 0.9f;
//		it->color.z *= 0.9f;
		++it;
	}

	//プレイヤーが移動しているか確認
	float distance = 0.0f;
	DirectX::XMFLOAT3 pos = m_pObject->GetPos();
	DirectX::XMVECTOR vOld = DirectX::XMLoadFloat3(&m_oldPos);
	DirectX::XMVECTOR vNow = DirectX::XMLoadFloat3(&pos);
	DirectX::XMVECTOR vDir = DirectX::XMVectorSubtract(vNow, vOld);
	DirectX::XMStoreFloat(&distance, DirectX::XMVector3Length(vDir));

	if (distance >= 0.2f)
	{
		//1つずつずらす
		for (int i = controlPoints.size() - 1; i > 0; --i)
		{
			controlPoints[i] = controlPoints[i - 1];
		}
		//先頭に新しいデータを設定
		controlPoints[0].pos = pos;
		controlPoints[0].pos.y += 0.1f;
		controlPoints[0].bold = 0.3f;
		controlPoints[0].color = { 1.0f,1.0f,1.0f,1.0f };

		//プレイヤーの前の位置を更新
		m_oldPos = pos;
	}
}

void TrailEffect::SetOldPos(DirectX::XMFLOAT3 oldPos)
{
	m_oldPos = oldPos;
}
