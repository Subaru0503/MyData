#ifndef __SIGNBOARD_H__
#define __SIGNBOARD_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class CSignboard : public Object
{
public:
	CSignboard(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ, float rot);
	~CSignboard();	// デストラクタ
private:
};

#endif // __SIGNBOARD_H__
