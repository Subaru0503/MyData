// �C���N���[�h��
#include "BoxCollider.h"

#include "CheckPointPath.h"

// �R���X�g���N�^
BoxCollider::BoxCollider()
	: m_isTrigger(false)
	, m_Collision(false)
{
	m_Scale = float3(0.5f, 0.5f, 0.5f);
}

// obb���m�̓����蔻��`�F�b�N
bool BoxCollider::CheckObb(GameObject* objA, GameObject* objB)
{
	// �e�����x�N�g���̊m��
	float3 NAe1 = float3::Tofloat3(objA->GetRight()), Ae1 = NAe1 * m_Scale.x;
	float3 NAe2 = float3::Tofloat3(objA->GetUp()), Ae2 = NAe2 * m_Scale.y;
	float3 NAe3 = float3::Tofloat3(objA->GetFront()), Ae3 = NAe3 * m_Scale.z;
	float3 NBe1 = float3::Tofloat3(objB->GetRight()), Be1 = NBe1 * objB->GetComponent<BoxCollider>()->GetScale().x;
	float3 NBe2 = float3::Tofloat3(objB->GetUp()), Be2 = NBe2 * objB->GetComponent<BoxCollider>()->GetScale().y;
	float3 NBe3 = float3::Tofloat3(objB->GetFront()), Be3 = NBe3 * objB->GetComponent<BoxCollider>()->GetScale().z;
	float3 Interval;
	if (objA->GetTag() == "Player")
	{
		DirectX::XMFLOAT3 posA = PlayerAdjust(objA);
		Interval = float3::Tofloat3(posA) - float3::Tofloat3(objB->GetPos());
	}
	else if (objB->GetTag() == "Player")
	{
		DirectX::XMFLOAT3 posB = PlayerAdjust(objB);
		Interval = float3::Tofloat3(objA->GetPos()) - float3::Tofloat3(posB);
	}
	else
	{
		Interval = float3::Tofloat3(objA->GetPos()) - float3::Tofloat3(objB->GetPos());
	}

	// ������ : Ae1
	float rA = Ae1.length();
	float rB = LenSegOnSeparateAxis(&NAe1, &Be1, &Be2, &Be3);
	float L = fabs(float3::dot(Interval, NAe1));
	if (L > rA + rB)
	{
		//m_Collision = false;
		return false; // �Փ˂��Ă��Ȃ�
	}
	
	// ������ : Ae2
	rA = Ae2.length();
	rB = LenSegOnSeparateAxis(&NAe2, &Be1, &Be2, &Be3);
	L = fabs(float3::dot(Interval, NAe2));
	if (L > rA + rB)
	{
		//m_Collision = false;
		return false;
	}
	
	// ������ : Ae3
	rA = Ae3.length();
	rB = LenSegOnSeparateAxis(&NAe3, &Be1, &Be2, &Be3);
	L = fabs(float3::dot(Interval, NAe3));
	if (L > rA + rB)
	{
		//m_Collision = false;
		return false;
	}
	
	// ������ : Be1
	rA = LenSegOnSeparateAxis(&NBe1, &Ae1, &Ae2, &Ae3);
	rB = Be1.length();
	L = fabs(float3::dot(Interval, NBe1));
	if (L > rA + rB)
	{
		//m_Collision = false;
		return false;
	}
	
	// ������ : Be2
	rA = LenSegOnSeparateAxis(&NBe2, &Ae1, &Ae2, &Ae3);
	rB = Be2.length();
	L = fabs(float3::dot(Interval, NBe2));
	if (L > rA + rB)
	{
		//m_Collision = false;
		return false;
	}
	
	// ������ : Be3
	rA = LenSegOnSeparateAxis(&NBe3, &Ae1, &Ae2, &Ae3);
	rB = Be3.length();
	L = fabs(float3::dot(Interval, NBe3));
	if (L > rA + rB)
	{
		//m_Collision = false;
		return false;
	}
	
	// ������ : C11
	float3 Cross;
	Cross = NAe1.cross(NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabs(float3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		//m_Collision = false;
		return false;
	}
	
	// ������ : C12
	Cross = NAe1.cross(NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabs(float3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		//m_Collision = false;
		return false;
	}
	
	// ������ : C13
	Cross = NAe1.cross(NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabs(float3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		//m_Collision = false;
		return false;
	}
	
	// ������ : C21
	Cross = NAe2.cross(NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabs(float3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		//m_Collision = false;
		return false;
	}
	
	// ������ : C22
	Cross = NAe2.cross(NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabs(float3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		//m_Collision = false;
		return false;
	}
	
	// ������ : C23
	Cross = NAe2.cross(NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabs(float3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		//m_Collision = false;
		return false;
	}
	
	// ������ : C31
	Cross = NAe3.cross(NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabs(float3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		//m_Collision = false;
		return false;
	}
	
	// ������ : C32
	Cross = NAe3.cross(NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabs(float3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		//m_Collision = false;
		return false;
	}
	
	// ������ : C33
	Cross = NAe3.cross(NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabs(float3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		//m_Collision = false;
		return false;
	}
	
	// �������ʂ����݂��Ȃ��̂Łu�Փ˂��Ă���v
	//m_Collision = true;
	return true;
}

// �������ɓ��e���ꂽ���������瓊�e���������Z�o
float BoxCollider::LenSegOnSeparateAxis(float3* Sep, float3* e1, float3* e2, float3* e3)
{
	// 3�̓��ς̐�Βl�̘a�œ��e���������v�Z
	// ������Sep�͕W��������Ă��邱��
	float r1 = fabs(float3::dot(*Sep, *e1));
	float r2 = fabs(float3::dot(*Sep, *e2));
	float r3 = e3 ? (fabs(float3::dot(*Sep, *e3))) : 0;
	return r1 + r2 + r3;
}

// ���W�␳
void BoxCollider::FixPos(GameObject* objB)
{
	// �^�O�擾
	// �����̃^�O���擾
	string objATag = transform->GetTag();

	// ����̃^�O���擾
	string objBTag = objB->GetTag();

	// �␳�������t���O
	bool check = false;

	// ����������̃^�O���`�F�b�N�|�C���g��H��M�~�b�N��������
	if (objATag == "CheckPointPath" ||
		objBTag == "CheckPointPath")
	{
		check = PushAdjust(objB);
	}

	// �ړ����ɏ���Ă�����
	if (transform->GetOnMoveFloor())
	{
		// �ړ����͈̔͊O�ɂ��邩����
		if (FloorInSide(objB))
		{
			// ���W�␳
			MoveGimmickFixPos(objB);
		}
		else
		{
			// �͈͊O
			transform->SetOnMoveFloor(false);
		}
	}

	// Y�����߂�����������
	if (objATag == "Player")
	{
		check = CheckHeightOnly(objB);
	}

	// �����␳�A�����o���̕␳�����Ă���I���
	if (check)
	{
		return;
	}

	// �ʏ�␳
	NormalFixPos(objB);
}

// �����o���ĕ␳
// �����o���̕␳������������true��Ԃ�
// �����o���̕␳������O�ɏI��������false��Ԃ�
bool BoxCollider::PushAdjust(GameObject * objB)
{
	// �ϐ��錾

	// �����̌��݂̍��W
	float3 objAPos = float3::Tofloat3(transform->GetPos());

	// �����̉ߋ����W
	float3 objAOldPos = float3::Tofloat3(transform->GetOldPos());

	// �����̃T�C�Y
	float3 objAScale = float3::Tofloat3(transform->GetScale());

	// ������������̍��W
	float3 objBPos = float3::Tofloat3(objB->GetPos());

	// ������������̉ߋ����W
	float3 objBOldPos = float3::Tofloat3(objB->GetOldPos());

	// ������������̃T�C�Y
	float3 objBScale = float3::Tofloat3(objB->GetScale());

	// �ړ���
	float3 movePos[2];

	// �V�������W
	float3 newPos = objAPos;

	// �����̃^�O���擾
	string tag = transform->GetTag();

	// ����̃^�O�擾
	string tagB = objB->GetTag();

	// �M�~�b�N�e�N���X
	GimmickBase* gimmickBase[2];

	// �n�ʂɓ��������t���O
	bool groundCollision[2];

	// �M�~�b�N�̐e�N���X�ɃL���X�g
	gimmickBase[0] = dynamic_cast<GimmickBase*>(transform);
	gimmickBase[1] = dynamic_cast<GimmickBase*>(objB);

	// �M�~�b�N�ȊO�̂��܂܂�Ă��牟���o���̕␳�̏������Ȃ�
	if (!gimmickBase[0] || !gimmickBase[1])
	{
		return false;
	}

	// �n�ʂɓ��������t���O���擾
	groundCollision[0] = gimmickBase[0]->GetGroundCollision();
	groundCollision[1] = gimmickBase[1]->GetGroundCollision();

	// �n�ʂɓ������Ă��牟���o���̕␳�̏��������Ȃ�
	if (groundCollision[0] || groundCollision[1])
	{
/*		if (!groundCollision[0])
		{
			gimmickBase[1]->SetGroundCollision(false);
		}
		else */if (groundCollision[1])
		{
			gimmickBase[0]->SetGroundCollision(true);
		}
		return false;
	}

	// �ړ����̈ړ������ʂ����߂�
	movePos[0] = objAPos - objAOldPos;
	movePos[1] = objBPos - objBOldPos;


	// �␳�����V�������W���Z�b�g
	newPos.x += movePos[1].x;
	newPos.z += movePos[1].z;

	// �f�[�^�ϊ����ĐV�������W��ݒ�
	transform->SetPos(float3::ToXMFLOAT3(newPos));

	// �`�F�b�N�|�C���g��H��M�~�b�N��
	// �ړ��M�~�b�N�ɉ�����Ă���
	if (tag == "CheckPointPath" && tagB == "MoveGimmick"
		&& movePos[0] == float3(0.0f, 0.0f, 0.0f))
	{
		// �`�F�b�N�|�C���g�̏����폜
		CheckPointPath* checkPointPath = dynamic_cast<CheckPointPath*>(transform);
		checkPointPath->AllDeleteCheckPoint();
	}

	return true;
}

// �����݂̂̕␳������+�␳������
bool BoxCollider::CheckHeightOnly(GameObject * objB)
{
	// ���������I�u�W�F�N�g���W�擾
	float3 objBPos = float3::Tofloat3(objB->GetPos());

	// ���������I�u�W�F�N�g�T�C�Y�擾
	float3 objBScale = float3::Tofloat3(objB->GetScale());

	// �ߋ����W�擾
	DirectX::XMFLOAT3 objAOldPos = transform->GetOldPos();

	// �v���C���[�T�C�Y
	DirectX::XMFLOAT3 objAScale = transform->GetScale();

	// �ߋ����W�̍���������̃T�C�Y���O����������
	if (!(objBPos.y + objBScale.y / 2.0f > objAOldPos.y + objAScale.y / 2.0f &&
		objBPos.y - objBScale.y / 2.0f < objAOldPos.y + objAScale.y / 2.0f))
	{
		// �ړ����Ƃ̓����蔻��Ȃ炻��p�ɕ␳����
		if (objB->GetTag() == "MoveGimmick")
		{
			MoveGimmickFixPos(objB);
			return true;
		}
		// y���W�����߂�
		// ������O�̍��W�ɖ߂�
		DirectX::XMFLOAT3 newPos = objAOldPos;

		// x���W�͖߂��Ȃ�
		newPos.x = transform->GetPos().x;

		// �����������ɖ߂�
		newPos.y += objAScale.y / 2.0f;

		// z���W�͖߂��Ȃ�
		newPos.z = transform->GetPos().z;

		if (newPos.y > objBPos.y)
		{
			newPos.y = objBPos.y + objBScale.y / 2.0f;
		}

		// ���W�␳
		transform->SetPos(newPos);
		return true;
	}
	return false;
}

// �ړ����͈̔͊O�ɂ��邩���肷��֐�
bool BoxCollider::FloorInSide(GameObject * objB)
{
	// �ϐ��錾
	// �����̌��݂̍��W���擾
	float3 objAPos = float3::Tofloat3(transform->GetPos());

	// ����̌��݂̍��W���擾
	float3 objBPos = float3::Tofloat3(objB->GetPos());

	// ����̃T�C�Y���擾
	float3 objBScale = objB->GetComponent<BoxCollider>()->GetScale();

	// �͈͓����m�F
	if (objAPos.x + m_Scale.x > objBPos.x - objBScale.x &&
		objAPos.x - m_Scale.x < objBPos.x + objBScale.x &&
		objAPos.z + m_Scale.z > objBPos.z - objBScale.z &&
		objAPos.z - m_Scale.z < objBPos.z + objBScale.z)
	{
		// �͈͓�
		return true;
	}

	// �͈͊O
	return false;
}

// �ړ����p�̍��W�␳
void BoxCollider::MoveGimmickFixPos(GameObject * objB)
{
	// �ϐ��錾
	// �����̌��݂̍��W���擾
	float3 objAPos = float3::Tofloat3(transform->GetPos());

	// �����̃T�C�Y���擾
	float3 objAScale = float3::Tofloat3(transform->GetScale());

	// ����̌��݂̍��W���擾(�ړ���)
	float3 objBPos = float3::Tofloat3(objB->GetPos());

	// ����̉ߋ����W���擾
	float3 objBOldPos = float3::Tofloat3(objB->GetOldPos());

	// ����̃T�C�Y���擾
	float3 objBScale = float3::Tofloat3(objB->GetScale());

	// �ړ���
	float3 movePos;

	// �V�������W
	float3 newPos = objAPos;

	// �ړ����ɏ����
	transform->SetOnMoveFloor(true);

	// �ړ����̈ړ������ʂ����߂�
	movePos = objBPos - objBOldPos;

	// �␳�����V�������W���Z�b�g
	newPos.x += movePos.x;
	newPos.y = objBPos.y + objBScale.y / 2.0f;
	newPos.z += movePos.z;

	// �V�������W���Z�b�g
	transform->SetPos(float3::ToXMFLOAT3(newPos));
}

// �ʏ�␳
void BoxCollider::NormalFixPos(GameObject * objB)
{
	// �����̃^�O���擾
	string objATag = transform->GetTag();

	// ����̃^�O���擾
	string objBTag = objB->GetTag();

	// ���������I�u�W�F�N�g���W�擾
	float3 objBPos = float3::Tofloat3(objB->GetPos());

	// ���ʂ̖@���ɑ΂���OBB�̎ˉe���̒������Z�o
	float r = 0.0f;

	// ����̍��W���擾
	float3 objBNormal = float3::Tofloat3(objB->GetPos());
	objBNormal = objBNormal.normalize();

	float3 NAe1 = float3::Tofloat3(transform->GetRight()), Ae1 = NAe1 * m_Scale.x;
	float3 NAe2 = float3::Tofloat3(transform->GetUp()), Ae2 = NAe2 * m_Scale.y;
	float3 NAe3 = float3::Tofloat3(transform->GetFront()), Ae3 = NAe3 * m_Scale.z;

	r += fabs(float3::dot(Ae1, objBNormal));
	r += fabs(float3::dot(Ae2, objBNormal));
	r += fabs(float3::dot(Ae3, objBNormal));


	// ���ʂ�OBB�̋������Z�o
	float3 objAPos = float3::Tofloat3(transform->GetPos());
	float3 distance = objAPos - objBPos;

	float s = float3::dot(distance, objBNormal);

	float3 direction;							// ����
	if (distance.length() > 0.0f)
	{
		direction = distance.normalize();		// ���K��
	}
	else
	{
		direction = float3(0.0f, 0.0f, 0.0f);	// �f�t�H���g�l
	}
	// �߂��������Z�o
	float Len = 0.0f;
	if (s > 0)
	{
		Len = r - fabs(s);
	}
	else
	{
		Len = r + fabs(s);
	}

	//if (fabs(s) - r < 0.0f)
	//{
		// ������O�̍��W�ɖ߂�
	DirectX::XMFLOAT3 newPos = transform->GetOldPos();//float3::ToXMFLOAT3(objAPos + direction * Len);

	// �V�������W���Z�b�g
	transform->SetPos(newPos);

	// �`�F�b�N�|�C���g��H��M�~�b�N��
	// �ړ��M�~�b�N��������
	if ((objATag == "CheckPointPath" || objATag == "MoveGimmick") &&
		(objBTag == "MoveGimmick" || objBTag == "CheckPointPath"))
	{
		// �O�̃��[�v�ŏ����ς݂̂��̂�������ꏏ�ɕ␳
		int objANo = extractNumber(transform->GetName());
		int objBNo = extractNumber(objB->GetName());

		if (objANo > objBNo)
		{
			objB->SetPos(objB->GetOldPos());
		}
	}
//}
}

// �v���C���[�̍��W�^�񒆂ɕ␳
DirectX::XMFLOAT3 BoxCollider::PlayerAdjust(GameObject * obj)
{
	// �V�������W���擾
	DirectX::XMFLOAT3 pos = obj->GetPos();

	// �v���C���[�̌��_���^�񒆉��ɂȂ��Ă���̂�
	// �^�񒆂ɍ��킹��
	pos.y += obj->GetScale().y / 2.0f;

	return pos;
}

// �����̐��l���擾����
int BoxCollider::extractNumber(const string & str)
{
	std::string numStr;

	// ������̌�납�琔���𒊏o
	for (int i = str.size() - 1; i >= 0; --i)
	{
		if (isdigit(str[i]))
		{
			numStr = str[i] + numStr;
		}
		else
		{
			break;
		}
	}

	return numStr.empty() ? 0 : std::stoi(numStr);
}
