// �C���N���[�h��
#include "Gravity.h"

// �萔�E�}�N����`
#define GRAVITY (0.21f)

// �X�V����
void Gravity::Execute()
{
	DirectX::XMFLOAT3 pos = transform->GetPos();

	pos.y -= GRAVITY;	// �d�͌v�Z

	transform->SetPos(pos);	// �l�X�V
}
