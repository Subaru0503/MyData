#ifndef __CANDLE_H__
#define __CANDLE_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class Candle : public Object
{
public:
	Candle(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ, int level);
	~Candle();	// デストラクタ
private:
};

#endif // __CANDLE_H__
