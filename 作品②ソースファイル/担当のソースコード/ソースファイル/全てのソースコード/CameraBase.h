//CameraBase.h
#ifndef __CAMERA_BASE_H__
#define __CAMERA_BASE_H__
//=====インクルード部=====
#include <DirectXMath.h>
#include "SceneManager.h"
#include "Planet.h"

//=====クラス=====
class CameraBase
{
public:
	CameraBase();
	virtual ~CameraBase() {};
	virtual void Update() = 0;

	virtual DirectX::XMFLOAT4X4 GetViewMatrix();
	DirectX::XMFLOAT4X4 GetProjectionMatrix();
	DirectX::XMFLOAT4X4 GetNPViewMatrix();			// 転置前
	DirectX::XMFLOAT4X4 GetNPProjectionMatrix();	// 転置前
	DirectX::XMFLOAT3 GetPos();
	DirectX::XMFLOAT3 GetLook();
	virtual void SetGreen(Planet* green) = 0;
	virtual void SetMushroom(Planet* mushroom) = 0;
	virtual void SetWholeCake(Planet* wholecake) = 0;

protected:
	DirectX::XMFLOAT3 m_pos, m_look, m_up;	//ビュー行列の設定に必要な変数
	float m_fovy, m_aspect, m_near, m_far;	//プロジェクション行列の設定に必要な変数
	float m_radY, m_radXZ, m_rad;			//カメラの移動・回転に必要な変数
};

#endif