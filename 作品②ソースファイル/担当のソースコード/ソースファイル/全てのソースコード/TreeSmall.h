#ifndef __TREE_SMALL_H__
#define __TREE_SMALL_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class CTreeSmall : public Object
{
public:
	CTreeSmall(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ, CSoundMng* sound);
	~CTreeSmall();

private:
};

#endif // __TREE_SMALL_H__
