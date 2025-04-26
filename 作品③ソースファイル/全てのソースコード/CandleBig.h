#ifndef __CANDLEBIG_H__
#define __CANDLEBIG_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class CandleBig : public Object
{
public:
	CandleBig(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ, CSoundMng* sound);
	~CandleBig();	// デストラクタ
private:
};

#endif // __CANDLEBIG_H__
