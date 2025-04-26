#ifndef __CAKEPIECE_H__
#define __CAKEPIECE_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class CakePiece : public Object
{
public:
	CakePiece(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ);
	~CakePiece();	// デストラクタ
private:
};

#endif // __CAKEPIECE_H__

