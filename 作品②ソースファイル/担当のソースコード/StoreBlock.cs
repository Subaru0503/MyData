using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StoreBlock : MonoBehaviour
{
    // �I�u�W�F�N�g���͈͂ɓ����Ă��邩�m�F
    [SerializeField] private Vector2 objcheckPos;
    [SerializeField] private Vector2 objcheckSize;      // �l�p�`�̃T�C�Y
    [SerializeField] private LayerMask objcheckLayer;   // ���C���[

    // �u���b�N���^���ɂ���
    public bool block_InArea { get; set; }

    // Update is called once per frame
    void Update()
    {
        Vector2 checkPos = (Vector2)transform.position + (Vector2)transform.TransformDirection(objcheckPos);

        if(Physics2D.OverlapBox(checkPos, objcheckSize, 0.0f, objcheckLayer))
        {
            block_InArea = true;
        }
        else
        {
            block_InArea = false;
        }
    }

    // �f�o�b�O�p�M�Y��
    private void OnDrawGizmos()
    {
        // �v���C���[�̃��[�J����ԂɊ�Â��� objCheckPos ���v�Z
        Vector2 checkPos = (Vector2)transform.position + (Vector2)transform.TransformDirection(objcheckPos);

        // Gizmos�̉�]�s���ݒ肵�āA��`��`��
        Gizmos.color = Color.red;
        Gizmos.matrix = Matrix4x4.TRS(checkPos, Quaternion.Euler(0, 0, 0.0f), Vector3.one);
        Gizmos.DrawWireCube(Vector2.zero, objcheckSize);
    }
}
