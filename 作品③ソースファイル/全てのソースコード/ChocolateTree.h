#ifndef __CHOCOLATETREE_H__
#define __CHOCOLATETREE_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class ChocolateTree : public Object
{
public:
	ChocolateTree(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ, int level);
	~ChocolateTree();	// デストラクタ
private:
};

#endif // __CHOCOLATETREE_H__
