#ifndef __CHOCOLATETREE_H__
#define __CHOCOLATETREE_H__

//----�C���N���[�h��----
#include "Object.h"

//----�N���X��`----
class ChocolateTree : public Object
{
public:
	ChocolateTree(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ, int level);
	~ChocolateTree();	// �f�X�g���N�^
private:
};

#endif // __CHOCOLATETREE_H__
