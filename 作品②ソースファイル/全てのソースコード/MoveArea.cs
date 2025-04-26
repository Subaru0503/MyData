using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MoveArea : MonoBehaviour
{
    // 移動範囲
    [SerializeField] private Vector2 Min_AreaPos;
    [SerializeField] private Vector2 Max_AreaPos;
    private Vector2 AreaSize = new Vector2(0.1f, 0.1f);

    // Update is called once per frame
    void Update()
    {
        //現在の座標取得
        Vector3 currentPos = transform.position;

        Min_AreaPos.y = transform.position.y;
        Max_AreaPos.y = transform.position.y;

        //追加　Mathf.ClampでX,Yの値それぞれが最小～最大の範囲内に収める。
        //範囲を超えていたら範囲内の値を代入する
        currentPos.x = Mathf.Clamp(currentPos.x, Min_AreaPos.x, Max_AreaPos.x);

        //座標代入
        transform.position = currentPos;
    }

    // デバッグ用ギズモ
    private void OnDrawGizmos()
    {
        Vector3 minPos = Min_AreaPos;
        minPos.x -= 0.5f;

        Vector3 maxPos = Max_AreaPos;
        maxPos.x += 0.5f;

        // Gizmosの回転行列を設定して、矩形を描画
        Gizmos.color = Color.red;
        
        Gizmos.DrawLine(minPos, maxPos);
    }
}
