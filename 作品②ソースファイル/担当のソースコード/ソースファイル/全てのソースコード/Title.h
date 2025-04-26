
#ifndef ___TITLE_H___
#define ___TITLE_H___
#include <DirectXMath.h>
#include "Defines.h"
#include "Sprite.h"
#include "Texture.h"
class TItle
{
public:
	TItle();
	~TItle();
	void Update();
	void Draw();
	bool AnimeButton();
	bool GetPlayerAnime();
private:
	/*int m_nclearTime;
	int m_nTimeMinutes;
	int m_nTimeSeconds;
	int m_nper;*/
	float m_Left, m_Right, m_Bottom, m_Top, m_near, m_far;
	
	Texture* m_pTexture[5];
	DirectX::XMFLOAT2 m_PlayerPos;
	DirectX::XMFLOAT2 m_PlayerSize;
	DirectX::XMFLOAT2 m_ButtonPos;
	DirectX::XMFLOAT2 m_ButtonSize;
	DirectX::XMFLOAT2 m_BGPos;
	DirectX::XMFLOAT2 m_BGSize;
	DirectX::XMFLOAT2 m_LogoPos;
	DirectX::XMFLOAT2 m_LogoSize;
	DirectX::XMFLOAT2 m_LogoBasePos;
	DirectX::XMFLOAT2 m_LogoBaseSize;
	int m_nMAXRatio;
	int m_nMAXRatio2;
	float m_fRatio;
	float m_fRatio2;
	float m_fRadius;
	float m_fRadian;
	float m_fRadian2;
	bool AnimeFinish;
	bool LogoAnime;
	bool PlayerAnime;


};

#endif // !___TITLE_BG_H___






