//=================================================================
//
//	SceneStage3.h
//	ステージ３シーン
//
//=================================================================
#ifndef __SCENE_STAGE3_H__
#define __SCENE_STAGE3_H__

// ========== インクルード部 ==========
#include "SceneStageBase.h"

// ========== クラス =================
class CSceneStage3 : public CSceneStageBase
{
public:
	CSceneStage3(CSceneMng* pSceneMng, CSoundMng* pSoundMng);
	~CSceneStage3();
	void Update(float tick);
	void Draw();
	void StartCameraWork();

private:
	void DrawStage(DirectX::XMFLOAT4X4 * mat, VertexShader * vs);	// 陸描画
	void LoadMap(list<Object*>* pObjList, list<CCollisionArea*>* pAreaList, CPlayer* pPlayer, CObjectMng* pObjMng);
};

#endif // !__SCENE_STAGE3_H__