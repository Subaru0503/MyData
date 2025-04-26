using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SelfDestroy : MonoBehaviour
{
    [SerializeField] private float deleteTimer;

    // Update is called once per frame
    void Update()
    {
        // 0�b�ɂȂ�����폜
        if(deleteTimer <= 0.0f)
        {
            Destroy(gameObject);
        }

        // ���Ԍo��
        deleteTimer -= Time.deltaTime;
    }
}
