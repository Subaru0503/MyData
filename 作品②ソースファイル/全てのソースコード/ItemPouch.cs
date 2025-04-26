using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ItemPouch : MonoBehaviour
{
    // �^�O�ݒ�
    public string blocktagName;                                     // �A�C�e���̑ΏۂɂȂ�^�O
    public string sticktagName;                                     // �̂�A�C�e���̃^�O
    public string bigtagName;                                       // ���剻�A�C�e���̃^�O
    public string erasertagName;                                    // �����S���A�C�e���̃^�O

    [SerializeField] private LayerMask itemLayer;                   // �A�C�e�����ʂ̃��C���[

    [SerializeField] private GameObject eraserObj;                  // �����S���I�u�W�F�N�g

    public SoundManager _soundManager { get; set; } // �T�E���h�R���|�[�l���g

    public GameObject item { get; set; }                            // �������Ă���A�C�e��

    // �����t���O
    public bool hasStick { get; set; }                              // �̃A�C�e���������
    public bool hasBig { get; set; }                                // ���剻�A�C�e��������
    public bool hasEraser { get; set; }                             // �����S���A�C�e��������

    private Image itemImage;                                        // �A�C�e��UI

    private Sprite newSprite;                                       // �ݒ�摜
    private Sprite noItemSprite;                                    // �A�C�e�����Ȃ��Ƃ��̐ݒ�摜

    // Start is called before the first frame update
    void Start()
    {
        // ���̎擾
        itemImage = GameObject.Find("ItemUIImage").GetComponent<Image>();
    }

    // �A�C�e���̃��C���[����
    public void ItemLayer(bool use)
    {
        if(use)
        {
            itemImage.sprite = noItemSprite;    // UI�摜�ݒ�Ȃ�
            return;
        }
        itemImage.sprite = newSprite;           // UI�摜�ݒ�
    }

    // �A�C�e���g�p �A�C�e�����|�[�`����폜
    public void ItemDelete()
    {
        Destroy(item);  // �A�C�e���폜
        item = null;
        NoItem();       // �A�C�e�����Ȃ��Ȃ����̂Ńt���O��������
    }

    // ���������Ȃ��Ȃ���
    private void NoItem()
    {
        // �t���O����    
        hasStick = false;
        hasBig = false;
        hasEraser = false;
    }

    // �������`�F�b�N
    private void CheckItem()
    {
        // �A�C�e���̃^�O���m�F
        switch(item.tag)
        {
            case "Stick":           // �̂�
                hasStick = true;    // �����t���O�グ

                // �����t���O����
                hasBig = false;
                hasEraser = false;
                break;

            case "Big":             // ���剻
                hasBig = true;      // �����t���O�グ

                // �����t���O����
                hasStick = false;
                hasEraser = false;
                break;

            case "Eraser":          // �����S��
                hasEraser = true;   // �����t���O�グ

                // �����t���O����
                hasStick = false;
                hasBig = false;
                break;
        }
    }

    // �A�C�e������
    private void OnTriggerEnter2D(Collider2D collision)
    {
        // ���C���[�`�F�b�N
        if(((1 << collision.gameObject.layer) & itemLayer.value) != 0)
        {
            _soundManager.PlayerSound(1);                                   // ����SE�Đ�

            item = collision.gameObject;                                            // �A�C�e�����
            CheckItem();                                                            // ���肵���A�C�e�����m�F
            item.transform.position = new
                Vector3(-100.0f, item.transform.position.y, 0.0f);                  // ���W�����炷

            // UI�ݒ�
            noItemSprite = item.                                                    // �A�C�e���������ĂȂ��Ƃ���
                GetComponent<UISprite>().IsnoItemUISprite;                          // �\������摜���擾
            newSprite = item.GetComponent<UISprite>().Issprite;                     // UI�ɕ\������摜���擾
            itemImage.sprite = newSprite;                                           // UI�摜�ݒ�
        }
    }

    // �����S���A�C�e��
    public GameObject GetEraserObj()
    {
        return eraserObj;
    }
}
