#ifndef __TREE_SMALL_H__
#define __TREE_SMALL_H__

//----�C���N���[�h��----
#include "Object.h"

//----�N���X��`----
class CTreeSmall : public Object
{
public:
	CTreeSmall(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ, CSoundMng* sound);
	~CTreeSmall();

private:
};

#endif // __TREE_SMALL_H__
