using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//using static UnityEditor.Experimental.GraphView.GraphView;

public class ProgressBar : MonoBehaviour
{
    [SerializeField] private GameObject _ProgressImage;
    [SerializeField] private Transform Player1StartPos;
    [SerializeField] private float GoalPos;

    private Transform player1;       // Player1のTransform
    private Transform player2;       // Player2のTransform

    private float minValue = -322f;  // ゲージの最小値
    private float maxValue = 388f;   // ゲージの最大値
    private float initialDistance; // 初期距離を記録

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


        // 現在のプレイヤー間の距離
        float currentDistance = Mathf.Abs(player1.position.y - GoalPos);

        // 現在の距離をゲージの範囲にマッピング
        float normalizedDistance = Mathf.Clamp01(1 - (currentDistance / initialDistance));
        float arrowY = Mathf.Lerp(minValue, maxValue, normalizedDistance);

        // 矢印の位置を更新
        _ProgressImage.transform.localPosition = new Vector2(_ProgressImage.transform.localPosition.x, arrowY);
    }
}
