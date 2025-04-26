//SceneGame.h
#ifndef __SCENE_STAGE2_H__
#define __SCENE_STAGE2_H__
//=====�C���N���[�h��=====
#include "SceneStageBase.h"

//=====�N���X=====
class CSceneStage2 : public CSceneStageBase
{
public:
	CSceneStage2(CSceneMng* pSceneMng, CSoundMng* pSoundMng);
	~CSceneStage2();
	void Update(float tick);
	void Draw();
	void StartCameraWork();

private:
	void LoadMap(list<Object*>* pObjList, list<CCollisionArea*>* pAreaList, CPlayer* pPlayer, CObjectMng* pObjMng);
	void DrawStage(DirectX::XMFLOAT4X4 * mat, VertexShader * vs);	// ���E��E�C�`��

private:
};


#endif // __SCENE_STAGE2_H__