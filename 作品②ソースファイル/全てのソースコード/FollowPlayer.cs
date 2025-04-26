using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FollowPlayer : MonoBehaviour
{
    private GameObject player;
    private CameraSizeChange cameraSizeChange;
    private Camera cc;

    private Vector3 protoPos;
    private Vector3 sub;
    //private Rigidbody2D playerRB;

    private float followSpeed = 1.0f;

    private float startHeight = 0.0f;
    private float playerDethHeight = 0.0f;

    private float offset;

    Matrix4x4 p;
    Matrix4x4 v;
    Matrix4x4 pv;

    // Start is called before the first frame update
    void Start()
    {
        //cameraSizeChange = transform.parent.gameObject.GetComponent<CameraSizeChange>();
        transform.parent.gameObject.TryGetComponent(out cameraSizeChange);
        TryGetComponent(out cc);

        //startHeight = transform.position.y;

        //transform.position = new Vector3(transform.position.x, player.transform.position.y, -10);
    }

    void LateUpdate()
    {
        // 画面統一するまでは動いている
        // プレイヤーの相対移動量が大きくなったらカメラを動かす
        // 滑らかに動かしたい

        //if (cameraSizeChange.GetUnion() && transform.position.y < (player.transform.position.y + 1.0f)) return;
        //if (cameraSizeChange.GetUnion()) return;
        if (cameraSizeChange.GetUnion())
        {
            p = cc.projectionMatrix;
            v = cc.worldToCameraMatrix;
            pv = p * v;

            Vector4 pos = pv * new Vector4(player.transform.position.x, player.transform.position.y, player.transform.position.z, 1.0f);

            if (pos.w == 0)
            {
            }

            float y = pos.y / pos.w;

            if (y < -1.0f)
            {
                cameraSizeChange.SetSeparation();
            }
        }
        else
        {
            protoPos = Vector2.Lerp(transform.position, new Vector3(player.transform.position.x, player.transform.position.y + offset, 0.0f), Time.deltaTime * followSpeed);
            if (startHeight < protoPos.y) transform.position = new Vector3(transform.position.x, protoPos.y, -10.0f);

            if (player.transform.position.y < playerDethHeight)
            {
                protoPos = Vector2.Lerp(transform.position, new Vector3(player.transform.position.x, player.transform.position.y + offset, 0.0f), Time.deltaTime * followSpeed);
                if ((playerDethHeight - 1.0f) < protoPos.y) transform.position = new Vector3(transform.position.x, protoPos.y, -10.0f);
            }
        }
    }

    public void Setting(GameObject p, float s, float o, float sh, float psh)
    {
        player = p;
        followSpeed = s;
        offset = o;
        startHeight = sh;
        playerDethHeight = psh - 1.0f;
    }
}
