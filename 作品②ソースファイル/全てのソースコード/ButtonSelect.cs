using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;
using System.Collections;

public class ButtonBackgroundController : MonoBehaviour
{
    // �{�^���z��
    public Button[] buttons;

    // �w�i�Ƃ��ĕ\������X�v���C�g�̔z��
    public Sprite[] backgroundSprites;

    // �摜��\�����邽�߂�Image�R���|�[�l���g
    public Image backgroundImage;

    void Start()
    {
        // �e�{�^���ɃC�x���g�g���K�[��ǉ�
        for (int i = 0; i < buttons.Length; i++)
        {
            int index = i;  // �L���v�`������������邽�߂Ƀ��[�J���ϐ����g�p

            // �{�^���ɑI�����̃C�x���g�g���K�[��ǉ�
            EventTrigger trigger = buttons[i].gameObject.AddComponent<EventTrigger>();

            // OnSelect�̃C�x���g
            EventTrigger.Entry entry = new EventTrigger.Entry
            {
                eventID = EventTriggerType.Select
            };
            entry.callback.AddListener((eventData) => OnButtonSelected(index));
            trigger.triggers.Add(entry);
        }

        // ������Ԃōŏ��̃X�v���C�g��ݒ肷��i�K�v�ɉ����āj
        if (backgroundSprites.Length > 0)
        {
            backgroundImage.sprite = backgroundSprites[1];
        }
    }

    // �{�^�����I�����ꂽ���ɌĂ΂�郁�\�b�h
    void OnButtonSelected(int index)
    {
        Debug.Log("Button " + index + " selected");

        // �I�����ꂽ�{�^���ɑΉ�����X�v���C�g�ɔw�i��ύX
        if (index >= 0 && index < backgroundSprites.Length)
        {
            backgroundImage.sprite = backgroundSprites[index];
        }
    }
}