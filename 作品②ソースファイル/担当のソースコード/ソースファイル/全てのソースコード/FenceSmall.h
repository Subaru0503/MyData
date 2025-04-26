#ifndef __FENCESMALL_H__
#define __FENCESMALL_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class CFenceSmall : public Object
{
public:
	CFenceSmall(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ, float rot, CSoundMng* sound);
	~CFenceSmall();	// デストラクタ
private:
};

#endif // __FENCESMALL_H__
