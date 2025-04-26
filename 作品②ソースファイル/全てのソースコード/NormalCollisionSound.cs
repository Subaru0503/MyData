using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NormalCollisionSound : MonoBehaviour
{
    private SoundManager _soundManager;             // サウンドコンポーネント

    private int SENo;                               // SEナンバー

    private bool PlaySE = false;                    // SE再生フラグ

    // 音セット
    public void SetSE(SoundManager soundManager, int seNo)
    {
        _soundManager = soundManager;
        SENo = seNo;
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
            _soundManager.PlayerSound(SENo);        // SE再生
            PlaySE = true;                          // フラグ上げ
        }
    }
}
