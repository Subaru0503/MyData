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
	//���t���[���A�|�����C���̕�������������������
	ControlPoints::iterator it = controlPoints.begin();
	while (it != controlPoints.end())
	{
		it->bold *= 0.9f;
		it->color.x *= 0.9f;
		it->color.y *= 0.9f;
//		it->color.z *= 0.9f;
		++it;
	}

	//�v���C���[���ړ����Ă��邩�m�F
	float distance = 0.0f;
	DirectX::XMFLOAT3 pos = m_pObject->GetPos();
	DirectX::XMVECTOR vOld = DirectX::XMLoadFloat3(&m_oldPos);
	DirectX::XMVECTOR vNow = DirectX::XMLoadFloat3(&pos);
	DirectX::XMVECTOR vDir = DirectX::XMVectorSubtract(vNow, vOld);
	DirectX::XMStoreFloat(&distance, DirectX::XMVector3Length(vDir));

	if (distance >= 0.2f)
	{
		//1�����炷
		for (int i = controlPoints.size() - 1; i > 0; --i)
		{
			controlPoints[i] = controlPoints[i - 1];
		}
		//�擪�ɐV�����f�[�^��ݒ�
		controlPoints[0].pos = pos;
		controlPoints[0].pos.y += 0.1f;
		controlPoints[0].bold = 0.3f;
		controlPoints[0].color = { 1.0f,1.0f,1.0f,1.0f };

		//�v���C���[�̑O�̈ʒu���X�V
		m_oldPos = pos;
	}
}

void TrailEffect::SetOldPos(DirectX::XMFLOAT3 oldPos)
{
	m_oldPos = oldPos;
}
