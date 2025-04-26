using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StoreBlock : MonoBehaviour
{
    // オブジェクトが範囲に入っているか確認
    [SerializeField] private Vector2 objcheckPos;
    [SerializeField] private Vector2 objcheckSize;      // 四角形のサイズ
    [SerializeField] private LayerMask objcheckLayer;   // レイヤー

    // ブロックが真下にある
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

    // デバッグ用ギズモ
    private void OnDrawGizmos()
    {
        // プレイヤーのローカル空間に基づいて objCheckPos を計算
        Vector2 checkPos = (Vector2)transform.position + (Vector2)transform.TransformDirection(objcheckPos);

        // Gizmosの回転行列を設定して、矩形を描画
        Gizmos.color = Color.red;
        Gizmos.matrix = Matrix4x4.TRS(checkPos, Quaternion.Euler(0, 0, 0.0f), Vector3.one);
        Gizmos.DrawWireCube(Vector2.zero, objcheckSize);
    }
}
