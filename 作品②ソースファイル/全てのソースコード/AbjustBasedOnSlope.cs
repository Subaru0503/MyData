using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AbjustBasedOnSlope : MonoBehaviour
{
    private Rigidbody2D _rigidbody2D;
    [SerializeField] private PhysicsMaterial2D lowFrictionMaterial;  // �ᖀ�C�p�̕����}�e���A��
    [SerializeField] private PhysicsMaterial2D highFrictionMaterial; // �����C�p�̕����}�e���A��
    [SerializeField] private float slopeThreshold = 30f; // �p�x�̂������l�i���̊p�x�ȏ�ō����C�Ɂj


    [SerializeField] public LayerMask groundLayer;
    // Start is called before the first frame update
    void Start()
    {
        _rigidbody2D = GetComponent<Rigidbody2D>();
    }

    // Update is called once per frame
    void Update()
    {
        // �L�����N�^�[�̑����Ƀ��C���΂��Ēn�ʂ����o
        RaycastHit2D hit = Physics2D.Raycast(transform.position, Vector2.down, 1f, groundLayer);

        if (hit.collider != null)
        {
            // �n�ʂ̖@�����擾
            Vector2 groundNormal = hit.normal;

            // �n�ʂ̊p�x���v�Z
            float slopeAngle = Vector2.Angle(groundNormal, Vector2.up);

            // �p�x�ɉ����Ė��C��ݒ�
            if (slopeAngle > slopeThreshold)
            {
                // �����C�̕����}�e���A����ݒ�
                _rigidbody2D.sharedMaterial = highFrictionMaterial;
            }
            else
            {
                // �ᖀ�C�̕����}�e���A����ݒ�
                _rigidbody2D.sharedMaterial = lowFrictionMaterial;
            }

            // �n�ʂ̖@���Ɋ�Â��ĉ�]�p�x���v�Z
            float slopeRotationAngle = Mathf.Atan2(groundNormal.y, groundNormal.x) * Mathf.Rad2Deg - 90f;

            // ��]�p�x�� -30�x���� +30�x�͈͓̔��ɐ���
            slopeRotationAngle = Mathf.Clamp(slopeRotationAngle, -30f, 30f);

            // �ڕW�̉�]�p�x��ݒ�
            Quaternion targetRotation = Quaternion.Euler(0f, 0f, slopeRotationAngle);

            // ���݂̉�]�ƖڕW�̉�]�̊Ԃ���`�⊮���Ċ��炩�ɉ�]
            transform.rotation = Quaternion.Lerp(transform.rotation, targetRotation, Time.deltaTime * 10f);  // �⊮���x
        }
        else
        {
            // �󒆂ɂ���ꍇ�͖��C�����Z�b�g
            _rigidbody2D.sharedMaterial = lowFrictionMaterial;

            // �n�ʂɐڒn���Ă��Ȃ��ꍇ�͉�]�����Z�b�g
            Quaternion targetRotation = Quaternion.Euler(0f, 0f, 0f);
            transform.rotation = Quaternion.Lerp(transform.rotation, targetRotation, Time.deltaTime * 10f);  // �⊮���x
        }
    }
    // ���C�L���X�g�̉���
    private void OnDrawGizmos()
    {
        // �V�[���r���[�Ń��C��ԐF�ŕ`��
        Gizmos.color = Color.blue;

        // ���C�̋N�_
        Vector2 rayOrigin = transform.position;

        // ���C�̕����Ƌ�����`��
        Gizmos.DrawLine(rayOrigin, rayOrigin + Vector2.down * 0.5f);
    }
}
