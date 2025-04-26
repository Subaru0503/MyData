using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Big : MonoBehaviour
{
    public SoundManager _soundManager { get; set; } // �T�E���h�R���|�[�l���g

    private Vector3 normalScale;    // �ʏ�T�C�Y
    private float giantScal = 1.5f; // �X�P�[���T�C�Y

    private bool PlaySE = false;    // SE�Đ��t���O

    // ���剻
    public void BigScale(GameObject block)
    {
        normalScale = block.transform.localScale;   // �ʏ�T�C�Y�ޔ�
        block.transform.localScale *= giantScal;    // ���剻
    }

    // �T�C�Y��߂�
    public void ResetScale(GameObject block)
    {
        block.transform.localScale = normalScale;   // �ʏ�T�C�Y�ɂ���
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        // �v���C���[�A�폜�p�u���b�N�Ȃ珈�������Ȃ�
        if (collision.collider.tag == "Player" ||
            collision.gameObject.layer == 11)
        {
            return;
        }

        // �Đ����ĂȂ������炷��
        if (!PlaySE)
        {
            MainCameraManager mcm;
            GameObject.FindGameObjectWithTag("MainCamera").TryGetComponent(out mcm);
            StartCoroutine(mcm.Shake(0.2f,0.3f));
            _soundManager.PlayerSound(3);   // SE�Đ�
            PlaySE = true;                          // �t���O�グ
        }
    }
}
