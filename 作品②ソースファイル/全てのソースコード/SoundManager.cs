using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SoundManager: MonoBehaviour
{
    [SerializeField] private AudioSource audioSource;//AudioSource型の変数aを宣言 使用するAudioSourceコンポーネントをアタッチ必要

    [SerializeField] private List<AudioClip> SE;//AudioClip型の変数b1を宣言 使用するAudioClipをアタッチ必要
    [SerializeField] private List<float> volumes; // 各AudioClipに対応する音量のリスト
    // Start is called before the first frame update
    void Start()
    {
        audioSource = GetComponent<AudioSource>();
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void PlayerSound(int index)
    {
        // index がリストの範囲内かどうかチェック
        if (index >= 0 && index < SE.Count)
        {
            AudioClip clip = SE[index];
            float volume = 1.0f; // デフォルト値

            // volumesが設定されていて、指定したインデックスが範囲内の場合はその音量を使用
            if (volumes != null && index < volumes.Count)
            {
                volume = volumes[index];
            }
            audioSource.PlayOneShot(clip, volume);
        }
        else
        {
            Debug.LogWarning("指定されたindexのAudioClipまたはVolumeが見つかりません");
        }
    }
}
