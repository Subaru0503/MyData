// Suction.cpp

//====インクルード=====
#include "Suction.h"
#include <math.h>
#include "Shop.h"
#include "Input.h"
#include "Player.h"

//=====定数・マクロ定義=====
static const float INITIAL_SUCTION_RANGE = 4.0f;		// 基本吸い込み有効距離
static const float INITIAL_SUCTION_ANGLE = 50.0f;		// 基本吸い込み有効吸い込み角度（正面から左右に何度ずつか）
static const float INITIAL_SUCTION_SECONDS = 1.0f;		// 吸い込むまでに最長何秒か
static const float DELETE_ANGLE = 90.0f;				// 完全吸い込み範囲の角度（正面から左右に何度ずつか）
static const float SUCTION_INTO_MATER = 2.0f;			// 完全に吸い込まれるモードに入るオブジェクトとの距離
static const float LEVEL_SPEED = 0.5f;					// １レベル差ごとの吸い込みスピード倍率
#define PLAY_GIMMICK (3.0f)								// 青キノコを引っ張れる範囲制限
#define RELEASE_GIMMICK (9.0f)							// 青キノコが伸びる範囲制限
#define WEIGHT_MINUS (0.007f)							// 範囲制限半径減算用
#define VEC_OFFSETX (5.0f)								// ベクトルを取るための移動量
#define PLAY_GIMMICK_DELTA_POS (0.8f)					// プレイギミックで使う座標の変化量
#define INIT_DELTA_POS (0.95f)							// 座標調整用の変化量の初期値
#define DELTA_POS (0.9f)								// 座標調整用の変化量を変える

// コンストラクタ
Suction::Suction()
	: m_suctionRange(INITIAL_SUCTION_RANGE)
	, m_suctionAngle(INITIAL_SUCTION_ANGLE)
	, m_suctionSeconds(INITIAL_SUCTION_SECONDS)
	, m_pObjectList(nullptr)
	, m_playerForward{ 0.0f,0.0f,0.0f,0.0f }
	, m_playerPos{ 0.0f,0.0f,0.0f }
	, m_nozzleLevel(1)
	, m_fPower(1.0f)
	, m_pPlayer(nullptr)
	, m_start(false)
	, m_fAngle(90.0f)
	, m_pDrill(nullptr)
	, m_pSaw(nullptr)
	, m_pHammer(nullptr)
{
}

Suction::~Suction()
{
}

/**************************************************************************
*@brief オブジェクトが吸い込み範囲内にいるか判定しオブジェクトに結果を格納
***************************************************************************
*@param [in] pObject		オブジェクトリストの参照
*@param [in] playerPos		プレイヤーの座標
*@param [in] playerForward	プレイヤーが向いている方向のベクトル
*@param [in] Custom			カスタムの所持状況情報
****************************************************************************/
void Suction::IsObjectInSuctionRange(std::list<Object*>* pObjectList, DirectX::XMFLOAT3 playerPos,
	DirectX::XMFLOAT3 playerForward, int* Custom)
{
	m_start = true;	// player.cppで関数を呼び出せるように
	if (IsKeyPress('0'))
	{
		m_nozzleLevel = 3;
		m_suctionRange = 20.0f;
		m_suctionAngle = 90.0f;
	}

	// ノズルレベルに応じて有効距離を調節
	m_suctionRange = INITIAL_SUCTION_RANGE * m_fPower *(1.0f + (m_nozzleLevel - 1) * 0.5f);

	// プレイヤーの向きを受け取って計算用に変換
	DirectX::XMFLOAT3 playerForwardXZ = playerForward;
	m_playerForward = DirectX::XMLoadFloat3(&playerForwardXZ);

	// カメラの向きを使ったプレイヤー方向ベクトルのため、Y成分を無くしてX軸と平行なベクトルに直す
	m_playerForward = DirectX::XMVectorMultiply(m_playerForward, DirectX::XMVectorSet(1.0f, 0.0f, 1.0f, 0.0f));
	// プレイヤーの方向ベクトルを正規化
	m_playerForward = DirectX::XMVector3Normalize(m_playerForward);
	// メンバにプレイヤー座標をセット
	m_playerPos = playerPos;
	// メンバにオブジェクトリストをセット
	m_pObjectList = pObjectList;


	// オブジェクトリストの全要素
	for (Object* pObj : *m_pObjectList)
	{
		if (pObj->IsDrop()) { continue; }
		if (!CheckHeightLink(pObj) && !pObj->GetRandSlope()) { continue; }	// 

		//--プレイヤー、オブジェクト間の距離による判定
		// プレイヤー座標とオブジェクト座標から二点間の距離を計算
		float distance = 0.0f;
		DirectX::XMFLOAT3 objSize = pObj->GetScale();	// オブジェクトのサイズ
		if (pObj->GetKind() == Object::TREE && pObj->GetLevel() == 3)
		{
			distance = sqrt((pObj->GetPos().x - m_playerPos.x)*(pObj->GetPos().x - m_playerPos.x) +
				(pObj->GetPos().y - objSize.y / 2.0f - m_playerPos.y)*(pObj->GetPos().y - objSize.y / 2.0f - m_playerPos.y) +
				(pObj->GetPos().z - m_playerPos.z)*(pObj->GetPos().z - m_playerPos.z)
			);
		}
		else
		{
			distance = sqrt((pObj->GetPos().x - m_playerPos.x)*(pObj->GetPos().x - m_playerPos.x) +
				(pObj->GetPos().y - objSize.y / 2.0f - m_playerPos.y)*(pObj->GetPos().y - objSize.y / 2.0f - m_playerPos.y) +
				(pObj->GetPos().z - m_playerPos.z)*(pObj->GetPos().z - m_playerPos.z)
			);
		}
		// 吸い込み距離外ならfalseで終了
		if (m_suctionRange < distance)
		{
			pObj->SetSuctionFlg(false); continue; 
		}

		// 高さを考慮せずに測れるように調整
		DirectX::XMFLOAT3 objPos = pObj->GetPos();		// オブジェクトの座標
		objPos.y = objPos.y - objSize.y / 2.0f;			// 中心座標をプレイヤーと同じ位置に

		//--プレイヤーが向いている方向を基準とした角度による判定
		// プレイヤーからオブジェクトへのベクトルを取得
		DirectX::XMVECTOR difference = DirectX::XMVectorSubtract(	// 減算→(引数1 - 引数2)
			DirectX::XMLoadFloat3(&objPos),		// オブジェクトの座標のポインタ
			DirectX::XMLoadFloat3(&m_playerPos)			// プレイヤーの座標が格納されている変数アドレス
		);
		// オブジェクトへのベクトルを正規化
		difference = DirectX::XMVector3Normalize(difference);

		// オブジェクトへの方向ベクトルとプレイヤーの向きのベクトルの間のラジアン角を取得
		float angle;
		DirectX::XMStoreFloat(&angle, DirectX::XMVector3AngleBetweenNormals(
			difference,			// プレイヤーからオブジェクトへの方向ベクトル
			m_playerForward		// プレイヤーの方向ベクトル 
		));

		// ラジアンからDegreesに角度を変換
		float angleToObject = DirectX::XMConvertToDegrees(angle);

		pObj->SetAngleToPlayer(angleToObject);

		int nJudge = 0;

		// オブジェクトへの角度が有効範囲内か判定しオブジェクトのフラグを切り替える
		if (angleToObject <= m_suctionAngle)
		{
			int objLevel = pObj->GetLevel();	// オブジェクトのレベルを取得

			//	ノズルレベルがオブジェクトのレベル以上であれば
			if (m_nozzleLevel >= objLevel)
			{
				pObj->SetSuctionFlg(true);	// 吸い込みフラグを立てる
				pObj->SetPlayerPosY(playerPos.y);	// プレイヤー座標Yの情報を渡す
				nJudge = 1;
			}
			// ノズルレベルとオブジェクトのレベル差が１
			else if ((m_nozzleLevel + 1) == objLevel) {
				pObj->SetShake(true);	// 揺れフラグを立てる
			}
			// ノズルレベルが足りていなかったら
			if (!nJudge)
			{
				// ギミックであれば
				if (pObj->GetGimmick())
				{
					pObj->SetPlayGimmick(true);		// ギミックを開始
					pObj->SetSuctionGimmick(true);	// ギミックが吸い込まれている
					m_pPlayer->SetSuction(true);	// プレイヤーが吸い込みをしている
				}
				// このオブジェクトを破壊できるカスタムパーツを所持していれば
				for (int i = 0; i < MAX_CUSTOM; i++)
				{
					// 装備してなかったら次へ
					if (Custom[i] == 0) continue;
					switch (i)
					{
						// のこぎり
					case Custom::SAW:
						// レベルが足りているか
						if ((Custom[i] + 1 >= objLevel && pObj->GetKind() == Object::TREE) ||
							(Custom[i] + 1 >= objLevel && pObj->GetKind() == Object::SIGNBOARD) ||
							(Custom[i] + 1 >= objLevel && pObj->GetKind() == Object::CHOCOLATETREE))
						{
							if (INITIAL_SUCTION_RANGE > distance && !pObj->IsDrop())	// 破壊有効距離内か判定
							{
								pObj->SetGetMoney(false);
								pObj->SetDelete();	// 破壊フラグを立てる
								m_pSaw->SawAnimetion();
							}
						}
						// レベル差が1なら
						else if ((objLevel - (Custom[i] + 1) == 1 && pObj->GetKind() == Object::TREE) ||
							(objLevel - (Custom[i] + 1) == 1 && pObj->GetKind() == Object::SIGNBOARD) ||
							(objLevel - (Custom[i] + 1) == 1 && pObj->GetKind() == Object::CHOCOLATETREE))
						{
							pObj->SetShake(true);	// 揺れフラグを立てる
						}
						break;
					case Custom::HAMMER:
						// レベルが足りているか
						if ((Custom[i] + 1 >= objLevel && pObj->GetKind() == Object::HOUSE) ||
							(Custom[i] + 1 >= objLevel && pObj->GetKind() == Object::SWEETSHOUSE) ||
							(Custom[i] + 1 >= objLevel && pObj->GetKind() == Object::FENCE) ||
							(Custom[i] + 1 >= objLevel && pObj->GetKind() == Object::CHOCOLATEFENCE))
						{
							if (INITIAL_SUCTION_RANGE > distance && !pObj->IsDrop())	// 破壊有効距離内か判定
							{
								pObj->SetGetMoney(false);
								pObj->SetDelete();	// 破壊フラグを立てる
								m_pHammer->HammerAnimetion();
							}
						}
						// レベル差が1なら
						else if ((objLevel - (Custom[i] + 1) == 1 && pObj->GetKind() == Object::HOUSE) ||
							(objLevel - (Custom[i] + 1) == 1 && pObj->GetKind() == Object::SWEETSHOUSE) ||
							(objLevel - (Custom[i] + 1) == 1 && pObj->GetKind() == Object::FENCE) ||
							(objLevel - (Custom[i] + 1) == 1 && pObj->GetKind() == Object::CHOCOLATEFENCE))
						{
							pObj->SetShake(true);	// 揺れフラグを立てる
						}
						break;
					case Custom::DRILL:
						// レベルが足りているか
						if ((Custom[i] + 1 >= objLevel && pObj->GetKind() == Object::ROCK) ||
							(Custom[i] + 1 >= objLevel && pObj->GetKind() == Object::CANDYROCK))
						{
							if (INITIAL_SUCTION_RANGE > distance && !pObj->IsDrop())	// 破壊有効距離内か判定
							{
								pObj->SetGetMoney(false);
								pObj->SetDelete();	// 破壊フラグを立てる
								m_pDrill->DrillAnimetion();
							}
						}
						// レベル差が1なら
						else if ((objLevel - (Custom[i] + 1) == 1 && pObj->GetKind() == Object::ROCK) ||
							(objLevel - (Custom[i] + 1) == 1 && pObj->GetKind() == Object::CANDYROCK))
						{
							pObj->SetShake(true);	// 揺れフラグを立てる
						}
						break;
					}
					//if ((Custom[i] + 1 >= objLevel && pObj->GetKind() == Object::TREE) ||
					//	(Custom[i] - 2 >= objLevel && pObj->GetKind() == Object::HOUSE) ||
					//	(Custom[i] - 5 >= objLevel && pObj->GetKind() == Object::ROCK) ||
					//	(Custom[i] + 1 >= objLevel && pObj->GetKind() == Object::FENCE) ||
					//	(Custom[i] + 1 >= objLevel && pObj->GetKind() == Object::SIGNBOARD))
					//{
					//	if (INITIAL_SUCTION_RANGE > distance && !pObj->IsDrop())	// 破壊有効距離内か判定
					//	{
					//		pObj->SetDelete();	// 破壊フラグを立てる
					//	}
					//}
					//else if ((objLevel - Custom[i] + 1 == 1 && pObj->GetKind() == Object::TREE) ||
					//	(objLevel - Custom[i] - 2 == 1 && pObj->GetKind() == Object::HOUSE) ||
					//	(objLevel - Custom[i] - 5 == 1 && pObj->GetKind() == Object::ROCK) ||
					//	(objLevel - Custom[i] + 1 >= objLevel && pObj->GetKind() == Object::FENCE) ||
					//	(objLevel - Custom[i] + 1 >= objLevel && pObj->GetKind() == Object::SIGNBOARD))
					//{
					//	pObj->SetShake(true);	// 揺れフラグを立てる
					//}
				}
			}
			//if (pObj->GetKind() == Object::MUSHROOM ||
			//	pObj->GetKind() == Object::RUBBISH ||
			//	pObj->GetKind() == Object::STONE ||
			//	pObj->GetKind() == Object::WOOD) {
			//	pObj->SetSuctionFlg(true);
			//}
			//else
			//{
			//	for (int i = 0; i < MAX_CUSTOM; i++)
			//	{
			//		if ((Custom[i] == SAW && pObj->GetKind() == Object::TREE) || 
			//			(Custom[i] == HAMMER && pObj->GetKind() == Object::HOUSE) ||
			//			(Custom[i] == DRILL && pObj->GetKind() == Object::ROCK) || 
			//			(Custom[i] == HOSE && pObj->GetKind() == Object::BURNINGOBJECT) ||
			//			(Custom[i] == SAW && pObj->GetKind() == Object::FENCE) ||
			//			(Custom[i] == SAW && pObj->GetKind() == Object::SIGNBOARD))
			//		{
			//			pObj->SetDelete();
			//		}
			//	}
			//}
		}
		else {
			pObj->SetSuctionFlg(false);
			pObj->SetGetMoney(false);		// お金が手に入らないように
			pObj->SetShake(false);
			pObj->SetSuctionGimmick(false);	// ギミックが吸い込まれていない状態
			//m_pPlayer->SetSuction(false);	// プレイヤーが吸い込んでいない状態
		}
	}
}

/***********************************************************
*@brief 距離、質量に応じてオブジェクトに速度をセット
*@brief 完全吸い込み範囲内のオブジェクトの削除フラグを立てる
***********************************************************/
void Suction::SuctionObject(int *CandleDemelit, int *Custom)
{
	// リストの全要素
	for (Object* pObj : *m_pObjectList)
	{
		// 吸い込み中でないか慣性で移動中でなければ次のオブジェクトへ
		if (!pObj->IsSuction() && !pObj->IsMove()) { continue; }

		// オブジェクトの座標を取得
		DirectX::XMFLOAT3 objPos = pObj->GetPos();

		// プレイヤー座標とオブジェクト座標から二点間の距離を計算
		float distance = sqrt((objPos.x - m_playerPos.x)*(objPos.x - m_playerPos.x) +
			0.0f +
			(objPos.z - m_playerPos.z)*(objPos.z - m_playerPos.z)
		);

		// 完全吸い込み角度内なら
		if (pObj->GetAngleToPlayer() < DELETE_ANGLE)
		{
			// 距離が完全吸い込み距離内なら
			if (distance <= SUCTION_INTO_MATER) {
				pObj->SetDelete();			// オブジェクトの削除フラグを立てる
				pObj->SetGetMoney(true);
				// ろうそくを吸い込んで耐熱カスタムが装備されていなかったら
				if (pObj->GetKind() == Object::CANDLE && Custom[5] == 0)
				{
					*CandleDemelit = 1;	// フラグ上げ
				}
				continue;
			}
		}

		// 慣性で動いているだけのオブジェクトはここまで～
		if (!pObj->IsSuction() && pObj->IsMove()) { continue; }
		
		// オブジェクトからプレイヤーへのベクトルを取得
		DirectX::XMVECTOR objToPlayer = DirectX::XMVectorSubtract(	// 減算→(引数1 - 引数2)
			DirectX::XMLoadFloat3(&m_playerPos),			// プレイヤーの座標が格納されている変数アドレス
			DirectX::XMLoadFloat3(&objPos)		// オブジェクトの座標のポインタ
		);
		// ↑のベクトルを正規化
		objToPlayer = DirectX::XMVector3Normalize(objToPlayer);

		// 移動方向ベクトルをオブジェクトにセット
		pObj->SetDirection(objToPlayer);

		//--距離、質量に応じて速度を決める処理
		// 1秒間に何メートル引き寄せるか計算
		float speed = m_suctionRange / m_suctionSeconds;
		float rotate = 0.0f;
		// 距離が近づく程速くなるように計算
		speed = speed * (m_suctionRange / distance);
		rotate = 180.0f * (m_suctionRange / distance);
		// 質量が大きいほど遅くなるように計算
		speed = speed / pObj->GetMass();
		rotate = rotate / pObj->GetMass();
		// ノズルとオブジェクトのレベル差を取得
		int levelDifference = m_nozzleLevel - pObj->GetLevel();
		// ノズルのレベルとオブジェクトのレベルを考慮して吸い込み速度を調節
		if (levelDifference > 0)
		{
			speed *= 1.0f + (levelDifference * LEVEL_SPEED);
		}
		DirectX::XMFLOAT3 angle(rotate, rotate, rotate);
		// 速度をオブジェクトにセット
		pObj->SetVelocity(speed);
		pObj->SetAngle(angle);
	}
}

void Suction::NozzleLevelUp()				// ノズルレベルアップ
{
	if (m_nozzleLevel < 3)
	{
		m_nozzleLevel++;
		m_pESuction->SetScale();
	}
}

void Suction::PowerUP()						// パワーアップ
{
	m_fPower = 1.5f;
}

int Suction::GetNozzleLevel()				// ノズルレベルゲット
{
	return m_nozzleLevel;
}

bool Suction::GetStart()
{
	return m_start;
}

// オブジェクトとプレイヤーの高さが同じか判定
bool Suction::CheckHeightLink(Object * pObj)
{
	return m_pPlayer->GetRandHeight() == pObj->GetRandHeight();
}

// モデルを回転させる
void Suction::ModelRotate(Object* pObj, DirectX::XMFLOAT3 playerPos, DirectX::XMFLOAT3 pos)
{
	// プレイヤーの方向or傘の方向に青キノコ根本を傾ける
	if (pos.x < playerPos.x && pos.z < playerPos.z)	// プレイヤーor傘が左下の方にいたら
	{
		// Y軸で回転させる角度を取る用
		DirectX::XMFLOAT3 workPos = pos;	// 青キノコ根本
		workPos.z += VEC_OFFSETX;	// ベクトルを取るために青キノコ根本の座標から少しずらす

		// X軸で回転させる角度を取る用
		DirectX::XMFLOAT3 workPos2 = playerPos;
		workPos2.y = pos.y;

		// y軸で回転させる
		// 角度を取るためにベクトルを取る
		DirectX::XMVECTOR difference = DirectX::XMVectorSubtract(	// 減算→(引数1 - 引数2)
			DirectX::XMLoadFloat3(&workPos),		// 青キノコ根本の座標からずらした座標
			DirectX::XMLoadFloat3(&pos)				// 青キノコ根本の座標
		);
		// オブジェクトへのベクトルを正規化
		difference = DirectX::XMVector3Normalize(difference);

		DirectX::XMVECTOR difference2 = DirectX::XMVectorSubtract(	// 減算→(引数1 - 引数2)
			DirectX::XMLoadFloat3(&playerPos),		// プレイヤーor傘座標
			DirectX::XMLoadFloat3(&pos)				// 青キノコ根本の座標
		);
		// オブジェクトへのベクトルを正規化
		difference2 = DirectX::XMVector3Normalize(difference2);

		// プレイヤーor傘の方に向けるためのラジアン角を取得
		float angleY;
		DirectX::XMStoreFloat(&angleY, DirectX::XMVector3AngleBetweenNormals(
			difference,			// プレイヤーor傘からオブジェクトへの方向ベクトル
			difference2			// 青キノコ根本とプレイヤーor傘の距離ベクトル 
		));

		// ラジアンからDegreesに角度を変換
		float angleToObjectY = DirectX::XMConvertToDegrees(angleY);

		//pObj->SetAngleToPlayer(angleToObjectY);

		// x軸で回転させる
		// 角度を取るためにベクトルを取る
		difference = DirectX::XMVectorSubtract(	// 減算→(引数1 - 引数2)
			DirectX::XMLoadFloat3(&workPos2),		// 青キノコ根本の座標からずらした座標
			DirectX::XMLoadFloat3(&pos)				// 青キノコ根本の座標
		);
		// オブジェクトへのベクトルを正規化
		difference = DirectX::XMVector3Normalize(difference);

		// プレイヤーor傘の方に向けるためのラジアン角を取得
		float angleX;
		DirectX::XMStoreFloat(&angleX, DirectX::XMVector3AngleBetweenNormals(
			difference,			// プレイヤーor傘からオブジェクトへの方向ベクトル
			difference2			// 青キノコ根本とプレイヤーor傘の距離ベクトル 
		));

		// ラジアンからDegreesに角度を変換
		float angleToObjectX = DirectX::XMConvertToDegrees(angleX);

		//pObj->SetAngleToPlayer(angleToObjectX);

		// 角度セット
		DirectX::XMFLOAT3 objangle;
		objangle.x = m_fAngle - angleToObjectX;
		objangle.y = angleToObjectY;
		objangle.z = 0.0f;

		pObj->SetAngle(objangle);
	}
	// プレイヤーor傘が右下の方にいたら
	else if (pos.x > playerPos.x && pos.z < playerPos.z)
	{
		// Y軸で回転させる角度を取る用
		DirectX::XMFLOAT3 workPos = pos;	// 青キノコ根本
		workPos.z += VEC_OFFSETX;	// ベクトルを取るために青キノコ根本の座標から少しずらす	

		// X軸で回転させる角度を取る用
		DirectX::XMFLOAT3 workPos2 = playerPos;
		workPos2.y = pos.y;

		// y軸で回転させる
		// 角度を取るためにベクトルを取る
		DirectX::XMVECTOR difference = DirectX::XMVectorSubtract(	// 減算→(引数1 - 引数2)
			DirectX::XMLoadFloat3(&pos),				// 青キノコ根本の座標
			DirectX::XMLoadFloat3(&workPos)				// 青キノコ根本の座標からずらした座標
		);
		// オブジェクトへのベクトルを正規化
		difference = DirectX::XMVector3Normalize(difference);

		DirectX::XMVECTOR difference2 = DirectX::XMVectorSubtract(	// 減算→(引数1 - 引数2)
			DirectX::XMLoadFloat3(&playerPos),		// プレイヤーor傘座標
			DirectX::XMLoadFloat3(&pos)				// 青キノコ根本の座標
		);
		// オブジェクトへのベクトルを正規化
		difference2 = DirectX::XMVector3Normalize(difference2);

		// プレイヤーor傘の方に向けるためのラジアン角を取得
		float angleY;
		DirectX::XMStoreFloat(&angleY, DirectX::XMVector3AngleBetweenNormals(
			difference,			// プレイヤーor傘からオブジェクトへの方向ベクトル
			difference2			// 青キノコ根本とプレイヤーor傘の距離ベクトル 
		));

		// ラジアンからDegreesに角度を変換
		float angleToObjectY = DirectX::XMConvertToDegrees(angleY);

		// x軸で回転させる
		// 角度を取るためにベクトルを取る
		difference = DirectX::XMVectorSubtract(	// 減算→(引数1 - 引数2)
			DirectX::XMLoadFloat3(&workPos2),	// 青キノコ根本の座標からずらした座標			
			DirectX::XMLoadFloat3(&pos)			// 青キノコ根本の座標
		);
		// オブジェクトへのベクトルを正規化
		difference = DirectX::XMVector3Normalize(difference);

		// プレイヤーor傘の方に向けるためのラジアン角を取得
		float angleX;
		DirectX::XMStoreFloat(&angleX, DirectX::XMVector3AngleBetweenNormals(
			difference,			// プレイヤーor傘からオブジェクトへの方向ベクトル
			difference2			// 青キノコ根本とプレイヤーor傘の距離ベクトル 
		));

		// ラジアンからDegreesに角度を変換
		float angleToObjectX = DirectX::XMConvertToDegrees(angleX);

		// 角度セット
		DirectX::XMFLOAT3 objangle;
		objangle.x = -m_fAngle + angleToObjectX;
		objangle.y = angleToObjectY;
		objangle.z = 0.0f;

		pObj->SetAngle(objangle);
	}
	// プレイヤーor傘が左上の方にいたら
	else if (pos.x < playerPos.x && pos.z > playerPos.z)
	{
		// Y軸で回転させる角度を取る用
		DirectX::XMFLOAT3 workPos = pos;	// 青キノコ根本
		workPos.z -= VEC_OFFSETX;	// ベクトルを取るために青キノコ根本の座標から少しずらす	

		// X軸で回転させる角度を取る用
		DirectX::XMFLOAT3 workPos2 = playerPos;
		workPos2.y = pos.y;

		// y軸で回転させる
		// 角度を取るためにベクトルを取る
		DirectX::XMVECTOR difference = DirectX::XMVectorSubtract(	// 減算→(引数1 - 引数2)
			DirectX::XMLoadFloat3(&pos),				// 青キノコ根本の座標
			DirectX::XMLoadFloat3(&workPos)				// 青キノコ根本の座標からずらした座標
		);
		// オブジェクトへのベクトルを正規化
		difference = DirectX::XMVector3Normalize(difference);

		DirectX::XMVECTOR difference2 = DirectX::XMVectorSubtract(	// 減算→(引数1 - 引数2)
			DirectX::XMLoadFloat3(&playerPos),		// プレイヤーor傘座標
			DirectX::XMLoadFloat3(&pos)				// 青キノコ根本の座標
		);
		// オブジェクトへのベクトルを正規化
		difference2 = DirectX::XMVector3Normalize(difference2);

		// プレイヤーor傘の方に向けるためのラジアン角を取得
		float angleY;
		DirectX::XMStoreFloat(&angleY, DirectX::XMVector3AngleBetweenNormals(
			difference,			// プレイヤーor傘からオブジェクトへの方向ベクトル
			difference2			// 青キノコ根本とプレイヤーor傘の距離ベクトル 
		));

		// ラジアンからDegreesに角度を変換
		float angleToObjectY = DirectX::XMConvertToDegrees(angleY);


		// x軸で回転させる
		// 角度を取るためにベクトルを取る
		difference = DirectX::XMVectorSubtract(	// 減算→(引数1 - 引数2)
			DirectX::XMLoadFloat3(&workPos2),			// 青キノコ根本の座標からずらした座標
			DirectX::XMLoadFloat3(&pos)					// 青キノコ根本の座標
		);
		// オブジェクトへのベクトルを正規化
		difference = DirectX::XMVector3Normalize(difference);

		// プレイヤーor傘の方に向けるためのラジアン角を取得
		float angleX;
		DirectX::XMStoreFloat(&angleX, DirectX::XMVector3AngleBetweenNormals(
			difference,			// プレイヤーor傘からオブジェクトへの方向ベクトル
			difference2			// 青キノコ根本とプレイヤーor傘の距離ベクトル 
		));

		// ラジアンからDegreesに角度を変換
		float angleToObjectX = DirectX::XMConvertToDegrees(angleX);

		// 角度セット
		DirectX::XMFLOAT3 objangle;
		objangle.x = m_fAngle - angleToObjectX;
		objangle.y = angleToObjectY;
		objangle.z = 0.0f;

		pObj->SetAngle(objangle);
	}
	// プレイヤーor傘が右上の方にいたら
	else if (pos.x > playerPos.x && pos.z > playerPos.z)
	{
		// Y軸で回転させる角度を取る用
		DirectX::XMFLOAT3 workPos = pos;	// 青キノコ根本
		workPos.z -= VEC_OFFSETX;	// ベクトルを取るために青キノコ根本の座標から少しずらす	

		// X軸で回転させる角度を取る用
		DirectX::XMFLOAT3 workPos2 = playerPos;
		workPos2.y = pos.y;

		// y軸で回転させる
		// 角度を取るためにベクトルを取る
		DirectX::XMVECTOR difference = DirectX::XMVectorSubtract(	// 減算→(引数1 - 引数2)
			DirectX::XMLoadFloat3(&workPos),		// 青キノコ根本の座標からずらした座標
			DirectX::XMLoadFloat3(&pos)				// 青キノコ根本の座標
		);
		// オブジェクトへのベクトルを正規化
		difference = DirectX::XMVector3Normalize(difference);

		DirectX::XMVECTOR difference2 = DirectX::XMVectorSubtract(	// 減算→(引数1 - 引数2)
			DirectX::XMLoadFloat3(&playerPos),		// プレイヤーor傘座標
			DirectX::XMLoadFloat3(&pos)				// 青キノコ根本の座標
		);
		// オブジェクトへのベクトルを正規化
		difference2 = DirectX::XMVector3Normalize(difference2);

		// プレイヤーor傘の方に向けるためのラジアン角を取得
		float angleY;
		DirectX::XMStoreFloat(&angleY, DirectX::XMVector3AngleBetweenNormals(
			difference,			// プレイヤーor傘からオブジェクトへの方向ベクトル
			difference2			// 青キノコ根本とプレイヤーor傘の距離ベクトル 
		));

		// ラジアンからDegreesに角度を変換
		float angleToObjectY = DirectX::XMConvertToDegrees(angleY);

		// x軸で回転させる
		// 角度を取るためにベクトルを取る
		difference = DirectX::XMVectorSubtract(	// 減算→(引数1 - 引数2)
			DirectX::XMLoadFloat3(&workPos2),		// 青キノコ根本の座標からずらした座標
			DirectX::XMLoadFloat3(&pos)				// 青キノコ根本の座標
		);
		// オブジェクトへのベクトルを正規化
		difference = DirectX::XMVector3Normalize(difference);

		// プレイヤーor傘の方に向けるためのラジアン角を取得
		float angleX;
		DirectX::XMStoreFloat(&angleX, DirectX::XMVector3AngleBetweenNormals(
			difference,			// プレイヤーor傘からオブジェクトへの方向ベクトル
			difference2			// 青キノコ根本とプレイヤーor傘の距離ベクトル 
		));

		// ラジアンからDegreesに角度を変換
		float angleToObjectX = DirectX::XMConvertToDegrees(angleX);

		// 角度セット
		DirectX::XMFLOAT3 objangle;
		objangle.x = -m_fAngle + angleToObjectX;
		objangle.y = angleToObjectY;
		objangle.z = 0.0f;

		pObj->SetAngle(objangle);
	}
}


void Suction::SetESuction(ESuction * pEsuction)
{
	m_pESuction = pEsuction;
}

//=====ギミック吸い込み処理=====
void Suction::PlayGimmick()
{
	float deltaMove = 1.0f;			// 移動の変化量
	int NemotoNum = 0;				// 根本の個数カウント用
	m_fAngle = 90.0f;				// 角度セット
	prevObjPos = m_playerPos;		// プレイヤー座標セット
	int KasaSuction = false;	// 傘が動いたフラグ
	// リストの全要素
	for (Object* pObj : *m_pObjectList)
	{
		if (pObj->GetGimmick() && !pObj->IsSuction() && pObj->GetTime() < 0.1f && pObj->GetSuctionGimmick())
		{

			// 描画フラグが下がっていたら
			if (!pObj->GetDraw())
			{
				pObj->SetDraw(true);			// フラグ上げ
				pObj->SetPlayGimmick(true);		// ギミックフラグ上げ
			}
			DirectX::XMFLOAT3 pos = pObj->GetPos();					// ギミックオブジェクト座標
			if (pObj->GetKind() == Object::Kind::BLUE_MUSHROOM_NEMOTO)	// 根本だったら
			{
				// 動いてなかったら終わり
				if (!KasaSuction) return;
				NemotoNum++;										// カウントアップ
				pos.y = prevObjPos.y - 0.2f;						// 高さ調整
				for (int j = 0; j < NemotoNum; j++)
				{
					deltaMove *= PLAY_GIMMICK_DELTA_POS;						// 変化量の値を変えていく
				}
			}
			else
			{
				KasaSuction = true;	// 動いてたらフラグ上げ
			}

			DirectX::XMFLOAT3 origin = pObj->GetGimmickOldPos();	// オブジェクトの初期位置
			float radius = PLAY_GIMMICK * deltaMove;				// 移動可能範囲の半径
			pObj->SetSuctionGimmick(true);							// ギミック吸い込み中
			DirectX::XMFLOAT3 playerPos;							// プレイヤー座標
			pObj->SetTime(0.0f);									// 時間経過リセット
			pObj->SetWeight(1.0f);									// 往復量リセット
			//pObj->SetRadius(RELEASE_GIMMICK);						// 伸びる範囲リセット

			// プレイヤーの前方(カメラの向き)座標
			playerPos.x = m_playerPos.x;
			playerPos.y = m_playerPos.y;
			playerPos.z = m_playerPos.z;

			// 根本だけ角度を変える(プレイヤーの方向に向くように)
			if (pObj->GetKind() == Object::Kind::BLUE_MUSHROOM_NEMOTO)
			{
				// プレイヤーの方に向ける
				ModelRotate(pObj, prevObjPos, pos);
			}

			// ベクトルの差分を計算
			DirectX::XMVECTOR startVec = DirectX::XMLoadFloat3(&pos);
			DirectX::XMVECTOR endVec = DirectX::XMLoadFloat3(&playerPos);
			DirectX::XMVECTOR direction = DirectX::XMVectorSubtract(endVec, startVec);
			direction = DirectX::XMVector3Normalize(direction); // 正規化

			// 速度に基づいて移動距離を計算
			float speed = 0.1f * deltaMove;
			DirectX::XMVECTOR velocity = DirectX::XMVectorScale(direction, speed);

			// 現在の位置を更新
			DirectX::XMVECTOR currentVec = DirectX::XMLoadFloat3(&pos);
			currentVec = DirectX::XMVectorAdd(currentVec, velocity);
			DirectX::XMStoreFloat3(&pos, currentVec);

			// 原点からの新しい位置までの距離を計算
			DirectX::XMVECTOR originVec = DirectX::XMLoadFloat3(&origin);
			DirectX::XMVECTOR diffVecFromOrigin = DirectX::XMVectorSubtract(currentVec, originVec);
			float distanceFromOrigin = DirectX::XMVectorGetX(DirectX::XMVector3Length(diffVecFromOrigin));
			float distanceFromOriginSquared = DirectX::XMVectorGetX(DirectX::XMVector3LengthSq(diffVecFromOrigin));

			// 距離を半径で割って比率を計算（0.0f から 1.0f の範囲にクランプ）
			float ratio = min(distanceFromOrigin / (radius * 0.5f), 1.0f);
			pObj->SetSuctionDis(ratio);

			DirectX::XMFLOAT3 relese;

			// 距離が半径の範囲内かどうかを確認
			if (distanceFromOriginSquared > radius * radius)
			{
				// 到達可能な最も近い点を設定
				DirectX::XMVECTOR limitedVec = DirectX::XMVectorAdd(originVec, DirectX::XMVectorScale(DirectX::XMVector3Normalize(diffVecFromOrigin), radius));
				currentVec = limitedVec;
			}

			// 更新された位置を設定
			DirectX::XMStoreFloat3(&pos, currentVec);
			relese.x = (pos.x) * 2.0f;
			relese.y = -pos.y;
			relese.z = (pos.z) * 2.0f;
			pObj->SetPos(pos);
			prevObjPos = pos;						// 一つ前のオブジェクトの座標を取っておく
			pObj->SetRadius(RELEASE_GIMMICK);

			//// 到達判定用の距離の閾値
			//const float arrivalThreshold = speed * 1.5f; // 十分に近いとみなす距離

			//// 目的座標との距離を計算
			//DirectX::XMVECTOR diffVec = DirectX::XMVectorSubtract(currentVec, endVec);
			//float distanceSquared = DirectX::XMVectorGetX(DirectX::XMVector3LengthSq(diffVec));

			//// 距離が閾値以下かどうかで判定
			//if (distanceSquared <= arrivalThreshold * arrivalThreshold)
			//{
			//	//pObj->SetPos(playerPos);
			//}
		}
	}
}

//=====ギミック動作処理=====
void Suction::ReleaseGimmick()
{
	float speed;		// 移動速度
	int nCnt = 0;		// 根本の個数カウント用
	float deltaPos;		// 移動範囲を調整するための変化量
	m_fAngle = 90.0f;	// 角度調整
	int firstNemoto = 0;
	int KasaSuction = false;	// 傘が動いたフラグ
	for (Object* pObj : *m_pObjectList)
	{
		if (pObj->GetGimmick() && !pObj->GetSuctionGimmick() && pObj->GetPlayGimmick())
		{
			DirectX::XMFLOAT3 origin = pObj->GetGimmickOldPos(); // オブジェクトの初期位置
			DirectX::XMFLOAT3 pos = pObj->GetPos();

			// 根本だったら
			if (pObj->GetKind() == Object::Kind::BLUE_MUSHROOM_NEMOTO)
			{
				// 動いてなかったら終わり
				if (!KasaSuction) return;

				pos.y = prevObjPos.y - 0.2f;		// 高さ調整
				deltaPos = INIT_DELTA_POS;			// 移動範囲を調整
				nCnt += 1;
				for (int i = 1; i < nCnt; i++)
				{
					deltaPos *= DELTA_POS;			// 前の根本よりも移動範囲が狭くなるように
				}
				// 根本だけ角度を変える
				// 傘の方に向ける
				ModelRotate(pObj, prevObjPos, pos);
			}
			else
			{
				KasaSuction = true;	// 動いてたらフラグ上げ
			}

			// 最初だけ到達座標を設定
			if (pObj->GetTime() < 0.1f)
			{
				pObj->SetEndPos(DirectX::XMFLOAT3(m_playerPos.x, pObj->GetPos().y, m_playerPos.z));
			}

			// ベクトルの差分を計算
			DirectX::XMVECTOR startVec = DirectX::XMLoadFloat3(&pos);
			DirectX::XMVECTOR endVec = DirectX::XMLoadFloat3(&pObj->GetEndPos());
			DirectX::XMVECTOR direction = DirectX::XMVectorSubtract(endVec, startVec);
			direction = DirectX::XMVector3Normalize(direction); // 正規化

			// 速度に基づいて移動距離を計算
			float frequency = 1.0f; // 周波数（変化の速さ）
			float radMinus;			// 範囲制限半径減算用

			// 根本のカウントが始まっていたら
			if (nCnt)
			{
				// サインカーブを使った速度の計算
				speed = -(((pObj->GetAmplitude() * deltaPos) * pObj->GetSuctionDis()) * sin(frequency * pObj->GetTime()));
				speed *= (pObj->GetWeight() * deltaPos);
			}
			// 始まっていなかったら
			else
			{
				// サインカーブを使った速度の計算
				speed = -((pObj->GetAmplitude() * pObj->GetSuctionDis()) * sin(frequency * pObj->GetTime()));
				speed *= pObj->GetWeight();
			}

			// 減速処理
			if (pObj->GetWeight() > 0.1f)
			{
				pObj->SetWeight(pObj->GetWeight() - WEIGHT_MINUS);
			}
			else
			{
				pObj->SetWeight(0.1f);
			}

			DirectX::XMVECTOR velocity = DirectX::XMVectorScale(direction, speed);
			// 時間（またはフレーム数）を更新
			pObj->SetTime(pObj->GetTime() + 0.1f);
			radMinus = pObj->GetTime() * 0.01f;

			// 現在の位置を更新
			DirectX::XMVECTOR currentVec = DirectX::XMLoadFloat3(&pos);
			currentVec = DirectX::XMVectorAdd(currentVec, velocity);
			DirectX::XMStoreFloat3(&pos, currentVec);

			// 原点からの新しい位置までの距離を計算
			DirectX::XMVECTOR originVec = DirectX::XMLoadFloat3(&origin);
			DirectX::XMVECTOR diffVecFromOrigin = DirectX::XMVectorSubtract(currentVec, originVec);

			// 原点(元の位置)からの距離を測る
			DirectX::XMFLOAT3 diffF3;									// 距離を測る用
			DirectX::XMStoreFloat3(&diffF3, diffVecFromOrigin);			// Float3に変換

			// 原点から離れすぎていないなら描画しない
			if (pObj->GetKind() == Object::Kind::BLUE_MUSHROOM_NEMOTO &&
				((diffF3.x > -0.02f && diffF3.x < 0.02f) && (diffF3.z > -0.02f && diffF3.z < 0.02f)))
			{
				pObj->SetDraw(false);	// 描画フラグ下げ
			}

			float distanceFromOriginSquared = DirectX::XMVectorGetX(DirectX::XMVector3LengthSq(diffVecFromOrigin));

			if (pObj->GetRadius() > 0.1f)
			{
				pObj->SetRadius(pObj->GetRadius() - radMinus);
			}
			if (pObj->GetRadius() <= 0.1f)
			{
				m_pPlayer->SetSuction(false);
				pObj->SetPlayGimmick(false);
				pObj->SetTime(0.0f);
				pObj->SetWeight(1.0f);
				pObj->SetRadius(0.0f);

				// 角度リセット
				m_fAngle = 0.0f;
				DirectX::XMFLOAT3 objangle;
				objangle.x = 0.0f;
				objangle.y = 0.0f;
				objangle.z = 0.0f;

				pObj->SetAngle(objangle);
				if (firstNemoto == 0 && pObj->GetKind() == Object::Kind::BLUE_MUSHROOM_NEMOTO)
				{
					firstNemoto++;
					pObj->SetDraw(true);	// 先頭の根本は描画する
				}
			}

			// 距離が半径の範囲内かどうかを確認
			if (distanceFromOriginSquared > pObj->GetRadius() * pObj->GetRadius())
			{
				// 到達可能な最も近い点を設定
				DirectX::XMVECTOR limitedVec = DirectX::XMVectorAdd(originVec, DirectX::XMVectorScale(DirectX::XMVector3Normalize(diffVecFromOrigin), pObj->GetRadius()));
				currentVec = limitedVec;
			}

			// 更新された位置を設定
			DirectX::XMStoreFloat3(&pos, currentVec);
			pObj->SetPos(pos);
			prevObjPos = pos;				// 一つ前のオブジェクトの座標として取っておく		
			
		}
	}
}

void Suction::SetPlayer(CPlayer * player)
{
	m_pPlayer = player;
}

void Suction::SetDrill(CDrill * drill)
{
	m_pDrill = drill;
}

void Suction::SetHammer(CHammer * hammer)
{
	m_pHammer = hammer;
}

void Suction::SetSaw(CSaw * saw)
{
	m_pSaw = saw;
}
