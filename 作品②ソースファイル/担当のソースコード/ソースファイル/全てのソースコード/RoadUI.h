#ifndef ___ROAD_UI_H___
#define ___ROAD_UI_H___

#include <DirectXMath.h>
#include "Defines.h"
#include "Sprite.h"
#include "Texture.h"

class Road
{
public:
	Road();
	~Road();
	void Update(int StageNum);
	void Draw();
	void SetRatio();

private:
	DirectX::XMFLOAT3 m_RoadUIPos;
	DirectX::XMFLOAT2 m_RoadUISize;
	DirectX::XMFLOAT3 m_TipsPos;
	DirectX::XMFLOAT2 m_TipsSize;

	int m_nMaxRatio;
	float m_fRatio;
	float m_fRadian;
	Texture* m_pTexture[6];
	int m_nStageNum;
	int m_nFrame;
	int m_nSwitchFlg;
	float m_fAlpha;

};

#endif // !___ROADUI_H___