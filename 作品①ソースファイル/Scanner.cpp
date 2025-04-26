// �C���N���[�h��
#include "Scanner.h"

// �����蔻��R���|�[�l���g
#include "BoxCollider.h"

// �R���X�g���N�^
Scanner::Scanner()
	: m_Collision(false)
{
	m_Scale = float3(0.5f, 0.5f, 0.5f);
}

// obb���m�̓����蔻��`�F�b�N
bool Scanner::CheckObb(GameObject* objA, GameObject* objB)
{
	// �e�����x�N�g���̊m��
	float3 NAe1 = float3::Tofloat3(objA->GetRight()), Ae1 = NAe1 * m_Scale.x;
	float3 NAe2 = float3::Tofloat3(objA->GetUp()), Ae2 = NAe2 * m_Scale.y;
	float3 NAe3 = float3::Tofloat3(objA->GetFront()), Ae3 = NAe3 * m_Scale.z;
	float3 NBe1, Be1;
	float3 NBe2, Be2;
	float3 NBe3, Be3;
	float3 Interval;

	if (objB->GetComponent<BoxCollider>())
	{
		NBe1 = float3::Tofloat3(objB->GetRight()), Be1 = NBe1 * objB->GetComponent<BoxCollider>()->GetScale().x;
		NBe2 = float3::Tofloat3(objB->GetUp()), Be2 = NBe2 * objB->GetComponent<BoxCollider>()->GetScale().y;
		NBe3 = float3::Tofloat3(objB->GetFront()), Be3 = NBe3 * objB->GetComponent<BoxCollider>()->GetScale().z;
	}
	else
	{
		NBe1 = float3::Tofloat3(objB->GetRight()), Be1 = NBe1 * objB->GetScale().x;
		NBe2 = float3::Tofloat3(objB->GetUp()), Be2 = NBe2 * objB->GetScale().y;
		NBe3 = float3::Tofloat3(objB->GetFront()), Be3 = NBe3 * objB->GetScale().z;
	}

	if (objA->GetTag() == "Player")
	{
		DirectX::XMFLOAT3 posA = PlayerAdjust(objA);
		Interval = float3::Tofloat3(posA) - float3::Tofloat3(objB->GetPos());
	}
	else if (objB->GetTag() == "Player")
	{
		DirectX::XMFLOAT3 posB = PlayerAdjust(objB);
		Interval = float3::Tofloat3(objA->GetPos()) - float3::Tofloat3(posB);
	}
	else
	{
		Interval = float3::Tofloat3(objA->GetPos()) - float3::Tofloat3(objB->GetPos());
	}

	// ������ : Ae1
	float rA = Ae1.length();
	float rB = LenSegOnSeparateAxis(&NAe1, &Be1, &Be2, &Be3);
	float L = fabs(float3::dot(Interval, NAe1));
	if (L > rA + rB)
	{
		return false; // �Փ˂��Ă��Ȃ�
	}

	// ������ : Ae2
	rA = Ae2.length();
	rB = LenSegOnSeparateAxis(&NAe2, &Be1, &Be2, &Be3);
	L = fabs(float3::dot(Interval, NAe2));
	if (L > rA + rB)
	{
		return false;
	}

	// ������ : Ae3
	rA = Ae3.length();
	rB = LenSegOnSeparateAxis(&NAe3, &Be1, &Be2, &Be3);
	L = fabs(float3::dot(Interval, NAe3));
	if (L > rA + rB)
	{
		return false;
	}

	// ������ : Be1
	rA = LenSegOnSeparateAxis(&NBe1, &Ae1, &Ae2, &Ae3);
	rB = Be1.length();
	L = fabs(float3::dot(Interval, NBe1));
	if (L > rA + rB)
	{
		return false;
	}

	// ������ : Be2
	rA = LenSegOnSeparateAxis(&NBe2, &Ae1, &Ae2, &Ae3);
	rB = Be2.length();
	L = fabs(float3::dot(Interval, NBe2));
	if (L > rA + rB)
	{
		return false;
	}

	// ������ : Be3
	rA = LenSegOnSeparateAxis(&NBe3, &Ae1, &Ae2, &Ae3);
	rB = Be3.length();
	L = fabs(float3::dot(Interval, NBe3));
	if (L > rA + rB)
	{
		return false;
	}

	// ������ : C11
	float3 Cross;
	Cross = NAe1.cross(NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabs(float3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// ������ : C12
	Cross = NAe1.cross(NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabs(float3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// ������ : C13
	Cross = NAe1.cross(NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabs(float3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// ������ : C21
	Cross = NAe2.cross(NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabs(float3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// ������ : C22
	Cross = NAe2.cross(NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabs(float3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// ������ : C23
	Cross = NAe2.cross(NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabs(float3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// ������ : C31
	Cross = NAe3.cross(NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabs(float3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// ������ : C32
	Cross = NAe3.cross(NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabs(float3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// ������ : C33
	Cross = NAe3.cross(NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabs(float3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// �������ʂ����݂��Ȃ��̂Łu�Փ˂��Ă���v
	return true;
}

// �������ɓ��e���ꂽ���������瓊�e���������Z�o
float Scanner::LenSegOnSeparateAxis(float3* Sep, float3* e1, float3* e2, float3* e3)
{
	// 3�̓��ς̐�Βl�̘a�œ��e���������v�Z
	// ������Sep�͕W��������Ă��邱��
	float r1 = fabs(float3::dot(*Sep, *e1));
	float r2 = fabs(float3::dot(*Sep, *e2));
	float r3 = e3 ? (fabs(float3::dot(*Sep, *e3))) : 0;
	return r1 + r2 + r3;
}

// �v���C���[�̍��W�^�񒆂ɕ␳
DirectX::XMFLOAT3 Scanner::PlayerAdjust(GameObject * obj)
{
	DirectX::XMFLOAT3 pos = obj->GetPos();
	pos.y += obj->GetScale().y / 2.0f;

	return pos;
}