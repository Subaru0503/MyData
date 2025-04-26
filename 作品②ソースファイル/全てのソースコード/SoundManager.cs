using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SoundManager: MonoBehaviour
{
    [SerializeField] private AudioSource audioSource;//AudioSource�^�̕ϐ�a��錾 �g�p����AudioSource�R���|�[�l���g���A�^�b�`�K�v

    [SerializeField] private List<AudioClip> SE;//AudioClip�^�̕ϐ�b1��錾 �g�p����AudioClip���A�^�b�`�K�v
    [SerializeField] private List<float> volumes; // �eAudioClip�ɑΉ����鉹�ʂ̃��X�g
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
        // index �����X�g�͈͓̔����ǂ����`�F�b�N
        if (index >= 0 && index < SE.Count)
        {
            AudioClip clip = SE[index];
            float volume = 1.0f; // �f�t�H���g�l

            // volumes���ݒ肳��Ă��āA�w�肵���C���f�b�N�X���͈͓��̏ꍇ�͂��̉��ʂ��g�p
            if (volumes != null && index < volumes.Count)
            {
                volume = volumes[index];
            }
            audioSource.PlayOneShot(clip, volume);
        }
        else
        {
            Debug.LogWarning("�w�肳�ꂽindex��AudioClip�܂���Volume��������܂���");
        }
    }
}
