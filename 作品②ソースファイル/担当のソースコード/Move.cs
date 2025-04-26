using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Move : MonoBehaviour
{
    // 移動量
    [SerializeField] private float MoveValue;

    // リジッドボディ
    Rigidbody2D rb;

    // Start is called before the first frame update
    void Start()
    {
        // 実体取得
        rb = GetComponent<Rigidbody2D>();
    }

    // 右に移動
    public void RightMove()
    {
        rb.velocity = new Vector2(MoveValue, rb.velocity.y);
    }

    // 左に移動
    public void LeftMove()
    {
        rb.velocity = new Vector2(-MoveValue, rb.velocity.y);
    }

    // 移動量リセット
    public void ResetValue()
    {
        if (rb == null) return;
        rb.velocity = new Vector2(0, rb.velocity.y);
    }
}
