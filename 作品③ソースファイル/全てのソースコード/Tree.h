#ifndef __TREE_H__
#define __TREE_H__

//----�C���N���[�h��----
#include "Object.h"

//----�N���X��`----
class CTree : public Object
{
public:
	CTree(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ, int level);
	~CTree();

private:
};

#endif // __TREE_H__