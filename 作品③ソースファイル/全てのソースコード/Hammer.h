#ifndef __HAMMER_H__
#define __HAMMER_H__

#include "Model.h"
#include "Shader.h"
#include <DirectXMath.h>

class CHammer
{
public:
	CHammer();
	~CHammer();

	void Update(float tick);
	void Draw(DirectX::XMFLOAT4X4 *mat, VertexShader* vs);
	void SetPlayerPos(DirectX::XMFLOAT3 pos);

	void HammerAnimetion();
private:

	DirectX::XMFLOAT4X4 m_WVP[3];

	Model* m_pModel;
	VertexShader* m_pVS;

	DirectX::XMFLOAT3 m_pos;
	DirectX::XMFLOAT3 m_scale, m_rotate;
	float m_directRad;

	float HammerCount;

	Model::AnimeNo anime[2];
};

#endif