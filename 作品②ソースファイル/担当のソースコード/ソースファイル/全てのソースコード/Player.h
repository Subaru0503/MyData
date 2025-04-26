//Player.h
#ifndef __PLAYER_H__
#define __PLAYER_H__

//=====�C���N���[�h��=====
#include <DirectXMath.h>
#include "ObjectManager.h"
#include "Model.h"
#include "Shader.h"
#include "Suction.h"		// �z�����݋@�\�N���X
#include "Value.h"
#include "Shop.h"
#include "UI.h"
#include "SoundManager.h"
#include "Effect.h"
#include "RunSmoke.h"
#include "ESuction.h"
#include "EStun.h"
#include "XController.h"
#include "Drill.h"
#include "Saw.h"
#include "Hammer.h"
//=====�N���X=====
class CPlayer
{
public:
	CPlayer();
	~CPlayer();

	enum Direct
	{
		DIRECT_UP = 0,
		DIRECT_DOWN,
		DIRECT_LEFT,
		DIRECT_RIGHT,
		DIRECT_UPR,
		DIRECT_UPL,
		DIRECT_DOWNR,
		DIRECT_DOWNL,
	};

	void Update(float tick);														//�X�V����
	void Draw();
	void MoveModel(float deltaX, float deltaZ);							//���f���ړ�

	DirectX::XMFLOAT3	GetPos();										//���W�󂯓n��
	DirectX::XMFLOAT3	GetMove();										//�ړ��ʎ󂯓n��
	DirectX::XMFLOAT3	GetCameraPos();
	DirectX::XMFLOAT3	GetOldPos();									//�ߋ����W�󂯓n��
	DirectX::XMFLOAT3	GetScale();										//�T�C�Y�󂯓n��
	DirectX::XMFLOAT4X4 GetWorldMatrix();								//���[���h�s��󂯓n��
	DirectX::XMFLOAT4X4 GetViewMatrix();								//�r���[�s��󂯓n��
	DirectX::XMFLOAT4X4 GetProjectionMatrix();							//�v���W�F�N�V�����s��󂯓n��
	DirectX::XMFLOAT4X4 GetNViewMatrix();								//�]�u�Ȃ��r���[�s��󂯓n��
	DirectX::XMFLOAT4X4 GetNProjectionMatrix();							//�]�u�Ȃ��v���W�F�N�V�����s��󂯓n��
	DirectX::XMFLOAT3 GetForwardVector();								//�O�����x�N�g���擾
	DirectX::XMFLOAT3 GetRightVector();									//�������x�N�g���擾
	DirectX::XMFLOAT3 GetUpRightVector();
	DirectX::XMFLOAT3 GetUpLeftVector();
	int GetRandKind();													// ������n�ʂ̎�ނ�n��
	int GetRandHeight();												// ������n�ʂ̍�����n��
	bool GetRandSlope();												// ��̏ォ
	bool GetRandBiscuit();												// �r�X�P�b�g�̏�ɂ��邩
	bool GetShop();														// �w����ʂɈڂ�t���O�̃Q�b�g	// �ύX�_
	int* GetMoney();													// �������Q�b�g�֐�
	int* GetCustom();													// �����J�X�^�}�C�Y�p�[�c�Q�b�g�֐�
	float GetRadius();
	Suction* GetSuction();												// �z�����݃N���X�Q�b�g
	float GetRad();														// �v���C���[�̃��W�A���p�Q�b�g
	bool GetTrade();
	bool GetTutorial();													// �`���[�g���A����ʕ\���t���O

	void SetObjectMng(CObjectMng* pCObjectMng);							// �I�u�W�F�N�gMng�̃|�C���^��ݒ�
	void SetPos(DirectX::XMFLOAT3 pos);									// �v���C���[���W��ݒ�
	void SetMoney(int money);
	void SetPosX(float posx);
	void SetPosY(float posy);
	void SetPosZ(float posz);
	void SetCameraPosX(float camPosX);
	void SetCameraPosY(float camPosY);
	void SetCameraPosZ(float camPosZ);
	void SetCamRadius(float radius);
	void SetHorizon(float horizon);
	void SetTrade(bool trade);
	void SetShop(bool Shop);											// �w����ʃt���O���� // �ύX�_
	void SetRandKind(int crntGround);									// ������n�ʂ̎�ސݒ�
	void SetRandHeight(int crntHeight);									// ������n�ʂ̍����ݒ�
	void SetRandSlope(bool slope);										// ��̏�ɂ��邩�t���O���Z�b�g
	void SetRandBiscuit(bool is);										// �r�X�P�b�g�̏�ɂ��邩�t���O���Z�b�g
	void SetSoundMng(CSoundMng* soundMng);								// �T�E���h���̎󂯎��
	void SetItem(int drink, int nozzle);								// �A�C�e�����g�p���ꂽ��
	void SetUI(CUI* ui);	// �������f�[�^�擾
	void SetTutorial(bool, int);										// �`���[�g���A���Ŕ͈͓��t���O
	void SetSuction(bool suction);
	void SetTutorialDraw(bool);	// �`���[�g���A���\���t���O
	int GetTutorialNum();
	bool IsTutorial();
	void StopSound();//�z������se��~
	void LoadEffect();
	void SetDrill(bool* m_bDrill);										//�J�X�^���p�[�c
	void SetSaw(bool* m_bSaw);											//�J�X�^���p�[�c
	void SetHammer(bool* m_bHammer);									//�J�X�^���p�[�c
	void SetShopCustom(CShop* shop);									//�J�X�^���p�[�c
private:
	void Footsteps(XINPUT_STATE state);													// �n�ʂ̎�ނő�������
	DirectX::XMFLOAT3 m_pos, m_oldPos, m_scale, m_camPos, m_look, m_up;	// �v���C���[���W�A�v���C���[�ߋ����W�A�傫���A�J�������W�A�œ_�A�J���������
	DirectX::XMFLOAT3 m_move;											// �ړ����x
	float m_fovy, m_aspect, m_near, m_far;								// ����p�A��ʔ䗦�A�ߋ������e���E�A���������E
	float m_radius, m_horizon, m_vertical;								// �v���C���[�܂ł̋������a�A�J�������s�ړ����W�A���p�A�c�ړ�
	float m_angleHorizon, m_angleVertical;								// �J�������s�ړ��p�x�A�c�ړ��p�x
	float m_directRad, m_directAngle;									// �v���C���[���W�A���p�A�p�x(��)
	int m_direct;
	int m_nCustom[MAX_CUSTOM];											// �J�X�^�}�C�Y�p�[�c����
	int m_nMoney;														// ������
	char str[256];														// �E�B���h�E������
	int  m_nTime;														// �o�ߎ���
	float m_fTimeLimit;													// ��������
	bool m_trade;
	float m_gravity;
	bool m_bShop;														// �w����ʂɈڂ�t���O
	int m_nCandleDemerit;												// �낤�����̃f�����b�g�t���O
	int m_nDemelitFrame;												// �f�����b�g�̎���
	int m_randKind;														// ������n�ʂ̎��(���A���Aetc)
	int m_randHeight;													// ������n�ʂ̍���
	bool m_randSlope;													// ��̏ォ
	bool m_randBiscuit;													// �r�X�P�b�g�̏ォ
	bool m_tutorial, m_tutorialDraw;									// �`���[�g���A����ʕ\���t���O
	bool m_suction;
	bool* m_bDrill;														//�J�X�^���p�[�c
	bool* m_bSaw;														//�J�X�^���p�[�c
	bool* m_bHammer;
	CTutorialSignboard::textureKind m_tutorialKind;						// �`���[�g���A���Ŕ̎��
	Model::AnimeNo anime[5];
	DirectX::XMFLOAT3 m_oldPlayerForward;	// �v���C���[�����ޔ�p

	CObjectMng* m_pObjectMng;
	Model* m_pModel;
	VertexShader* m_pVS;
	Suction* m_pSuction;					// �z�����݋@�\�N���X�|�C���^
	CUI* m_pUI_Money;						// UI(������)
	CSoundMng* m_pSoundMng;					// �T�E���h����p

	Effect* m_pEffect;
	RunSmoke* m_pRunSmoke;
	ESuction* m_pESuction;
	EStun* m_pEStun;
	CDrill* m_pDrill;						//�J�X�^���p�[�c
	CSaw* m_pSaw;							//�J�X�^���p�[�c
	CHammer* m_pHammer;						//�J�X�^���p�[�c
	CShop* m_pshop;
	bool IsMove;//�y���G�t�F�N�g
	bool Pmove;
	bool Pvaccum;
	XINPUT_STATE state;
	XINPUT_KEYSTROKE stroke;
	//----�A�C�e���g�p�m�F�p----
	int m_nDrink;							// �h�����N�t���O
	int m_nNozzle;							// �m�Y�������t���O

	Texture* m_pShadowTex;
};

#endif