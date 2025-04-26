#ifndef __PLANET_H__
#define __PLANET_H__

//=====インクルード=====
#include <DirectXMath.h>
#include "Shader.h"
#include "Model.h"

/****************************************
*@brief セレクト画面に配置する惑星の処理
*****************************************/
class Planet
{
public:
	Planet();
	virtual ~Planet();
	void Update(float tick);
	void Draw(DirectX::XMFLOAT4X4* mat);
	DirectX::XMFLOAT3 GetPos();
	void StartFocus();
	void EndFocus();

protected:
	Model* m_pModel;		// モデルデータ
	VertexShader* m_pVS;	// 頂点シェーダー
	DirectX::XMFLOAT3 m_pos;	// 座標
	DirectX::XMFLOAT3 m_scale;	// 拡縮率
	DirectX::XMFLOAT3 m_rotate;	// 回転角度
	bool m_bFocus;				// 選択フラグ

};

#endif // !__PLANET_H__