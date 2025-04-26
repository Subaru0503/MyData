using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//using static UnityEditor.Experimental.GraphView.GraphView;

public class ProgressBar : MonoBehaviour
{
    [SerializeField] private GameObject _ProgressImage;
    [SerializeField] private Transform Player1StartPos;
    [SerializeField] private float GoalPos;

    private Transform player1;       // Player1��Transform
    private Transform player2;       // Player2��Transform

    private float minValue = -322f;  // �Q�[�W�̍ŏ��l
    private float maxValue = 388f;   // �Q�[�W�̍ő�l
    private float initialDistance; // �����������L�^

    // Start is called before the first frame update
    void Start()
    {
        initialDistance = Mathf.Abs(Player1StartPos.position.y - GoalPos);

    }

    // Update is called once per frame
    void Update()
    {
        if (!player1)
        {
            player1 = GameObject.FindGameObjectWithTag("Player").transform;
        }
        if(!player2) {
            player2 = GameObject.FindGameObjectWithTag("Player2").transform;
        }


        // ���݂̃v���C���[�Ԃ̋���
        float currentDistance = Mathf.Abs(player1.position.y - GoalPos);

        // ���݂̋������Q�[�W�͈̔͂Ƀ}�b�s���O
        float normalizedDistance = Mathf.Clamp01(1 - (currentDistance / initialDistance));
        float arrowY = Mathf.Lerp(minValue, maxValue, normalizedDistance);

        // ���̈ʒu���X�V
        _ProgressImage.transform.localPosition = new Vector2(_ProgressImage.transform.localPosition.x, arrowY);
    }
}
