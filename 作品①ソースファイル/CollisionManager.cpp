// �C���N���[�h��
#include "CollisionManager.h"

// �R���|�[�l���g
#include "BoxCollider.h"
#include "Scanner.h"
#include "ModelRenderer3D.h"

// �X�V����
void CollisionManager::Update()
{
	// �R���C�_�[�t���̃I�u�W�F�N�g�̓����蔻��`�F�b�N���[�v
	for (auto itA = m_pObjList.begin(); itA != m_pObjList.end(); ++itA)
	{
		// ��̂ɂȂ�I�u�W�F�N�g
		GameObject* objA = *itA;

		// BoxCollider�R���|�[�l���g
		BoxCollider* _objABoxCollider = objA->GetComponent<BoxCollider>();

		// �X�L���i�R���|�[�l���g
		Scanner* _objAScanner = objA->GetComponent<Scanner>();

		// �^�O�擾
		string tag = objA->GetTag();

		if (_objABoxCollider)
		{
			// �t���O���Z�b�g
			_objABoxCollider->SetCollision(false);
		}

		// �X�L���i�R���|�[�l���g�����邩�m�F
		if (_objAScanner)
		{
			// �t���O�����Z�b�g
			_objAScanner->SetCollision(false);
		}
		// ����̃^�O�ȊO�͂����ŏI���
		else if(tag != "Goal" && tag != "CheckPointPath")
		{
			continue;
		}

		for (auto itB = m_pObjList.begin(); itB != m_pObjList.end(); ++itB)
		{
			// �Q�[���I�u�W�F�N�g�^�ɕϊ�
			GameObject* objB = *itB;

			// �I�u�W�F�N�gA�̍��W���擾
			float3 objAPos = float3::Tofloat3(objA->GetPos());

			// �I�u�W�F�N�gB�̍��W���擾
			float3 objBPos = float3::Tofloat3(objB->GetPos());

			// �I�u�W�F�N�gA�ƃI�u�W�F�N�gB�̋������v�Z
			float distance = float3::distance(objAPos, objBPos);

			// 3D���f�������_���[�R���|�[�l���g�擾
			ModelRenderer3D* modelRenderer3D = objB->GetComponent<ModelRenderer3D>();

			// �I�u�W�F�N�g�i���o�[���������(�����I�u�W�F�N�g)�������Ȃ�
			// �����蔻������Ȃ��^�O�������珈�����Ȃ�
			// ���ȏ㋗��������Ă��珈�����Ȃ�
			// �`�悵�ĂȂ��I�u�W�F�N�g�͏������Ȃ�
			if (objA->Get3DObjNo() == objB->Get3DObjNo() ||
				_objABoxCollider->CheckTag(objB) ||
				distance > 15.0f ||
				(modelRenderer3D && !modelRenderer3D->GetDrawFlg()))
			{
				continue;
			}

			// ����ɃI�u�W�F�N�g�����邩�X�L����
			if (_objAScanner &&
				_objAScanner->CheckObb(objA, objB))
			{
				// �X�L��������Ăяo��
				objA->OnScanner(objB);

				// ���m�����t���O���グ��
				_objAScanner->SetCollision(true);
			}

			// obb�����蔻��`�F�b�N
			if (modelRenderer3D && !_objABoxCollider->GetIsTrigger() &&
				_objABoxCollider->CheckObb(objA, objB))
			{
				// �R���W��������Ăяo��
				objA->OnCollision(objB);

				// ���������t���O���グ��
				_objABoxCollider->SetCollision(true);

				// ���W��␳
				_objABoxCollider->FixPos(objB);
			}
		}

		// ���m���Ȃ�����
		if (_objAScanner && !_objAScanner->GetCollision())
		{
			objA->OnScanner(nullptr);	// �������ĂȂ�����n��
		}
		// ���ɂ�������Ȃ�����
		if (!_objABoxCollider->GetCollision())
		{
			objA->OnCollision(nullptr);
		}
	}
}
