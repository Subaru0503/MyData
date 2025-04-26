// インクルード部
#include "Scanner.h"

// 当たり判定コンポーネント
#include "BoxCollider.h"

// コンストラクタ
Scanner::Scanner()
	: m_Collision(false)
{
	m_Scale = float3(0.5f, 0.5f, 0.5f);
}

// obb同士の当たり判定チェック
bool Scanner::CheckObb(GameObject* objA, GameObject* objB)
{
	// 各方向ベクトルの確保
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

	// 分離軸 : Ae1
	float rA = Ae1.length();
	float rB = LenSegOnSeparateAxis(&NAe1, &Be1, &Be2, &Be3);
	float L = fabs(float3::dot(Interval, NAe1));
	if (L > rA + rB)
	{
		return false; // 衝突していない
	}

	// 分離軸 : Ae2
	rA = Ae2.length();
	rB = LenSegOnSeparateAxis(&NAe2, &Be1, &Be2, &Be3);
	L = fabs(float3::dot(Interval, NAe2));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離軸 : Ae3
	rA = Ae3.length();
	rB = LenSegOnSeparateAxis(&NAe3, &Be1, &Be2, &Be3);
	L = fabs(float3::dot(Interval, NAe3));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離軸 : Be1
	rA = LenSegOnSeparateAxis(&NBe1, &Ae1, &Ae2, &Ae3);
	rB = Be1.length();
	L = fabs(float3::dot(Interval, NBe1));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離軸 : Be2
	rA = LenSegOnSeparateAxis(&NBe2, &Ae1, &Ae2, &Ae3);
	rB = Be2.length();
	L = fabs(float3::dot(Interval, NBe2));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離軸 : Be3
	rA = LenSegOnSeparateAxis(&NBe3, &Ae1, &Ae2, &Ae3);
	rB = Be3.length();
	L = fabs(float3::dot(Interval, NBe3));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離軸 : C11
	float3 Cross;
	Cross = NAe1.cross(NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabs(float3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離軸 : C12
	Cross = NAe1.cross(NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabs(float3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離軸 : C13
	Cross = NAe1.cross(NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabs(float3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離軸 : C21
	Cross = NAe2.cross(NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabs(float3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離軸 : C22
	Cross = NAe2.cross(NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabs(float3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離軸 : C23
	Cross = NAe2.cross(NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabs(float3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離軸 : C31
	Cross = NAe3.cross(NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabs(float3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離軸 : C32
	Cross = NAe3.cross(NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabs(float3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離軸 : C33
	Cross = NAe3.cross(NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabs(float3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離平面が存在しないので「衝突している」
	return true;
}

// 分離軸に投影された軸成分から投影線分長を算出
float Scanner::LenSegOnSeparateAxis(float3* Sep, float3* e1, float3* e2, float3* e3)
{
	// 3つの内積の絶対値の和で投影線分長を計算
	// 分離軸Sepは標準化されていること
	float r1 = fabs(float3::dot(*Sep, *e1));
	float r2 = fabs(float3::dot(*Sep, *e2));
	float r3 = e3 ? (fabs(float3::dot(*Sep, *e3))) : 0;
	return r1 + r2 + r3;
}

// プレイヤーの座標真ん中に補正
DirectX::XMFLOAT3 Scanner::PlayerAdjust(GameObject * obj)
{
	DirectX::XMFLOAT3 pos = obj->GetPos();
	pos.y += obj->GetScale().y / 2.0f;

	return pos;
}