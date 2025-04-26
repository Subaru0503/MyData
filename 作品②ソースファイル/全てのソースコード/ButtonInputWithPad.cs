using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;
using UnityEngine.UI;
using UnityEngine.EventSystems;
using Unity.VisualScripting;

public class ButtonInputWithPad : MonoBehaviour
{
    [SerializeField] private Button[] Buttons;
    private Button selectedButton; // ���ݑI������Ă���{�^��
    private Vector3 defaultScale;  // �{�^���̃f�t�H���g�̃X�P�[��
    [SerializeField] private float selectedScaleFactor = 1.2f; // �I�����Ɋg�傷��X�P�[���{��
    private AudioSource _audio;

    bool _enableds = false;

    public float duration = 2.0f;                    // �T�C�Y�ω��ɂ����鎞��

    // Start is called before the first frame update
    void Start()
    {
       _audio = GetComponent<AudioSource>();
        InputSystem.DisableDevice(Mouse.current);
        Buttons[0].Select(); // �ŏ��̃{�^����I��
        defaultScale = new Vector3(1.0f,1.0f,1.0f); // �ŏ��̃{�^���̃X�P�[�����L�^
        _enableds =true;


    }

    // Update is called once per frame
    void Update()
    {
        if (_enableds == false) return;

        // ���ݑI������Ă���{�^�����擾
        GameObject currentSelected = EventSystem.current.currentSelectedGameObject;

        if (currentSelected != null && currentSelected.GetComponent<Button>() != null )
        {
            Button currentButton = currentSelected.GetComponent<Button>();

            // �ȑO�̑I���{�^��������A���ꂪ���ݑI���{�^���ƈقȂ�ꍇ�A�ȑO�̃{�^���̃X�P�[�������ɖ߂�
            if (selectedButton != null && selectedButton != currentButton)
            {
                selectedButton.transform.localScale = defaultScale;
                _audio.Play();
            }

            if (!System.Array.Exists(Buttons, button => button == currentButton))
            {
                return;
            }
            // ���ݑI������Ă���{�^���̃X�P�[�����g�傷��
            Vector3 targetScale = defaultScale * selectedScaleFactor;

            float t = Mathf.PingPong(Time.unscaledTime / duration,1.0f);

            currentButton.transform.localScale = Vector3.Lerp(defaultScale, targetScale,t);
            selectedButton = currentButton;
        }
    }

   void EnableButtons(bool enable)
    {

        _enableds = enable;
        if (enable == true)
        {

            if (selectedButton)
                selectedButton.Select();
            else
                Buttons[0].Select(); // �ŏ��̃{�^����I��
        }
        foreach (Button button in Buttons)
        {
            button.interactable = enable;
        }
    }

    public void ChangeButtons(ButtonInputWithPad NewButtons)
    {
        EnableButtons(false);

        NewButtons.EnableButtons(true);
    }
}