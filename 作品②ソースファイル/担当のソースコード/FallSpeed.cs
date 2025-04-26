using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FallSpeed : MonoBehaviour
{
    // �������x����l
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
            // �X�N���v�g�폜
            Destroy(gameObject.GetComponent<FallSpeed>());
        }
    }

    // Rigidbody2D�Z�b�g
    public void Setrb()
    {
        rb = GetComponent<Rigidbody2D>();
    }

    // ����������X�N���v�g�폜
    void OnCollisionEnter2D(Collision2D collision)
    {
        if(collision.gameObject.layer == gameObject.layer)
        {
            // �X�N���v�g�폜
            Destroy(gameObject.GetComponent<FallSpeed>());
        }
    }
}
