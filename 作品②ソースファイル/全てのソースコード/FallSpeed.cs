using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FallSpeed : MonoBehaviour
{
    // 落下速度上限値
    [SerializeField] private float MAX_fallspeed;

    Rigidbody2D rb; // Rigidbody2D

    // Update is called once per frame
    void Update()
    {
        if (!rb) return;

        if(rb.velocity.y < -MAX_fallspeed)
        {
            rb.velocity = new Vector2(rb.velocity.x, -MAX_fallspeed);
        }
        else if(rb.velocity.y == 0.0f)
        {
            // スクリプト削除
            Destroy(gameObject.GetComponent<FallSpeed>());
        }
    }

    // Rigidbody2Dセット
    public void Setrb()
    {
        rb = GetComponent<Rigidbody2D>();
    }

    // 落下したらスクリプト削除
    void OnCollisionEnter2D(Collision2D collision)
    {
        if(collision.gameObject.layer == gameObject.layer)
        {
            // スクリプト削除
            Destroy(gameObject.GetComponent<FallSpeed>());
        }
    }
}
