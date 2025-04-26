using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Eraser : MonoBehaviour
{
    [SerializeField] private GameObject Effect;         // 削除エフェクト

    public SoundManager _soundManager { get; set; } // サウンドコンポーネント

    public string[] tagName { get; set; }              // 消す対象になるタグ

    const int MAX_Tag = 3;

    private bool PlaySE = false;                       // SE再生フラグ

    void Awake()
    {
        tagName = new string[MAX_Tag];

    }

    // 消す処理
    private void OnCollisionEnter2D(Collision2D collision)
    {
        // プレイヤー、土台、削除用ブロックなら処理をしない
        if (collision.collider.tag == "Player" || collision.collider.tag == "Base" ||
            collision.gameObject.layer == 11)
        {
            return;
        }

        Collider2D collisionObj = null; // 衝突したオブジェクト
        float IsNear = 0.0f;            // 一番近かった距離

        // 衝突したコライダーを取得
        foreach (ContactPoint2D contact in collision.contacts)
        {
            // 衝突したコライダーのオブジェクトを取得
            Collider2D collider = contact.collider;

            // 距離を計算
            float distance = Vector3.Distance(transform.position, collider.transform.position);

            // 今までで一番距離が近いオブジェクトか
            if (IsNear > distance || IsNear == 0.0f)
            {
                IsNear = distance;          // 距離更新
                collisionObj = collider;    // 情報取得
            }
            else
            {
                continue;
            }
        }

        // タグーチェック
        for (int i = 0; i < MAX_Tag; i++)
        {
            if (collisionObj.gameObject.CompareTag(tagName[i]))
            {
                // エフェクトをブロック同士の間に生成する
                Vector2 pos = Vector2.Lerp(transform.position, collision.transform.localPosition, 0.5f);
                Instantiate(Effect, pos, Quaternion.identity);

                Destroy(collisionObj.gameObject);       // 対象のブロック削除
                Destroy(gameObject);                    // 自分自身も削除
            }
        }

        // 再生してなかったらする
        if (!PlaySE)
        {
            _soundManager.PlayerSound(4);   // SE再生
            PlaySE = true;                          // フラグ上げ
        }
    }
}
