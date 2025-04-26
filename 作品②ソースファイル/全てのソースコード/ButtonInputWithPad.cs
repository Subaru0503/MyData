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
    private Button selectedButton; // 現在選択されているボタン
    private Vector3 defaultScale;  // ボタンのデフォルトのスケール
    [SerializeField] private float selectedScaleFactor = 1.2f; // 選択時に拡大するスケール倍率
    private AudioSource _audio;

    bool _enableds = false;

    public float duration = 2.0f;                    // サイズ変化にかかる時間

    // Start is called before the first frame update
    void Start()
    {
       _audio = GetComponent<AudioSource>();
        InputSystem.DisableDevice(Mouse.current);
        Buttons[0].Select(); // 最初のボタンを選択
        defaultScale = new Vector3(1.0f,1.0f,1.0f); // 最初のボタンのスケールを記録
        _enableds =true;


    }

    // Update is called once per frame
    void Update()
    {
        if (_enableds == false) return;

        // 現在選択されているボタンを取得
        GameObject currentSelected = EventSystem.current.currentSelectedGameObject;

        if (currentSelected != null && currentSelected.GetComponent<Button>() != null )
        {
            Button currentButton = currentSelected.GetComponent<Button>();

            // 以前の選択ボタンがあり、それが現在選択ボタンと異なる場合、以前のボタンのスケールを元に戻す
            if (selectedButton != null && selectedButton != currentButton)
            {
                selectedButton.transform.localScale = defaultScale;
                _audio.Play();
            }

            if (!System.Array.Exists(Buttons, button => button == currentButton))
            {
                return;
            }
            // 現在選択されているボタンのスケールを拡大する
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
                Buttons[0].Select(); // 最初のボタンを選択
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