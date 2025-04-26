using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

// ‚±‚±‚ß‚Á‚¿‚á‚¢‚¶‚è‚»‚¤

public class CameraTilt : MonoBehaviour
{
    private int tiltFrame;

    private float distance;

    private float animationRaito = 0.0f;

    private float raito = 0.0f;

    private float startPosY = 0.0f;

    private bool endTilt = false;

    // Start is called before the first frame update
    void Start()
    {
        animationRaito = 1.0f / tiltFrame;
        //startPosY = transform.position.y;
    }

    // Update is called once per frame
    void Update()
    {
        raito += animationRaito;
        if (1.0f < raito) raito = 1.0f;
        var r = EaseInOutSine(raito);
        transform.position = new Vector3(transform.position.x, startPosY - (distance * r), -10.0f);
        if (raito == 1.0f)
        {
            endTilt = true;
        }
    }

    public void Setting(int tf, float d, float sh)
    {
        tiltFrame = tf;
        distance = d;
        startPosY = sh;
    }

    public bool GetEndTilt()
    {
        return endTilt;
    }

    private float EaseInOutSine(float r)
    {
        return -(Mathf.Cos(Mathf.PI * r) - 1) / 2;

    }
}
