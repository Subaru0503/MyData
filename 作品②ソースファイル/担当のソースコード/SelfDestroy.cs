using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SelfDestroy : MonoBehaviour
{
    [SerializeField] private float deleteTimer;

    // Update is called once per frame
    void Update()
    {
        // 0秒になったら削除
        if(deleteTimer <= 0.0f)
        {
            Destroy(gameObject);
        }

        // 時間経過
        deleteTimer -= Time.deltaTime;
    }
}
