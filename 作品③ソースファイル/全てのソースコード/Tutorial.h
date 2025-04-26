#ifndef ___TUTORIAL_H___
#define ___TUTORIAL_H___

#include <DirectXMath.h>
#include "Defines.h"
#include "Sprite.h"
#include "Texture.h"
#include "Player.h"

class Tutorial
{
public:

	Tutorial();
	~Tutorial();
	void Update();
	void Draw(int num);
	void DrawIcon();
	void SetPlayer(CPlayer* player);
	void SetPos(DirectX::XMFLOAT3 pos);
private:
	Texture* m_pTexture[4];
	Texture* m_pIconTex;
	DirectX::XMFLOAT3 m_pos;
	CPlayer* m_pPlayer;
	int m_nMaxRatio;
	float m_fRatio;


};


#endif // !___TUTORIAL_H___

