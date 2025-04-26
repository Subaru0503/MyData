using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NormalCollisionSound : MonoBehaviour
{
    private SoundManager _soundManager;             // �T�E���h�R���|�[�l���g

    private int SENo;                               // SE�i���o�[

    private bool PlaySE = false;                    // SE�Đ��t���O

    // ���Z�b�g
    public void SetSE(SoundManager soundManager, int seNo)
    {
        _soundManager = soundManager;
        SENo = seNo;
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
            _soundManager.PlayerSound(SENo);        // SE�Đ�
            PlaySE = true;                          // �t���O�グ
        }
    }
}
