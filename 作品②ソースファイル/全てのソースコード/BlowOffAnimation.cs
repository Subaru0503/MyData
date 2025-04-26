using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UIElements;

public class BlowOffAnimation : MonoBehaviour
{
    [SerializeField, Header("èâë¨")] private Vector2 sv = new Vector2(10, 10);
    [SerializeField, Header("èdóÕ")] private float gravity = 0.1f;

    private RectTransform rectTransform;
    private Behaviour behaviour;


    private bool nowAnimation = false;

    private float rotate = 0.0f;

    private bool leftToRightBlow;

    private float angleSpeed = 3;

    private Vector2 v = Vector2.zero;

    // Start is called before the first frame update
    void Start()
    {
        gameObject.TryGetComponent(out rectTransform);
        TryGetComponent(out behaviour);
    }

    // Update is called once per frame
    void Update()
    {

        if (nowAnimation)
        {
            if ((Time.timeScale == 1))
            {
                rotate += angleSpeed;
                v = new Vector2(v.x, v.y - gravity);
                rectTransform.rotation = Quaternion.Euler(0, 0, rotate);
                rectTransform.localPosition = new Vector3(rectTransform.localPosition.x + v.x, rectTransform.localPosition.y + v.y, rectTransform.localPosition.z);
            }
        }
    }

    public void StartAnimation(bool ltr)
    {
        rotate = 0;
        nowAnimation = true;
        leftToRightBlow = ltr;
        angleSpeed *= -1;
        v = new Vector2(sv.x * (ltr ? 1 : (-1)), sv.y);
    }

    public void EndAnimation()
    {
        rectTransform.rotation = Quaternion.identity;
        nowAnimation = false;
        behaviour.enabled = false;
    }

    public void Setting(bool ltr)
    {
        angleSpeed = (ltr ? 1 : -1);
    }
}
