#ifndef ___SHOP_BG_H___
#define ___SHOP_BG_H___


#include <DirectXMath.h>
#include "Defines.h"
#include "Sprite.h"
#include "Texture.h"

class ShopBG
{
public:
	ShopBG();
	~ShopBG();
	void Draw();
	

private:
	float m_Left, m_Right, m_Bottom, m_Top, m_near, m_far;
	Texture* m_pTexture;
};


#endif // !___SHOP_BG_H___

