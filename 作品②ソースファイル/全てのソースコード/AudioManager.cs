using UnityEngine;

public class AudioManager : MonoBehaviour
{
    // シングルトンインスタンス
    public static AudioManager Instance { get; private set; }

    private AudioSource audioSource;

    private void Awake()
    {
        // シングルトンのセットアップ
        if (Instance == null)
        {
            Instance = this;
            DontDestroyOnLoad(gameObject);  // シーン遷移で破棄されないようにする
        }
        else
        {
            Destroy(gameObject);  // 重複インスタンスを削除
            return;
        }

        // AudioSourceコンポーネントの取得
        audioSource = GetComponent<AudioSource>();
    }

    // 音声を停止するメソッド
    public void StopAudio()
    {
        if (audioSource.isPlaying)
        {
            audioSource.Stop();
        }
    }

    // 音声を再生するメソッド
    public void PlayAudio()
    {
        if (!audioSource.isPlaying)
        {
            audioSource.Play();
        }
    }
}