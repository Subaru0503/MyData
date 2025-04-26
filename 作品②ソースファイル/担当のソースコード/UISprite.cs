using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UISprite : MonoBehaviour
{
    [SerializeField] private Sprite noItemUISprite;

    private Sprite UIsprite;

    // Start is called before the first frame update
    void Awake()
    {
        UIsprite = GetComponent<SpriteRenderer>().sprite;
    }

    // UI�ɕ\������X�v���C�g��Ԃ�
    public Sprite Issprite
    {
        get
        {
            return UIsprite;
        }
    }

    // �A�C�e������̂Ƃ��ɕ\������X�v���C�g��Ԃ�
    public Sprite IsnoItemUISprite
    {
        get
        {
            return noItemUISprite;
        }
    }

    public void SetUISprite(Sprite sprite)
    {
        UIsprite = sprite;
    }
}
