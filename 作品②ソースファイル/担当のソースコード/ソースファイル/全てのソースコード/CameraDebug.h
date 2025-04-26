//CameraDebug.h
#ifndef __CAMERA_DEBUG_H__
#define __CAMERA_DEBUG_H__

//=====インクルード部=====
#include "Input.h"
#include "CameraBase.h"

//=====クラス=====
class CameraDebug : public CameraBase
{
public:
	CameraDebug();
	~CameraDebug() {}
	void Update();
	
};

#endif