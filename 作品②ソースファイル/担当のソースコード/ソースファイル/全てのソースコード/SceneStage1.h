//=================================================================
//
//	SceneStage1.h
//	ステージ１関連
//
//=================================================================

#ifndef __SCENE_STAGE1_H__
#define __SCENE_STAGE1_H__

// ========== インクルード部 ==========
#include "SceneStageBase.h"	// シーン遷移処理用

// ========== クラス ==========
class CSceneStage1 : public CSceneStageBase
{
public:
	CSceneStage1(CSceneMng* pSceneMng, CSoundMng* pSoundMng);
	~CSceneStage1();
	void Update(float tick);
	void Draw();
	void StartCameraWork();

private:
	void DrawStage(DirectX::XMFLOAT4X4 * mat, VertexShader * vs);	// 陸描画
	void LoadMap(list<Object*>* pObjList, list<CCollisionArea*>* pAreaList, CPlayer* pPlayer, CObjectMng* pObjMng);
};

#endif // !__SCENE_STAGE1_H__