#ifndef __COOKIE_H__
#define __COOKIE_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class Cookie : public Object
{
public:
	Cookie(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ);
	~Cookie();	// デストラクタ
private:
};

#endif // __COOKIE_H__

