//=====�C���N���[�h��=====
#include "CameraDebug.h"

//=====�}�N����`=====
#define CAMERA_ROTATION_SPEED (0.1f)
#define CAMERA_MOVE_SPEED (0.1f)

CameraDebug::CameraDebug()
{
}

//=====�X�V����=====
void CameraDebug::Update()
{
	//��������,Shift,Ctrl�ŃJ�����̒����_�𓮂���
	if (IsKeyPress(VK_UP))			{ m_look.z += CAMERA_ROTATION_SPEED; }
	if (IsKeyPress(VK_DOWN))		{ m_look.z -= CAMERA_ROTATION_SPEED; }
	if (IsKeyPress(VK_LEFT))		{ m_look.x -= CAMERA_ROTATION_SPEED; }
	if (IsKeyPress(VK_RIGHT))		{ m_look.x += CAMERA_ROTATION_SPEED; }
	if (IsKeyPress(VK_SHIFT))		{ m_look.y += CAMERA_ROTATION_SPEED; }
	if (IsKeyPress(VK_CONTROL))		{ m_look.y -= CAMERA_ROTATION_SPEED; }

	// W,A,S,D,Q,E�ŃJ�����̈ʒu(�����_�����ɂ�����])�𓮂���
	if (IsKeyPress('W')) { m_radY  -= CAMERA_MOVE_SPEED; }	// ��
	if (IsKeyPress('S')) { m_radY  += CAMERA_MOVE_SPEED; }	// ��
	if (IsKeyPress('D')) { m_radXZ -= CAMERA_MOVE_SPEED; }	// �E
	if (IsKeyPress('A')) { m_radXZ += CAMERA_MOVE_SPEED; }	// ��
	if (IsKeyPress('Q')) { m_rad   += CAMERA_MOVE_SPEED; }	// �߂Â�
	if (IsKeyPress('E')) { m_rad   -= CAMERA_MOVE_SPEED; }	// �����

	// �ړ��p�x���J�������W�ɐݒ�
	m_pos.x = cos(m_radY) * sin(m_radXZ) * m_rad + m_look.x;
	m_pos.y = sin(m_radY) * m_rad + m_look.y;
	m_pos.z = cos(m_radY) * cos(m_radXZ) * m_rad + m_look.z;
}
