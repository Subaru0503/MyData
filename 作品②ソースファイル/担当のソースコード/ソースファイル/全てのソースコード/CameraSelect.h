//=================================================================
//
//	CameraSelect.h
//	惑星セレクトシーンのカメラ
//
//=================================================================

#ifndef __CAMERA_SELECT_H__
#define __CAMERA_SELECT_H__

// ========== インクルード部 ==========
#include "CameraBase.h"

// ========== クラス ==========
class CCameraSelect : public CameraBase
{
public:
	CCameraSelect();
	~CCameraSelect();
	void Init(int num);
	void Update();								// 更新処理
	DirectX::XMFLOAT4X4 GetViewMatrix();		// カメラ情報受け渡し
	void SetGreen(Planet* green);				// ステージ1ポインタ受け取り
	void SetMushroom(Planet* mushroom);			// ステージ2ポインタ受け取り
	void SetWholeCake(Planet* wholecake);		// ステージ3ポインタ受け取り
	void SetMoveLeft(int select);				// 左移動設定
	void SetMoveRight(int select);				// 右移動設定
	bool GetMove();								// カメラが動いているか

private:
	void MoveCamera();							// カメラ移動処理

private:
	DirectX::XMFLOAT3 m_up;						// カメラの向き
	bool m_moveLeft;							// カメラ左移動フラグ
	bool m_moveRight;							// カメラ右移動フラグ
	bool m_flg;
	int m_oldSelectPlanet;						// 選択済み惑星番号
	int m_frame;
	float m_radius;								// 惑星とカメラとの距離
	float m_lookRadius;							// 惑星とカメラ焦点との距離
	float m_vertical;							// カメラ位置、縦ラジアン角
	float m_horizon;							// カメラ位置、横ラジアン角
	float m_angleVertical;						// カメラ位置縦角度
	float m_angleHorizon;						// カメラ位置横角度
	float m_factor;
	float m_value;
	float m_cnt;
	Planet* m_pPlanet[CSceneMng::MAX_STAGE];	// 惑星ポインタ
	DirectX::XMFLOAT3 m_lookPlanet;				// 惑星座標
	DirectX::XMFLOAT3 m_startPlanet;			// カメラ移動開始座標
	DirectX::XMFLOAT3 m_endPlanet;				// カメラ移動目標座標

};

#endif // !__CAMERA_SELECT_H__