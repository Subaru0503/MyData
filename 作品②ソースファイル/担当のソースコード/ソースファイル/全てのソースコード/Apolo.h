#ifndef __APOLO_H__
#define __APOLO_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class Apolo : public Object
{
public:
	Apolo(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ);
	~Apolo();	// デストラクタ
private:
};

#endif // __APOLO_H__
