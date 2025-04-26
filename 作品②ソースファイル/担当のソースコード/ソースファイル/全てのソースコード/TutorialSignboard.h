#ifndef __TUTORIALSIGNBOARD_H__
#define __TUTORIALSIGNBOARD_H__

//----インクルード部----
#include "Object.h"

//----- クラス定義 -----
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
	~CTutorialSignboard();	// デストラクタ

	

private:
	
};

#endif // __TUTORIALSIGNBOARD_H__
