//=================================================================
//
//	SceneStage3.h
//	�X�e�[�W�R�V�[��
//
//=================================================================
#ifndef __SCENE_STAGE3_H__
#define __SCENE_STAGE3_H__

// ========== �C���N���[�h�� ==========
#include "SceneStageBase.h"

// ========== �N���X =================
class CSceneStage3 : public CSceneStageBase
{
public:
	CSceneStage3(CSceneMng* pSceneMng, CSoundMng* pSoundMng);
	~CSceneStage3();
	void Update(float tick);
	void Draw();
	void StartCameraWork();

private:
	void DrawStage(DirectX::XMFLOAT4X4 * mat, VertexShader * vs);	// ���`��
	void LoadMap(list<Object*>* pObjList, list<CCollisionArea*>* pAreaList, CPlayer* pPlayer, CObjectMng* pObjMng);
};

#endif // !__SCENE_STAGE3_H__