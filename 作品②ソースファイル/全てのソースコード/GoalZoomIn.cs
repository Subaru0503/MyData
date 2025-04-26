using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GoalZoomIn : MonoBehaviour
{
    private float zoomRatio { get; set; }
    private int zoomFrame { get; set; }

    private GameObject player2p;
    private Camera cc;

    private float cameraSize;
    private float zoomCameraSize;
    private float cameraSizeSub;

    private float ratio = 0.0f;
    private float addRatio;

    private float cameraHeight;
    private float player2Height;
    private float heightSub;

    private GameObject player1pPos;
    private GameObject player2pPos;

    private bool endZoom = false;

    // Start is called before the first frame update
    void Start()
    {
        TryGetComponent(out cc);

        cameraSize = cc.orthographicSize;
        zoomCameraSize = cameraSize / zoomRatio;
        cameraSizeSub = zoomCameraSize - cameraSize;

        addRatio = 1.0f / zoomFrame;

        cameraHeight = transform.position.y;
        heightSub = player2Height - cameraHeight;

        player1pPos = GameObject.Find("Player_1_Pos");
        player2pPos = GameObject.Find("Player_2_Pos");
    }

    // Update is called once per frame
    void Update()
    {
        ratio += addRatio;
        if (1.0f < ratio) ratio = 1.0f;

        cc.orthographicSize = cameraSize + (cameraSizeSub * EaseInSine(ratio));
        transform.position = new Vector3(transform.position.x, cameraHeight + (heightSub * EaseInSine(ratio)), transform.position.z);

        if (ratio == 1.0f)
        {
            endZoom  = true;
        }
    }

    private float EaseInSine(float inputValue) { return 1 - Mathf.Cos((inputValue * Mathf.PI) / 2); }

    public void Setting(float zr, int zf, float p2h)
    {
        zoomRatio = zr;
        zoomFrame = zf;
        player2Height = p2h;
    }

    public bool GetEndZoom() 
    {
        return endZoom;
    }

    /*
    IEnumerator ClearDelay()
    {
        // 1•b‘Ò‚Â
        yield return new WaitForSeconds(2);

        var ct = gameObject.AddComponent<CameraTilt>();
        transform.position = new Vector3(transform.position.x, player1pPos.transform.position.y, -10);
        ct.Setting(tiltFrame, (player1pPos.transform.position.y - player2pPos.transform.position.y), player1pPos.transform.position.y);
        Destroy(gameObject.GetComponent<FollowPlayer>());
        Destroy(this);
    }
    */
}
