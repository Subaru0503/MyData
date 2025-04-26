#ifndef __DRILL_H__
#define __DRILL_H__

#include "Model.h"
#include "Shader.h"
#include <DirectXMath.h>

class CDrill
{
public:
	CDrill();
	~CDrill();

	void Update(float tick);
	void Draw(DirectX::XMFLOAT4X4 *mat, VertexShader* vs);
	void SetPlayerPos(DirectX::XMFLOAT3 pos);

	void DrillAnimetion();
private:

	DirectX::XMFLOAT4X4 m_WVP[3];

	Model* m_pModel;
	VertexShader* m_pVS;

	DirectX::XMFLOAT3 m_pos;
	DirectX::XMFLOAT3 m_scale, m_rotate;
	float m_directRad;

	float DrillCount;


	Model::AnimeNo anime[2];
};

#endif