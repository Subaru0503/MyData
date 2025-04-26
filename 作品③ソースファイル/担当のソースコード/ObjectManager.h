//----�C���N���[�h�K�[�h----
#ifndef __OBJECT_MANAGER__
#define __OBJECT_MANAGER__

//----�C���N���[�h��----
#include <DirectXMath.h>
#include "Defines.h"
#include "SoundManager.h"
#include "Suction.h"
#include "Model.h"
#include "ModelManager.h"		// ���f���}�l�[�W���[
// ----- �X�e�[�W�P -----
#include "Signboard.h"			// �Ŕ�
#include "Tree.h"				// ��
#include "Rubbish.h"			// �S�~
#include "Wood.h"				// �؍�
#include "WoodRoyal.h"			// �؍�(���x��4�p)
#include "Rock.h"				// ��
#include "Stone.h"				// ��
#include "StoneRoyal.h"				// ��(���x���S�p)
#include "House.h"				// ��
#include "Fence.h"				// ��
// ----- �X�e�[�W�Q -----
#include "Mushroom.h"			// ���̂�
// ----- �X�e�[�W3 -----
#include "ChocolateTree.h"		// �`���R�̖�
#include "CandyRock.h"			// �L�����f�B��
#include "SweetsHouse.h"		// ���َq�̉�
#include "ChocolatePiece.h"		// �`���R�̔j��
#include "ChocolatePieceRoyal.h"		// �`���R�̔j��(���x���S�p)
#include "CandyPiece.h"			// �L�����f�B�̔j��
#include "CandyPieceRoyal.h"			// �L�����f�B�̔j��(���x���S�p)
#include "ChocolateFence.h"		// �`���R�̃t�F���X
#include "Candle.h"				// �낤����
#include "Donuts.h"				// �h�[�i�c
#include "CakePiece.h"			// �P�[�L
#include "Strawberry.h"			// �C�`�S
#include "Apolo.h"				// �A�|��
#include "Cookie.h"				// �N�b�L�[
#include "BiscuitPiece.h"		// �r�X�P�b�g�̂�����
// ----- �M�~�b�N -----
#include "BlueMushroom.h"		// �L�m�R
#include "Biscuit.h"			// �r�X�P�b�g
#include "TutorialSignboard.h"	// �`���[�g���A���Ŕ�
// ------�G�t�F�N�g-----
#include "DustCloud.h"
#include "leaf.h"
#include "Bag.h"
// �I�u�W�F�N�g���X�g�p
#include <list>
using namespace std;

// �O���錾
class CPlayer;

//----�N���X��`----
class CObjectMng
{
public:
	typedef struct {	// �z�����݃t���O
		int tree1;
		int tree2;
		int tree3;
		int rock1;
		int rock2;
		int rock3;
		int fence;
		int signBoard;
	}FirstSuction;

public:
	CObjectMng();							// �R���X�g���N�^	
	~CObjectMng();							// �f�X�g���N�^

	void Update(float tick);				// �X�V
	void Draw(DirectX::XMFLOAT4X4 *mat);	// �`��

	void CreateObject(Object* pObj);		// �I�u�W�F�N�g�쐬

	list<Object*>* GetObjectList();			// �I�u�W�F�N�g���X�g�̃|�C���^��n��

	int GetTotalObjNum();					// �X�e�[�W�J�n���̋z�����߂�I�u�W�F�N�g�̑�����Ԃ�
	//void AddSuctionedObjNum();			// �z�����񂾃I�u�W�F�N�g�̃J�E���g���s��
	int GetSuctionedObjNum();				// ���݂܂łɋz�����񂾃I�u�W�F�N�g�̐���Ԃ�
	FirstSuction* GetFirstSuctionFlg();		// ���z�����݃t���O���擾

	void SetTotalObjNum(int totalObjNum);	// �z�����߂�I�u�W�F�N�g�̑�����ݒ�
	void ModelSetting();					// �I�u�W�F�N�g�Ƀ��f�����Z�b�g����
	void SetSuction(Suction* suction);
	void SetSound(CSoundMng* sound);
	void SetTime(int time);					// ���ԃZ�b�g
	void SetPlayer(CPlayer* pPlayer);
	void SetDust(Dust* pDust);
	void SetLeaf(Leaf* pLeaf);
	void SetBag(EBag * pBag);
private:
	list<Object*> m_ObjectList;				// �I�u�W�F�N�g���X�g

	int m_totalObjNum;						// �X�e�[�W�J�n���̋z�����߂�I�u�W�F�N�g�̑���
	int m_sucionedObjNum;					// ���݂܂łɋz�����񂾃I�u�W�F�N�g�̐�
	FirstSuction m_firstSuccsion;			// ���z�����݃t���O

	CSoundMng* m_pSoundMng;
	Suction* m_pSuction;
	ModelManager* m_pModelManager;			// ���f���}�l�[�W���[
	VertexShader* m_pVS;

	Model* m_pModel;
	CPlayer* m_pPlayer;
	//�G�t�F�N�g
	Dust* m_pDust;
	Leaf* m_pLeaf;
	EBag* m_pEBag;
	int m_nTime;							// ��������
};

#endif