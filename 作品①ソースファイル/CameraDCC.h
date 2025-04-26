#ifndef __CAMERA_DCC_H__
#define __CAMERA_DCC_H__

#include "Camera.h"
#include "GameObject.hpp"
#include <Windows.h>

class CameraDCC : public GameObject
{
private:
	//struct Argument
	//{
	//	DirectX::XMFLOAT2 mouseMove;
	//	DirectX::XMVECTOR vCamFront;
	//	DirectX::XMVECTOR vCamSide;
	//	DirectX::XMVECTOR vCamUp;
	//	DirectX::XMVECTOR vCamPos;
	//	DirectX::XMVECTOR vCamLook;
	//};
public:
	CameraDCC();
	~CameraDCC();
	void Update() final;

	// �^�[�Q�b�g���Z�b�g�֐�
	inline void ResetTarget()
	{
		m_target = nullptr;
	}

	// �Z�b�g�֐�
	inline void SetTarget(GameObject* obj)
	{
		m_target = obj;
		CamInitSetPos();			// �J�������W�����ݒ�
	}
private:
	void UpdateState();
	void CamInitSetPos();			// �J�������W�����ݒ�
	//void UpdateOrbit(Argument& arg);
	//void UpdateTrack(Argument& arg);
	//void UpdateDolly(Argument& arg);
	//void UpdateFlight(Argument& arg);
private:
	//int m_state;
	POINT m_oldPos;
	Camera* m_pComponent;
	GameObject* m_target;
};

#endif