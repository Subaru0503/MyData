using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player2_SoundManager : MonoBehaviour
{
    [SerializeField] private AudioSource audioSource;//AudioSource�^�̕ϐ�a��錾 �g�p����AudioSource�R���|�[�l���g���A�^�b�`�K�v

    [SerializeField] private List<AudioClip> SE;//AudioClip�^�̕ϐ�b1��錾 �g�p����AudioClip���A�^�b�`�K�v
    // Start is called before the first frame update

    public void PlayerSound(int index)
    {
        // index �����X�g�͈͓̔����ǂ����`�F�b�N
        if (index >= 0 && index < SE.Count)
        {

            audioSource.PlayOneShot(SE[index]);
        }
        else
        {
            Debug.LogWarning("�w�肳�ꂽSE������܂���");
        }
    }
}
