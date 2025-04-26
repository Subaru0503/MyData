#ifndef __RUBBISH_H__
#define __RUBBISH_H__

//----インクルード部----
#include "Object.h"

class CRubbish : public Object
{
public:
	// 親クラスの引数付きコンストラクタに引数を渡すコンストラクタ
	CRubbish(float posX, float posY, float posZ);
	~CRubbish();

private:
};

#endif // __RUBBISH_H__
