// Suction.h
#ifndef __SUCTION_H_
#define __SUCTION_H_

///////////
//INCLUDE
/////////
#include <DirectXMath.h>	// ���ώZ�o��
#include "Object.h"			// �I�u�W�F�N�g���擾���ύX�p
#include <list>				// �I�u�W�F�N�g���X�g�󂯎��p
#include "Value.h"
#include "ESuction.h"
#include "Drill.h"
#include "Saw.h"
#include "Hammer.h"
/**
*@brief	�z�����݋@�\
*/

class CPlayer;

class Suction
{
public:
	Suction();
	~Suction();
	void IsObjectInSuctionRange(std::list<Object*>* pObjectList, DirectX::XMFLOAT3, DirectX::XMFLOAT3,int* Custom);
	void SuctionObject(int *CandleDemelit, int *Custom);
	void NozzleLevelUp();				// �m�Y������
	void PowerUP();						// �p���[�A�b�v
	void SetESuction(ESuction* pEsuction);
	void PlayGimmick();
	void ReleaseGimmick();
	void SetPlayer(CPlayer* player);
	void SetDrill(CDrill* drill);
	void SetHammer(CHammer* hammer);
	void SetSaw(CSaw* saw);
	int GetNozzleLevel();
	bool GetStart();
private:
	bool CheckHeightLink(Object* pObj);	// �I�u�W�F�N�g�ƃv���C���[�����������ɂ��邩
	void ModelRotate(Object* pObj, DirectX::XMFLOAT3 playerPos, DirectX::XMFLOAT3 pos);					// ���f������]������
private:
	float m_suctionRange;				// �z�����ݗL������
	float m_suctionAngle;				// �z�����ݗL���p�x
	float m_suctionSeconds;				// �z�����ݑ��x�i1�b�ɉ����[�g���z�����ނ��j
	std::list<Object*>*  m_pObjectList;	// ���肷��I�u�W�F�N�g���X�g
	DirectX::XMVECTOR m_playerForward;	// �v���C���[�����x�N�g���i�[�p
	DirectX::XMFLOAT3 m_playerPos;		// �v���C���[���W�i�[�p
	int m_nozzleLevel;					// �m�Y�����x��
	float m_fPower;						// �z����
	bool m_start;						// �I�u�W�F�N�g���X�g�����������̂�҂�
	ESuction* m_pESuction;
	CPlayer* m_pPlayer;
	DirectX::XMFLOAT3 prevObjPos;		// ��O�̃I�u�W�F�N�g�̍��W
	float m_fAngle;						// X���ŉ�]������p�x
	CDrill* m_pDrill;
	CHammer* m_pHammer;
	CSaw* m_pSaw;
};


#endif // !__SUCTION_H_
