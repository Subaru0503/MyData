using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DeleteBlock : MonoBehaviour
{
    [SerializeField] private LayerMask[] deletelayer;
    [SerializeField] private GameManager _gameManager;
    // ��Ԃ����̒n�ʂɓ�����������������
    private void OnCollisionEnter2D(Collision2D collision)
    {

        if (collision.collider.tag == "Player")
        {
            _gameManager.GameOver();
        }
        // ���C���[�`�F�b�N
        for (int i = 0; i < deletelayer.Length; i++)
        {
            if ((deletelayer[i].value & (1 << collision.gameObject.layer)) != 0)
            {


                if (collision.gameObject.layer == 8)
                {
                    _gameManager.AddDropBlocks();
                }
                Destroy(collision.gameObject);    // �ΏۃI�u�W�F�N�g�폜
            }
        }
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        // ���C���[�`�F�b�N
        for (int i = 0; i < deletelayer.Length; i++)
        {
            if ((deletelayer[i].value & (1 << collision.gameObject.layer)) != 0)
            {


                if (collision.gameObject.layer == 8)
                {
                    _gameManager.AddDropBlocks();
                }
                Destroy(collision.gameObject);    // �ΏۃI�u�W�F�N�g�폜
            }
        }
    }
}
