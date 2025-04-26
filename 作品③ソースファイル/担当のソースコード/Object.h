// Object.h
#ifndef __OBJECT_H__
#define __OBJECT_H__

//=====�C���N���[�h=====
#include <DirectXMath.h>
#include "Shader.h"
#include "MeshBuffer.h"
#include "Model.h"
#include "ModelManager.h"
#include "SoundManager.h"
#include "DustCloud.h"
#include "TrailEffect.h"
#include "Defines.h"
#include "Sprite.h"
#include "Texture.h"
/******************************
*@brief	�I�u�W�F�N�g���N���X
******************************/
class Object
{
public:
	// �I�u�W�F�N�g�̎��
	enum Kind
	{
		NONE,
		TREE,			// ��
		ROCK,			// ��
		HOUSE,			// ��
		BURNINGOBJECT,	//�R���Ă�I�u�W�F�N�g
		FENCE,			// �t�F���X
		SIGNBOARD,		// �Ŕ�
		TUTORIALSIGNBOARD,	// �`���[�g���A���Ŕ�
		MUSHROOM,		// �L�m�R
		MUSHROOMCAT,	// �˂����̂�
		RUBBISH,		// �S�~
		STONE,			// ����
		WOOD,			// �؍�
		METAL,			// �|��
		// STAGE 3
		DONUTS,			// �h�[�i�c 
		CAKEPIECE,		// �W�����P�[�L
		STRAWBERRY,		// ������
		APOLO,			// �A�|��
		COOKIE,			// �N�b�L�[
		CHOCOLATETREE,	// �`���R�̖�
		CANDYROCK,		// �L�����f�B�[��
		CHOCOLATEFENCE,	// �`���R�v���[�g�i�t�F���X�j
		CHOCOLATEPIECE,	// �`���R�̂�����
		CANDYPIECE,		// �L�����f�B�[�̂�����
		CANDLE,			// �낤����
		SWEETSHOUSE,	// ���َq�̉�
		// �M�~�b�N
		BLUE_MUSHROOM,			// �L�m�R
		BLUE_MUSHROOM_NEMOTO,	// �L�m�R�̍��{
		BISCUIT,				// �r�X�P�b�g
		BISCUITPIECE,			// �r�X�P�b�g�̂�����
	};
private:
	// ������`�悷��ۂ̒��_���\����
	struct LineVertex
	{
		float pos[3];
		float color[4];
	};
	// �|���S����`�悷��ۂ̒��_���\����
	struct Vertex
	{
		float pos[3];
		float uv[2];
	};
public:
	// �`�揉���ʒu�A�X�P�[���A�A���O���������Ɏ��R���X�g���N�^
	Object(float posX, float posY, float posZ);
	virtual ~Object();					// �f�X�g���N�^

	void Init();				// ����������
	void Uninit();				// �I������
	virtual void Update(float tick);	// �X�V����

	void SetWorld(DirectX::XMFLOAT4X4 world);		// �萔�o�b�t�@�֑���f�[�^�Ƀ��[���h���W�ϊ��s����Z�b�g
	void SetView(DirectX::XMFLOAT4X4 view);			// �萔�o�b�t�@�֑���f�[�^�Ƀr���[���W�ϊ��s����Z�b�g
	void SetProjection(DirectX::XMFLOAT4X4 proj);	// �萔�o�b�t�@�֑���f�[�^�Ƀv���W�F�N�V�������W�ϊ��s����Z�b�g
	void SetBoxMove(float x = 0.0f, float y = 0.0f, float z = 0.0f);		// Box�ړ�����
	void SetSphereMove(float x = 0.0f, float y = 0.0f, float z = 0.0f);		// Sphere�ړ�����

	void AddLine(DirectX::XMFLOAT3 start, DirectX::XMFLOAT3 end,
		DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));	// �`�悷�������ǉ����鏈��
	void DrawLines();	// ������`�悷�鏈��

	void DrawBox(DirectX::XMFLOAT4X4*);			// Box�`�揈��
	void DrawCylinder(DirectX::XMFLOAT4X4*);	// Cylinder�`�揈��
	void DrawSphere(DirectX::XMFLOAT4X4*);		// Sphere�`�揈��

	int GetKind();					// �I�u�W�F�N�g�̎�ޔԍ���Ԃ�
	DirectX::XMFLOAT3 GetScale();	// �X�P�[����Ԃ�
	bool GetDelete();				// �폜�t���O��Ԃ�
	void SetDelete();				// �폜�t���O�𗧂Ă�
	int GetMoney();					// �z�����񂾂����̉��l��Ԃ�
	bool IsDrop();					// �h���b�v�A�j���[�V���������Ԃ�
	DirectX::XMFLOAT3 GetAngle();	// ��]�p�x

	void SetDropFlg(bool isDrop);	// �h���b�v���t���O���Z�b�g
	void SetSound(CSoundMng* sound);

private:
	void MakeVS();			// ���_�V�F�[�_�쐬
	void MakePS();			// �s�N�Z���V�F�[�_�쐬
	void MakeLineShader();	// �����p�V�F�[�_�쐬

private:
	void MakeLine();		// �����̒��_�o�b�t�@�쐬 
	void MakeBox();			// Box�̒��_�o�b�t�@�쐬
	void MakeCylinder();	// Cylinder�̒��_�o�b�t�@�쐬
	void MakeSphere();		// Sphere�̒��_�o�b�t�@�쐬
	const int MAX_LINE_NUM = 1000;	// shiran
	const int CIRCLE_DETAIL = 16;	// shiran

private:
	MeshBuffer* m_pBox;			// Box�̒��_�o�b�t�@�ւ̃|�C���^
	MeshBuffer* m_pCylinder;	// Cylinder�̒��_�o�b�t�@�ւ̃|�C���^
	MeshBuffer* m_pSphere;		// Sphere�̒��_�o�b�t�@�ւ̃|�C���^
	MeshBuffer* m_pLines;		// �����̒��_�o�b�t�@�ւ̃|�C���^
	Shader* m_pVS;				// ���_�V�F�[�_�̃|�C���^
	Shader* m_pPS;				// �s�N�Z���V�F�[�_�̃|�C���^
	Shader* m_pLineShader[2];		// �����p�V�F�[�_�̃|�C���^
	DirectX::XMFLOAT4X4 m_WVP[3];	// �萔�o�b�t�@�֏������ރf�[�^�̃|�C���^
	void* m_pLineVtx;				// shiran
	int m_lineCnt;					// shiran

public:
	DirectX::XMFLOAT3 GetPos();				// �I�u�W�F�N�g�̍��W��Ԃ�
	DirectX::XMFLOAT3 GetOldPos();			// 1�t���[���O�̍��W��Ԃ�
	DirectX::XMFLOAT3 GetDownVector();		// �������ւ̃x�N�g����Ԃ�
	void SetPos(DirectX::XMFLOAT3);			// ���W���Z�b�g
	void SetAngle(DirectX::XMFLOAT3 angle);	// ��]���Z�b�g
	void SetScale(DirectX::XMFLOAT3 scale);	// �T�C�Y���Z�b�g
	void SetMat(DirectX::XMFLOAT4X4*);		// �萔�o�b�t�@�|�C���^�w��p
	void SetVelocity(float);				// �ړ����x���Z�b�g
	void SetDirection(DirectX::XMVECTOR);	// �ړ������x�N�g�����Z�b�g
	bool IsSuction();						// �z�����܂ꒆ�t���O��Ԃ�
	void SetSuctionFlg(bool);				// �z�����܂ꒆ�t���O�Z�b�g
	int GetCreateNum();						// �j�󂳂ꂽ���ɐ�������I�u�W�F�N�g�̌�
	void SetPosX(float posx);				// X���W�Z�b�g
	void SetPosY(float posy);				// Y���W�Z�b�g
	void SetPosZ(float posz);				// Z���W�Z�b�g
	void SetPlayerPosY(float posY);			// �v���C���[Y���W�Z�b�g
	float GetMass();						// ���ʂ�Ԃ�
	void SetModelManager(ModelManager* modelManager);	// ���f���}�l�[�W���[�������o�ɃZ�b�g
	void SetModelData();								// �I�u�W�F�N�g�̎�ނɉ����ă��f���f�[�^���擾 
	void SetRandHeight(int crntHeight);		// ������n�ʂ̍����ݒ�
	void SetRandSlope(bool slope);			// ��̏�ɂ��邩�t���O���Z�b�g

	bool GetGimmick();						// �M�~�b�N���ǂ����̎󂯓n��
	bool GetPlayGimmick();					// �M�~�b�N���s��Ԏ󂯓n��
	void SetPlayGimmick(bool play);			// �M�~�b�N�Đ��̃Z�b�g
	bool GetSuctionGimmick();				// �M�~�b�N�z�����܂��Ԏ󂯓n��
	void SetSuctionGimmick(bool suction);	// �M�~�b�N�z�����܂��ԃZ�b�g
	float GetAmplitude();					// �M�~�b�N�X�s�[�h�v�Z�p�T�C���U�ꕝ�󂯓n��
	void SetAmplitude(float amplitude);
	float GetTime();						// �M�~�b�N�^�C���󂯓n��
	void SetTime(float time);
	float GetWeight();						// �M�~�b�N�X�s�[�h�������l�󂯓n��
	void SetWeight(float weight);
	float GetRadius();						// �M�~�b�N�L�т�͈͎󂯓n��
	void SetRadius(float radius);
	float GetSuctionDis();					// �M�~�b�N�z�����݌��E���W�Ƃ̔䗦�󂯓n��
	void SetSuctionDis(float dis);
	DirectX::XMFLOAT3 GetEndPos();			// �M�~�b�N�ڕW���W�󂯓n��
	void SetEndPos(DirectX::XMFLOAT3 endPos);
	DirectX::XMFLOAT3 GetGimmickOldPos();	// �M�~�b�N�������W�󂯓n��

	virtual void DrawModel(DirectX::XMFLOAT4X4* mat, VertexShader* vs);	// ���f���̕`��
	Model* GetModel();						// ���f���f�[�^�̃|�C���^��Ԃ�
	int GetLevel();							// ���x����Ԃ�
	bool IsShake();							// �h��t���O��Ԃ�
	void SetShake(bool OnOff);				// �h��t���O���Z�b�g
	bool IsMove();							// �ړ��t���O�擾
	void SetAngleToPlayer(float angle);		// �p�x�Z�b�g
	float GetAngleToPlayer();				// �p�x�Q�b�g
	bool GetDraw();
	void SetDraw(bool draw);
	void SetTime(int time);					// ���ԏ��Z�b�g
	std::string GetModelKey();
	void SetTouch(bool touch);				// player�ڐG���t���O�Z�b�g
	bool IsGetMoney();
	void SetGetMoney(bool getMoney);
	void SetPlayerPos(DirectX::XMFLOAT3 playerPos);
	int GetTutorialKind();					// �\���`���[�g���A���摜�̎�ޓn��
	void SetDust(Dust * pDust);

	bool GetEfkDestory();					//�j��G�t�F�N�g�Q�b�g
	void SetEfkDestory(bool pEDestoy);
	int GetRandHeight();					// ������n�ʂ̍�����n��
	bool GetRandSlope();					// ��̏ォ
	void DrawIcon(DirectX::XMFLOAT3 pos, int kind, int level,CPlayer* pPlayer);
	int GetDefCnt();						//�r�X�P�b�g�ϋv�l�Q�b�g
protected:
	DirectX::XMFLOAT4X4* m_mat;
	DirectX::XMFLOAT3 m_pos, m_scale, m_rotate;
	float m_PlayerPosY;					// �v���C���[�̍��WY
	DirectX::XMFLOAT3 m_oldPos;
	DirectX::XMFLOAT3 m_oldSize;		// Box�T�C�Y�ޔ�p�ϐ�
	DirectX::XMFLOAT3 m_oldScale;		// �T�C�Y�ޔ�p�ϐ�
	DirectX::XMVECTOR m_moveDirection;	// �ړ������x�N�g��
	int m_randHeight;					// ������n�ʂ̍���
	bool m_randSlope;					// ��̏ォ
	float m_velocity;					// ���x
	float m_lastVel;					// �Ō��Suction�ŃZ�b�g���ꂽ���x
	float m_gravity;					// �d��
	bool m_bSuction;					// �z�����܂ꒆ�t���O
	bool m_bGimmickSuction;				// �M�~�b�N�z�����܂�t���O
	int m_nKind;						// �I�u�W�F�N�g�̎��
	bool m_bDelete;						// �폜�t���O
	int m_nMoney;						// �Q�b�g�ł��邨��
	int m_createNum = 0;				// �j�󂳂ꂽ���ɐ�������I�u�W�F�N�g�̌�
	float m_mass;						// ����
	bool m_draw;
	bool m_bDrop;						// �h���b�v���̖��G�^�C���t���O
	bool m_EfkDestory;					// �j��G�t�F�N�g�t���O
	DirectX::XMVECTOR m_dropDirection;
	float dropTime;						// �h���b�v�A�j���[�V�����̌o�ߎ���
	float dropJump;						// �h���b�v���̃W�����v��
	bool m_bDropJump;					// �h���b�v���̃W�����v�t���O
	bool m_bTutorial;					// �`���[�g���A����bUI�\���t���O
	bool m_bTutorialTrigger;			// �`���[�g�����J�n�t���O
	int m_nTuturoalKind;					// �\������`���[�g���A���摜�̎��

	Model* m_pModel;				// ���f���f�[�^�i�[�p
	ModelManager* m_pModelManager;	// ���f���f�[�^�擾�p
	std::string m_modelKey;			// ���f���}�b�v�̃L�[

	float m_modelRatio;	// ���f���̊g�k��
	int m_nLevel;		// �I�u�W�F�N�g�̃��x��
	bool m_bShake;		// �h��t���O
	bool m_bMove;		// �ړ��t���O
	float m_angleToPlayer;	// �v���C���[�̐��ʂƁA�����ƃv���C���[���Ȃ��������Ƃ̊Ԃ̊p�x
	int m_noldTime;		// 30�b�o�������v�Z���邽�߂̒l�ޔ�
	int m_nTime;		// ���݂̎���
	int m_nLevelDown;	// ���x���_�E���t���O
	int m_nDefCnt;		// �ϋv��(�r�X�P�b�g)
	float m_fOnTime;	// �I�u�W�F�N�g�̏�ɂ���o�ߎ���
	bool m_bTouch;		// �v���C���[�ƐڐG����
	bool m_bOldTouch;	// �O��́��̒l�̑ޔ�p
	bool m_bGetMoney;	// �������𑝂₷���ǂ����̃t���O
	bool m_bGimmick;	// �M�~�b�N�I�u�W�F�N�g���ǂ���
	bool m_bPlayGimmick;		// �M�~�b�N���s�t���O
	bool m_bSuctionGimmick;		// �z�����܂ꂽ��
	float m_amplitude;			// �ړ����x�U�ꕝ
	float m_time;				// �T�C���p�^�C�}�[
	float m_weight;				// �ړ����x�����p
	float m_radius;				// �ړ��\�͈͂̔��a
	float m_suctionDis;			// �M�~�b�N�z�����݌��E���W�Ƃ̔䗦
	float m_fallTime;			// ��������
	DirectX::XMFLOAT3 m_playerPos;
	DirectX::XMFLOAT3 m_gimmickOldPos;	// �M�~�b�N�p�ߋ����W
	DirectX::XMFLOAT3 m_endPos;	// �ړ�����W

	DirectX::XMFLOAT3 m_shakePos;	// �h��A�N�V�������̍��W���
	Dust* m_pDust;
	CSoundMng* m_pSoundMng;
	TrailEffect* m_pTrail;	// �O�ՃG�t�F�N�g
	bool m_bTrailSet;			// 
	Texture* m_pTexture;
	int m_nMaxRatio;
	float m_fRatio;
};

#endif // __OBJECT_H__
