using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Eraser : MonoBehaviour
{
    [SerializeField] private GameObject Effect;         // �폜�G�t�F�N�g

    public SoundManager _soundManager { get; set; } // �T�E���h�R���|�[�l���g

    public string[] tagName { get; set; }              // �����ΏۂɂȂ�^�O

    const int MAX_Tag = 3;

    private bool PlaySE = false;                       // SE�Đ��t���O

    void Awake()
    {
        tagName = new string[MAX_Tag];

    }

    // ��������
    private void OnCollisionEnter2D(Collision2D collision)
    {
        // �v���C���[�A�y��A�폜�p�u���b�N�Ȃ珈�������Ȃ�
        if (collision.collider.tag == "Player" || collision.collider.tag == "Base" ||
            collision.gameObject.layer == 11)
        {
            return;
        }

        Collider2D collisionObj = null; // �Փ˂����I�u�W�F�N�g
        float IsNear = 0.0f;            // ��ԋ߂���������

        // �Փ˂����R���C�_�[���擾
        foreach (ContactPoint2D contact in collision.contacts)
        {
            // �Փ˂����R���C�_�[�̃I�u�W�F�N�g���擾
            Collider2D collider = contact.collider;

            // �������v�Z
            float distance = Vector3.Distance(transform.position, collider.transform.position);

            // ���܂łň�ԋ������߂��I�u�W�F�N�g��
            if (IsNear > distance || IsNear == 0.0f)
            {
                IsNear = distance;          // �����X�V
                collisionObj = collider;    // ���擾
            }
            else
            {
                continue;
            }
        }

        // �^�O�[�`�F�b�N
        for (int i = 0; i < MAX_Tag; i++)
        {
            if (collisionObj.gameObject.CompareTag(tagName[i]))
            {
                // �G�t�F�N�g���u���b�N���m�̊Ԃɐ�������
                Vector2 pos = Vector2.Lerp(transform.position, collision.transform.localPosition, 0.5f);
                Instantiate(Effect, pos, Quaternion.identity);

                Destroy(collisionObj.gameObject);       // �Ώۂ̃u���b�N�폜
                Destroy(gameObject);                    // �������g���폜
            }
        }

        // �Đ����ĂȂ������炷��
        if (!PlaySE)
        {
            _soundManager.PlayerSound(4);   // SE�Đ�
            PlaySE = true;                          // �t���O�グ
        }
    }
}
