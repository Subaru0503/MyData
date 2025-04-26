using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player2_SoundManager : MonoBehaviour
{
    [SerializeField] private AudioSource audioSource;//AudioSource型の変数aを宣言 使用するAudioSourceコンポーネントをアタッチ必要

    [SerializeField] private List<AudioClip> SE;//AudioClip型の変数b1を宣言 使用するAudioClipをアタッチ必要
    // Start is called before the first frame update

    public void PlayerSound(int index)
    {
        // index がリストの範囲内かどうかチェック
        if (index >= 0 && index < SE.Count)
        {

            audioSource.PlayOneShot(SE[index]);
        }
        else
        {
            Debug.LogWarning("指定されたSEがありません");
        }
    }
}
