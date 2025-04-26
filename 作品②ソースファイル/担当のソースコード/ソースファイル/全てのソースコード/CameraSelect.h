//=================================================================
//
//	CameraSelect.h
//	�f���Z���N�g�V�[���̃J����
//
//=================================================================

#ifndef __CAMERA_SELECT_H__
#define __CAMERA_SELECT_H__

// ========== �C���N���[�h�� ==========
#include "CameraBase.h"

// ========== �N���X ==========
class CCameraSelect : public CameraBase
{
public:
	CCameraSelect();
	~CCameraSelect();
	void Init(int num);
	void Update();								// �X�V����
	DirectX::XMFLOAT4X4 GetViewMatrix();		// �J�������󂯓n��
	void SetGreen(Planet* green);				// �X�e�[�W1�|�C���^�󂯎��
	void SetMushroom(Planet* mushroom);			// �X�e�[�W2�|�C���^�󂯎��
	void SetWholeCake(Planet* wholecake);		// �X�e�[�W3�|�C���^�󂯎��
	void SetMoveLeft(int select);				// ���ړ��ݒ�
	void SetMoveRight(int select);				// �E�ړ��ݒ�
	bool GetMove();								// �J�����������Ă��邩

private:
	void MoveCamera();							// �J�����ړ�����

private:
	DirectX::XMFLOAT3 m_up;						// �J�����̌���
	bool m_moveLeft;							// �J�������ړ��t���O
	bool m_moveRight;							// �J�����E�ړ��t���O
	bool m_flg;
	int m_oldSelectPlanet;						// �I���ςݘf���ԍ�
	int m_frame;
	float m_radius;								// �f���ƃJ�����Ƃ̋���
	float m_lookRadius;							// �f���ƃJ�����œ_�Ƃ̋���
	float m_vertical;							// �J�����ʒu�A�c���W�A���p
	float m_horizon;							// �J�����ʒu�A�����W�A���p
	float m_angleVertical;						// �J�����ʒu�c�p�x
	float m_angleHorizon;						// �J�����ʒu���p�x
	float m_factor;
	float m_value;
	float m_cnt;
	Planet* m_pPlanet[CSceneMng::MAX_STAGE];	// �f���|�C���^
	DirectX::XMFLOAT3 m_lookPlanet;				// �f�����W
	DirectX::XMFLOAT3 m_startPlanet;			// �J�����ړ��J�n���W
	DirectX::XMFLOAT3 m_endPlanet;				// �J�����ړ��ڕW���W

};

#endif // !__CAMERA_SELECT_H__