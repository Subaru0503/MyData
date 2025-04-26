// Suction.h
#ifndef __SUCTION_H_
#define __SUCTION_H_

///////////
//INCLUDE
/////////
#include <DirectXMath.h>	// 内積算出等
#include "Object.h"			// オブジェクト情報取得＆変更用
#include <list>				// オブジェクトリスト受け取り用
#include "Value.h"
#include "ESuction.h"
#include "Drill.h"
#include "Saw.h"
#include "Hammer.h"
/**
*@brief	吸い込み機能
*/

class CPlayer;

class Suction
{
public:
	Suction();
	~Suction();
	void IsObjectInSuctionRange(std::list<Object*>* pObjectList, DirectX::XMFLOAT3, DirectX::XMFLOAT3,int* Custom);
	void SuctionObject(int *CandleDemelit, int *Custom);
	void NozzleLevelUp();				// ノズル強化
	void PowerUP();						// パワーアップ
	void SetESuction(ESuction* pEsuction);
	void PlayGimmick();
	void ReleaseGimmick();
	void SetPlayer(CPlayer* player);
	void SetDrill(CDrill* drill);
	void SetHammer(CHammer* hammer);
	void SetSaw(CSaw* saw);
	int GetNozzleLevel();
	bool GetStart();
private:
	bool CheckHeightLink(Object* pObj);	// オブジェクトとプレイヤーが同じ高さにいるか
	void ModelRotate(Object* pObj, DirectX::XMFLOAT3 playerPos, DirectX::XMFLOAT3 pos);					// モデルを回転させる
private:
	float m_suctionRange;				// 吸い込み有効距離
	float m_suctionAngle;				// 吸い込み有効角度
	float m_suctionSeconds;				// 吸い込み速度（1秒に何メートル吸い込むか）
	std::list<Object*>*  m_pObjectList;	// 判定するオブジェクトリスト
	DirectX::XMVECTOR m_playerForward;	// プレイヤー方向ベクトル格納用
	DirectX::XMFLOAT3 m_playerPos;		// プレイヤー座標格納用
	int m_nozzleLevel;					// ノズルレベル
	float m_fPower;						// 吸引力
	bool m_start;						// オブジェクトリストが生成されるのを待つ
	ESuction* m_pESuction;
	CPlayer* m_pPlayer;
	DirectX::XMFLOAT3 prevObjPos;		// 一つ前のオブジェクトの座標
	float m_fAngle;						// X軸で回転させる角度
	CDrill* m_pDrill;
	CHammer* m_pHammer;
	CSaw* m_pSaw;
};


#endif // !__SUCTION_H_
