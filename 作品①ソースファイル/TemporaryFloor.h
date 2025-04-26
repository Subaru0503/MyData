///////////////////////////////////////
//
// 一時的に出現する床ギミッククラス
//
// ネジの回し量によって一時的に出現する
// 回し量が満たなかったら消える
//
///////////////////////////////////////

// インクルードガード
#ifndef __TEMPORARY_FLOOR_H__
#define __TEMPORARY_FLOOR_H__

// インクルード部
#include "GimmickBase.h"
#include <vector>
#include "float3.h"

// クラス定義
class TemporaryFloor : public GimmickBase
{
public:

	// 一時的に出現する床を実現させるのに必要な情報
	struct TemporaryFloorData
	{
		// 自分の出現状態
		bool draw;

		// 次の床
		TemporaryFloorData* nextObj;

		// 一個前の床
		TemporaryFloorData* preObj;

		// 自分の番号
		int myNo;

		// 合計数
		int totalNo;
	};

public:

	// コンストラクタ
	TemporaryFloor(std::string name = "TemporaryFloor");

	// デストラクタ
	~TemporaryFloor();

	// ターゲットオブジェクトの処理
	void Gimmick(int index, float rotY);

	// 通常のネジを回す方向と逆方向に回されたときに呼ぶ
	void InvertGimmick(int index, float rotY);

	// 一時的に出現する床を実現させるのに必要な情報を設定する
	inline void SetTemporaryFloorInfo(TemporaryFloorData* pre, TemporaryFloorData* next, int no, int totalno)
	{
		// 一個前の床を設定する
		m_TemporaryFloorData.preObj = pre;

		// 次の床を設定する
		m_TemporaryFloorData.nextObj = next;

		// 自分の番号
		m_TemporaryFloorData.myNo = no;

		// 合計数
		m_TemporaryFloorData.totalNo = totalno;
	}

	//----ゲット関数----

	// 一時的に出現する床を実現させるのに必要な情報を返す
	inline TemporaryFloorData* GetTemporaryData()
	{
		return &m_TemporaryFloorData;
	}

private:

	// 一時的に出現する床に必要な情報
	TemporaryFloorData  m_TemporaryFloorData;

};

#endif // __TEMPORARY_FLOOR_H__