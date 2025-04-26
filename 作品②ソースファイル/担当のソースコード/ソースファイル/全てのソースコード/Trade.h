//Trade.h
//=====�C���N���[�h�K�[�h=====
#ifndef __TRADE_H__
#define __TRADE_H__

//=====�C���N���[�h��=====
#include "Player.h"
#include "Model.h"
#include "Shader.h"

//=====�N���X=====
class CTrade
{
public:
	CTrade(float posX, float posY, float posZ, float Rot);
	~CTrade();
	void Update(float tick);
	void Draw();
	void SetPlayer(CPlayer* player);
	float GetRadius();
	DirectX::XMFLOAT4X4 GetWorldMatrix();		//���[���h�s��󂯓n��
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