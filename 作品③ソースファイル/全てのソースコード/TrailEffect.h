#ifndef ___TRAIL_EFFECT_H___
#define ___TRAIL_EFFECT_H___


#include "Polyline.h"

class Object;
//�v���C���[�̌��ǂ�������G�t�F�N�g
class TrailEffect : public Polyline
{
public:
	TrailEffect(Object* pObject);
	~TrailEffect();
	void Init();
	void SetOldPos(DirectX::XMFLOAT3 oldPos);
protected:
	//�|�����C���̐���_���X�V
	void UpdateControlPoints(
		LineID id, ControlPoints& controlPoints) final;

private:
	Object* m_pObject;
	DirectX::XMFLOAT3 m_oldPos;
};

#include "Object.h"
#endif // !___TRAIL_EFFECT_H___

