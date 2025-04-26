// インクルード部
#include "BoxCollider.h"

#include "CheckPointPath.h"

// コンストラクタ
BoxCollider::BoxCollider()
	: m_isTrigger(false)
	, m_Collision(false)
{
	m_Scale = float3(0.5f, 0.5f, 0.5f);
}

// obb同士の当たり判定チェック
bool BoxCollider::CheckObb(GameObject* objA, GameObject* objB)
{
	// 各方向ベクトルの確保
	float3 NAe1 = float3::Tofloat3(objA->GetRight()), Ae1 = NAe1 * m_Scale.x;
	float3 NAe2 = float3::Tofloat3(objA->GetUp()), Ae2 = NAe2 * m_Scale.y;
	float3 NAe3 = float3::Tofloat3(objA->GetFront()), Ae3 = NAe3 * m_Scale.z;
	float3 NBe1 = float3::Tofloat3(objB->GetRight()), Be1 = NBe1 * objB->GetComponent<BoxCollider>()->GetScale().x;
	float3 NBe2 = float3::Tofloat3(objB->GetUp()), Be2 = NBe2 * objB->GetComponent<BoxCollider>()->GetScale().y;
	float3 NBe3 = float3::Tofloat3(objB->GetFront()), Be3 = NBe3 * objB->GetComponent<BoxCollider>()->GetScale().z;
	float3 Interval;
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
		//m_Collision = false;
		return false; // 衝突していない
	}
	
	// 分離軸 : Ae2
	rA = Ae2.length();
	rB = LenSegOnSeparateAxis(&NAe2, &Be1, &Be2, &Be3);
	L = fabs(float3::dot(Interval, NAe2));
	if (L > rA + rB)
	{
		//m_Collision = false;
		return false;
	}
	
	// 分離軸 : Ae3
	rA = Ae3.length();
	rB = LenSegOnSeparateAxis(&NAe3, &Be1, &Be2, &Be3);
	L = fabs(float3::dot(Interval, NAe3));
	if (L > rA + rB)
	{
		//m_Collision = false;
		return false;
	}
	
	// 分離軸 : Be1
	rA = LenSegOnSeparateAxis(&NBe1, &Ae1, &Ae2, &Ae3);
	rB = Be1.length();
	L = fabs(float3::dot(Interval, NBe1));
	if (L > rA + rB)
	{
		//m_Collision = false;
		return false;
	}
	
	// 分離軸 : Be2
	rA = LenSegOnSeparateAxis(&NBe2, &Ae1, &Ae2, &Ae3);
	rB = Be2.length();
	L = fabs(float3::dot(Interval, NBe2));
	if (L > rA + rB)
	{
		//m_Collision = false;
		return false;
	}
	
	// 分離軸 : Be3
	rA = LenSegOnSeparateAxis(&NBe3, &Ae1, &Ae2, &Ae3);
	rB = Be3.length();
	L = fabs(float3::dot(Interval, NBe3));
	if (L > rA + rB)
	{
		//m_Collision = false;
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
		//m_Collision = false;
		return false;
	}
	
	// 分離軸 : C12
	Cross = NAe1.cross(NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabs(float3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		//m_Collision = false;
		return false;
	}
	
	// 分離軸 : C13
	Cross = NAe1.cross(NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabs(float3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		//m_Collision = false;
		return false;
	}
	
	// 分離軸 : C21
	Cross = NAe2.cross(NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabs(float3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		//m_Collision = false;
		return false;
	}
	
	// 分離軸 : C22
	Cross = NAe2.cross(NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabs(float3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		//m_Collision = false;
		return false;
	}
	
	// 分離軸 : C23
	Cross = NAe2.cross(NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabs(float3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		//m_Collision = false;
		return false;
	}
	
	// 分離軸 : C31
	Cross = NAe3.cross(NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabs(float3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		//m_Collision = false;
		return false;
	}
	
	// 分離軸 : C32
	Cross = NAe3.cross(NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabs(float3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		//m_Collision = false;
		return false;
	}
	
	// 分離軸 : C33
	Cross = NAe3.cross(NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabs(float3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		//m_Collision = false;
		return false;
	}
	
	// 分離平面が存在しないので「衝突している」
	//m_Collision = true;
	return true;
}

// 分離軸に投影された軸成分から投影線分長を算出
float BoxCollider::LenSegOnSeparateAxis(float3* Sep, float3* e1, float3* e2, float3* e3)
{
	// 3つの内積の絶対値の和で投影線分長を計算
	// 分離軸Sepは標準化されていること
	float r1 = fabs(float3::dot(*Sep, *e1));
	float r2 = fabs(float3::dot(*Sep, *e2));
	float r3 = e3 ? (fabs(float3::dot(*Sep, *e3))) : 0;
	return r1 + r2 + r3;
}

// 座標補正
void BoxCollider::FixPos(GameObject* objB)
{
	// タグ取得
	// 自分のタグを取得
	string objATag = transform->GetTag();

	// 相手のタグを取得
	string objBTag = objB->GetTag();

	// 補正をしたフラグ
	bool check = false;

	// 自分か相手のタグがチェックポイントを辿るギミックだったか
	if (objATag == "CheckPointPath" ||
		objBTag == "CheckPointPath")
	{
		check = PushAdjust(objB);
	}

	// 移動床に乗っていたら
	if (transform->GetOnMoveFloor())
	{
		// 移動床の範囲外にいるか判定
		if (FloorInSide(objB))
		{
			// 座標補正
			MoveGimmickFixPos(objB);
		}
		else
		{
			// 範囲外
			transform->SetOnMoveFloor(false);
		}
	}

	// Yだけ戻すか判定を取る
	if (objATag == "Player")
	{
		check = CheckHeightOnly(objB);
	}

	// 高さ補正、押し出しの補正をしてたら終わる
	if (check)
	{
		return;
	}

	// 通常補正
	NormalFixPos(objB);
}

// 押し出して補正
// 押し出しの補正処理をしたらtrueを返す
// 押し出しの補正をする前に終了したらfalseを返す
bool BoxCollider::PushAdjust(GameObject * objB)
{
	// 変数宣言

	// 自分の現在の座標
	float3 objAPos = float3::Tofloat3(transform->GetPos());

	// 自分の過去座標
	float3 objAOldPos = float3::Tofloat3(transform->GetOldPos());

	// 自分のサイズ
	float3 objAScale = float3::Tofloat3(transform->GetScale());

	// 当たった相手の座標
	float3 objBPos = float3::Tofloat3(objB->GetPos());

	// 当たった相手の過去座標
	float3 objBOldPos = float3::Tofloat3(objB->GetOldPos());

	// 当たった相手のサイズ
	float3 objBScale = float3::Tofloat3(objB->GetScale());

	// 移動量
	float3 movePos[2];

	// 新しい座標
	float3 newPos = objAPos;

	// 自分のタグを取得
	string tag = transform->GetTag();

	// 相手のタグ取得
	string tagB = objB->GetTag();

	// ギミック親クラス
	GimmickBase* gimmickBase[2];

	// 地面に当たったフラグ
	bool groundCollision[2];

	// ギミックの親クラスにキャスト
	gimmickBase[0] = dynamic_cast<GimmickBase*>(transform);
	gimmickBase[1] = dynamic_cast<GimmickBase*>(objB);

	// ギミック以外のが含まれてたら押し出しの補正の処理しない
	if (!gimmickBase[0] || !gimmickBase[1])
	{
		return false;
	}

	// 地面に当たったフラグを取得
	groundCollision[0] = gimmickBase[0]->GetGroundCollision();
	groundCollision[1] = gimmickBase[1]->GetGroundCollision();

	// 地面に当たってたら押し出しの補正の処理をしない
	if (groundCollision[0] || groundCollision[1])
	{
/*		if (!groundCollision[0])
		{
			gimmickBase[1]->SetGroundCollision(false);
		}
		else */if (groundCollision[1])
		{
			gimmickBase[0]->SetGroundCollision(true);
		}
		return false;
	}

	// 移動床の移動した量を求める
	movePos[0] = objAPos - objAOldPos;
	movePos[1] = objBPos - objBOldPos;


	// 補正した新しい座標をセット
	newPos.x += movePos[1].x;
	newPos.z += movePos[1].z;

	// データ変換して新しい座標を設定
	transform->SetPos(float3::ToXMFLOAT3(newPos));

	// チェックポイントを辿るギミックが
	// 移動ギミックに押されてたら
	if (tag == "CheckPointPath" && tagB == "MoveGimmick"
		&& movePos[0] == float3(0.0f, 0.0f, 0.0f))
	{
		// チェックポイントの情報を削除
		CheckPointPath* checkPointPath = dynamic_cast<CheckPointPath*>(transform);
		checkPointPath->AllDeleteCheckPoint();
	}

	return true;
}

// 高さのみの補正か判定+補正もする
bool BoxCollider::CheckHeightOnly(GameObject * objB)
{
	// 当たったオブジェクト座標取得
	float3 objBPos = float3::Tofloat3(objB->GetPos());

	// 当たったオブジェクトサイズ取得
	float3 objBScale = float3::Tofloat3(objB->GetScale());

	// 過去座標取得
	DirectX::XMFLOAT3 objAOldPos = transform->GetOldPos();

	// プレイヤーサイズ
	DirectX::XMFLOAT3 objAScale = transform->GetScale();

	// 過去座標の高さが相手のサイズより外側だったら
	if (!(objBPos.y + objBScale.y / 2.0f > objAOldPos.y + objAScale.y / 2.0f &&
		objBPos.y - objBScale.y / 2.0f < objAOldPos.y + objAScale.y / 2.0f))
	{
		// 移動床との当たり判定ならそれ用に補正する
		if (objB->GetTag() == "MoveGimmick")
		{
			MoveGimmickFixPos(objB);
			return true;
		}
		// y座標だけ戻す
		// 当たる前の座標に戻す
		DirectX::XMFLOAT3 newPos = objAOldPos;

		// x座標は戻さない
		newPos.x = transform->GetPos().x;

		// 正しい高さに戻す
		newPos.y += objAScale.y / 2.0f;

		// z座標は戻さない
		newPos.z = transform->GetPos().z;

		if (newPos.y > objBPos.y)
		{
			newPos.y = objBPos.y + objBScale.y / 2.0f;
		}

		// 座標補正
		transform->SetPos(newPos);
		return true;
	}
	return false;
}

// 移動床の範囲外にいるか判定する関数
bool BoxCollider::FloorInSide(GameObject * objB)
{
	// 変数宣言
	// 自分の現在の座標を取得
	float3 objAPos = float3::Tofloat3(transform->GetPos());

	// 相手の現在の座標を取得
	float3 objBPos = float3::Tofloat3(objB->GetPos());

	// 相手のサイズを取得
	float3 objBScale = objB->GetComponent<BoxCollider>()->GetScale();

	// 範囲内か確認
	if (objAPos.x + m_Scale.x > objBPos.x - objBScale.x &&
		objAPos.x - m_Scale.x < objBPos.x + objBScale.x &&
		objAPos.z + m_Scale.z > objBPos.z - objBScale.z &&
		objAPos.z - m_Scale.z < objBPos.z + objBScale.z)
	{
		// 範囲内
		return true;
	}

	// 範囲外
	return false;
}

// 移動床用の座標補正
void BoxCollider::MoveGimmickFixPos(GameObject * objB)
{
	// 変数宣言
	// 自分の現在の座標を取得
	float3 objAPos = float3::Tofloat3(transform->GetPos());

	// 自分のサイズを取得
	float3 objAScale = float3::Tofloat3(transform->GetScale());

	// 相手の現在の座標を取得(移動床)
	float3 objBPos = float3::Tofloat3(objB->GetPos());

	// 相手の過去座標を取得
	float3 objBOldPos = float3::Tofloat3(objB->GetOldPos());

	// 相手のサイズを取得
	float3 objBScale = float3::Tofloat3(objB->GetScale());

	// 移動量
	float3 movePos;

	// 新しい座標
	float3 newPos = objAPos;

	// 移動床に乗った
	transform->SetOnMoveFloor(true);

	// 移動床の移動した量を求める
	movePos = objBPos - objBOldPos;

	// 補正した新しい座標をセット
	newPos.x += movePos.x;
	newPos.y = objBPos.y + objBScale.y / 2.0f;
	newPos.z += movePos.z;

	// 新しい座標をセット
	transform->SetPos(float3::ToXMFLOAT3(newPos));
}

// 通常補正
void BoxCollider::NormalFixPos(GameObject * objB)
{
	// 自分のタグを取得
	string objATag = transform->GetTag();

	// 相手のタグを取得
	string objBTag = objB->GetTag();

	// 当たったオブジェクト座標取得
	float3 objBPos = float3::Tofloat3(objB->GetPos());

	// 平面の法線に対するOBBの射影線の長さを算出
	float r = 0.0f;

	// 相手の座標を取得
	float3 objBNormal = float3::Tofloat3(objB->GetPos());
	objBNormal = objBNormal.normalize();

	float3 NAe1 = float3::Tofloat3(transform->GetRight()), Ae1 = NAe1 * m_Scale.x;
	float3 NAe2 = float3::Tofloat3(transform->GetUp()), Ae2 = NAe2 * m_Scale.y;
	float3 NAe3 = float3::Tofloat3(transform->GetFront()), Ae3 = NAe3 * m_Scale.z;

	r += fabs(float3::dot(Ae1, objBNormal));
	r += fabs(float3::dot(Ae2, objBNormal));
	r += fabs(float3::dot(Ae3, objBNormal));


	// 平面とOBBの距離を算出
	float3 objAPos = float3::Tofloat3(transform->GetPos());
	float3 distance = objAPos - objBPos;

	float s = float3::dot(distance, objBNormal);

	float3 direction;							// 方向
	if (distance.length() > 0.0f)
	{
		direction = distance.normalize();		// 正規化
	}
	else
	{
		direction = float3(0.0f, 0.0f, 0.0f);	// デフォルト値
	}
	// 戻し距離を算出
	float Len = 0.0f;
	if (s > 0)
	{
		Len = r - fabs(s);
	}
	else
	{
		Len = r + fabs(s);
	}

	//if (fabs(s) - r < 0.0f)
	//{
		// 当たる前の座標に戻す
	DirectX::XMFLOAT3 newPos = transform->GetOldPos();//float3::ToXMFLOAT3(objAPos + direction * Len);

	// 新しい座標をセット
	transform->SetPos(newPos);

	// チェックポイントを辿るギミックか
	// 移動ギミックだったら
	if ((objATag == "CheckPointPath" || objATag == "MoveGimmick") &&
		(objBTag == "MoveGimmick" || objBTag == "CheckPointPath"))
	{
		// 前のループで処理済みのものだったら一緒に補正
		int objANo = extractNumber(transform->GetName());
		int objBNo = extractNumber(objB->GetName());

		if (objANo > objBNo)
		{
			objB->SetPos(objB->GetOldPos());
		}
	}
//}
}

// プレイヤーの座標真ん中に補正
DirectX::XMFLOAT3 BoxCollider::PlayerAdjust(GameObject * obj)
{
	// 新しい座標を取得
	DirectX::XMFLOAT3 pos = obj->GetPos();

	// プレイヤーの原点が真ん中下になっているのを
	// 真ん中に合わせる
	pos.y += obj->GetScale().y / 2.0f;

	return pos;
}

// 末尾の数値を取得する
int BoxCollider::extractNumber(const string & str)
{
	std::string numStr;

	// 文字列の後ろから数字を抽出
	for (int i = str.size() - 1; i >= 0; --i)
	{
		if (isdigit(str[i]))
		{
			numStr = str[i] + numStr;
		}
		else
		{
			break;
		}
	}

	return numStr.empty() ? 0 : std::stoi(numStr);
}
