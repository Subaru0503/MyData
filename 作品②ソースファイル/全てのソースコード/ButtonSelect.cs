using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;
using System.Collections;

public class ButtonBackgroundController : MonoBehaviour
{
    // ボタン配列
    public Button[] buttons;

    // 背景として表示するスプライトの配列
    public Sprite[] backgroundSprites;

    // 画像を表示するためのImageコンポーネント
    public Image backgroundImage;

    void Start()
    {
        // 各ボタンにイベントトリガーを追加
        for (int i = 0; i < buttons.Length; i++)
        {
            int index = i;  // キャプチャ問題を回避するためにローカル変数を使用

            // ボタンに選択時のイベントトリガーを追加
            EventTrigger trigger = buttons[i].gameObject.AddComponent<EventTrigger>();

            // OnSelectのイベント
            EventTrigger.Entry entry = new EventTrigger.Entry
            {
                eventID = EventTriggerType.Select
            };
            entry.callback.AddListener((eventData) => OnButtonSelected(index));
            trigger.triggers.Add(entry);
        }

        // 初期状態で最初のスプライトを設定する（必要に応じて）
        if (backgroundSprites.Length > 0)
        {
            backgroundImage.sprite = backgroundSprites[1];
        }
    }

    // ボタンが選択された時に呼ばれるメソッド
    void OnButtonSelected(int index)
    {
        Debug.Log("Button " + index + " selected");

        // 選択されたボタンに対応するスプライトに背景を変更
        if (index >= 0 && index < backgroundSprites.Length)
        {
            backgroundImage.sprite = backgroundSprites[index];
        }
    }
}