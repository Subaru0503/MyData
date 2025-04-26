#ifndef __BURNINGOBJECT_H__
#define __BURNINGOBJECT_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class CBurningObject : public Object
{
public:
	CBurningObject(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ);
	~CBurningObject();	// デストラクタ
private:
};

#endif // __BURNINGOBJECT_H__
