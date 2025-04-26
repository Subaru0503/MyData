using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SelfDestroy : MonoBehaviour
{
    [SerializeField] private float deleteTimer;

    // Update is called once per frame
    void Update()
    {
        // 0•b‚É‚È‚Á‚½‚çíœ
        if(deleteTimer <= 0.0f)
        {
            Destroy(gameObject);
        }

        // ŠÔŒo‰ß
        deleteTimer -= Time.deltaTime;
    }
}
