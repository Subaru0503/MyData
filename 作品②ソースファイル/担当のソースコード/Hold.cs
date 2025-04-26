using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Hold : MonoBehaviour
{
    public GameObject holdBlock { get; set; }   // �z�[���h�u���b�N

    private Image holdImage;                    // �z�[���hUI

    private int normalLayer;                    // �ʏ펞�̃��C���[

    // Start is called before the first frame update
    void Start()
    {
        holdImage = GameObject.Find("HoldUIImage").GetComponent<Image>();
    }

    // UI����
    public void SetImage(Sprite newSprite)
    {
        holdImage.sprite = newSprite;   // �摜�ݒ�
    }

    // ���C���[�l��߂�
    public void ResetLayer()
    {
        // �z�[���h�O�̃��C���[�l�ɂ���
        holdBlock.GetComponent<SpriteRenderer>().sortingOrder = normalLayer;
    }

    // �u���b�N���z�[���h
    public void HoldBlock()
    {
        // ��]���Z�b�g
        holdBlock.transform.eulerAngles = new Vector3(0.0f, 0.0f, 0.0f);

        // ���C���[�l�ޔ�
        normalLayer = holdBlock.GetComponent<SpriteRenderer>().sortingOrder;
        // �w�i�̌��ɂ���Č����Ȃ�����
        holdBlock.GetComponent<SpriteRenderer>().sortingOrder = -3;
    }
}
