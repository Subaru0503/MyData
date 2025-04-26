//Trade.h
//=====インクルードガード=====
#ifndef __TRADE_H__
#define __TRADE_H__

//=====インクルード部=====
#include "Player.h"
#include "Model.h"
#include "Shader.h"

//=====クラス=====
class CTrade
{
public:
	CTrade(float posX, float posY, float posZ, float Rot);
	~CTrade();
	void Update(float tick);
	void Draw();
	void SetPlayer(CPlayer* player);
	float GetRadius();
	DirectX::XMFLOAT4X4 GetWorldMatrix();		//ワールド行列受け渡し
	DirectX::XMFLOAT3 GetPos();
	DirectX::XMFLOAT3 GetAngle();
	void DrawIcon(DirectX::XMFLOAT3 pos);
	void SetPos(DirectX::XMFLOAT3 pos);
protected:
	DirectX::XMFLOAT3 m_pos, m_scale, m_angle;
	float m_radius;
private:
	CPlayer* m_pPlayer;
	Model* m_pModel;
	VertexShader* m_pVS;
	Texture* m_pTradeIcon;
	Texture* m_pTutorialIcon;
	int m_nMaxRatio;
	float m_fRatio;
	DirectX::XMFLOAT4X4 inv;
	DirectX::XMMATRIX matinv;
	DirectX::XMFLOAT3 IconPos;
	Model::AnimeNo anime;
};

#endif //__TRADE_H__