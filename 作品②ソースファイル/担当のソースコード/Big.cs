using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Big : MonoBehaviour
{
    public SoundManager _soundManager { get; set; } // サウンドコンポーネント

    private Vector3 normalScale;    // 通常サイズ
    private float giantScal = 1.5f; // スケールサイズ

    private bool PlaySE = false;    // SE再生フラグ

    // 巨大化
    public void BigScale(GameObject block)
    {
        normalScale = block.transform.localScale;   // 通常サイズ退避
        block.transform.localScale *= giantScal;    // 巨大化
    }

    // サイズを戻す
    public void ResetScale(GameObject block)
    {
        block.transform.localScale = normalScale;   // 通常サイズにする
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        // プレイヤー、削除用ブロックなら処理をしない
        if (collision.collider.tag == "Player" ||
            collision.gameObject.layer == 11)
        {
            return;
        }

        // 再生してなかったらする
        if (!PlaySE)
        {
            MainCameraManager mcm;
            GameObject.FindGameObjectWithTag("MainCamera").TryGetComponent(out mcm);
            StartCoroutine(mcm.Shake(0.2f,0.3f));
            _soundManager.PlayerSound(3);   // SE再生
            PlaySE = true;                          // フラグ上げ
        }
    }
}
