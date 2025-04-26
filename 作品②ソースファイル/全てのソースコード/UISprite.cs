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

    // UIに表示するスプライトを返す
    public Sprite Issprite
    {
        get
        {
            return UIsprite;
        }
    }

    // アイテムが空のときに表示するスプライトを返す
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
