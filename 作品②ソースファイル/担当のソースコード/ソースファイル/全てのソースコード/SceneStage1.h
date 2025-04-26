//=================================================================
//
//	SceneStage1.h
//	�X�e�[�W�P�֘A
//
//=================================================================

#ifndef __SCENE_STAGE1_H__
#define __SCENE_STAGE1_H__

// ========== �C���N���[�h�� ==========
#include "SceneStageBase.h"	// �V�[���J�ڏ����p

// ========== �N���X ==========
class CSceneStage1 : public CSceneStageBase
{
public:
	CSceneStage1(CSceneMng* pSceneMng, CSoundMng* pSoundMng);
	~CSceneStage1();
	void Update(float tick);
	void Draw();
	void StartCameraWork();

private:
	void DrawStage(DirectX::XMFLOAT4X4 * mat, VertexShader * vs);	// ���`��
	void LoadMap(list<Object*>* pObjList, list<CCollisionArea*>* pAreaList, CPlayer* pPlayer, CObjectMng* pObjMng);
};

#endif // !__SCENE_STAGE1_H__