#ifndef __TUTORIALSIGNBOARD_H__
#define __TUTORIALSIGNBOARD_H__

//----�C���N���[�h��----
#include "Object.h"

//----- �N���X��` -----
class CTutorialSignboard : public Object
{
public:
	enum textureKind {
		suction,
		custom,
		shop,
		max
	};

public:
	CTutorialSignboard(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ, float rot, int kind);
	~CTutorialSignboard();	// �f�X�g���N�^

	

private:
	
};

#endif // __TUTORIALSIGNBOARD_H__
