//CameraDebug.h
#ifndef __CAMERA_DEBUG_H__
#define __CAMERA_DEBUG_H__

//=====�C���N���[�h��=====
#include "Input.h"
#include "CameraBase.h"

//=====�N���X=====
class CameraDebug : public CameraBase
{
public:
	CameraDebug();
	~CameraDebug() {}
	void Update();
	
};

#endif