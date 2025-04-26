using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MoveArea : MonoBehaviour
{
    // �ړ��͈�
    [SerializeField] private Vector2 Min_AreaPos;
    [SerializeField] private Vector2 Max_AreaPos;
    private Vector2 AreaSize = new Vector2(0.1f, 0.1f);

    // Update is called once per frame
    void Update()
    {
        //���݂̍��W�擾
        Vector3 currentPos = transform.position;

        Min_AreaPos.y = transform.position.y;
        Max_AreaPos.y = transform.position.y;

        //�ǉ��@Mathf.Clamp��X,Y�̒l���ꂼ�ꂪ�ŏ��`�ő�͈͓̔��Ɏ��߂�B
        //�͈͂𒴂��Ă�����͈͓��̒l��������
        currentPos.x = Mathf.Clamp(currentPos.x, Min_AreaPos.x, Max_AreaPos.x);

        //���W���
        transform.position = currentPos;
    }

    // �f�o�b�O�p�M�Y��
    private void OnDrawGizmos()
    {
        Vector3 minPos = Min_AreaPos;
        minPos.x -= 0.5f;

        Vector3 maxPos = Max_AreaPos;
        maxPos.x += 0.5f;

        // Gizmos�̉�]�s���ݒ肵�āA��`��`��
        Gizmos.color = Color.red;
        
        Gizmos.DrawLine(minPos, maxPos);
    }
}
