using UnityEngine;

public class AudioManager : MonoBehaviour
{
    // �V���O���g���C���X�^���X
    public static AudioManager Instance { get; private set; }

    private AudioSource audioSource;

    private void Awake()
    {
        // �V���O���g���̃Z�b�g�A�b�v
        if (Instance == null)
        {
            Instance = this;
            DontDestroyOnLoad(gameObject);  // �V�[���J�ڂŔj������Ȃ��悤�ɂ���
        }
        else
        {
            Destroy(gameObject);  // �d���C���X�^���X���폜
            return;
        }

        // AudioSource�R���|�[�l���g�̎擾
        audioSource = GetComponent<AudioSource>();
    }

    // �������~���郁�\�b�h
    public void StopAudio()
    {
        if (audioSource.isPlaying)
        {
            audioSource.Stop();
        }
    }

    // �������Đ����郁�\�b�h
    public void PlayAudio()
    {
        if (!audioSource.isPlaying)
        {
            audioSource.Play();
        }
    }
}