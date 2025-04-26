//=====インクルード部=====
#include "CameraDebug.h"

//=====マクロ定義=====
#define CAMERA_ROTATION_SPEED (0.1f)
#define CAMERA_MOVE_SPEED (0.1f)

CameraDebug::CameraDebug()
{
}

//=====更新処理=====
void CameraDebug::Update()
{
	//←↑→↓,Shift,Ctrlでカメラの注視点を動かす
	if (IsKeyPress(VK_UP))			{ m_look.z += CAMERA_ROTATION_SPEED; }
	if (IsKeyPress(VK_DOWN))		{ m_look.z -= CAMERA_ROTATION_SPEED; }
	if (IsKeyPress(VK_LEFT))		{ m_look.x -= CAMERA_ROTATION_SPEED; }
	if (IsKeyPress(VK_RIGHT))		{ m_look.x += CAMERA_ROTATION_SPEED; }
	if (IsKeyPress(VK_SHIFT))		{ m_look.y += CAMERA_ROTATION_SPEED; }
	if (IsKeyPress(VK_CONTROL))		{ m_look.y -= CAMERA_ROTATION_SPEED; }

	// W,A,S,D,Q,Eでカメラの位置(注視点を軸にした回転)を動かす
	if (IsKeyPress('W')) { m_radY  -= CAMERA_MOVE_SPEED; }	// 上
	if (IsKeyPress('S')) { m_radY  += CAMERA_MOVE_SPEED; }	// 下
	if (IsKeyPress('D')) { m_radXZ -= CAMERA_MOVE_SPEED; }	// 右
	if (IsKeyPress('A')) { m_radXZ += CAMERA_MOVE_SPEED; }	// 左
	if (IsKeyPress('Q')) { m_rad   += CAMERA_MOVE_SPEED; }	// 近づく
	if (IsKeyPress('E')) { m_rad   -= CAMERA_MOVE_SPEED; }	// 離れる

	// 移動角度をカメラ座標に設定
	m_pos.x = cos(m_radY) * sin(m_radXZ) * m_rad + m_look.x;
	m_pos.y = sin(m_radY) * m_rad + m_look.y;
	m_pos.z = cos(m_radY) * cos(m_radXZ) * m_rad + m_look.z;
}
