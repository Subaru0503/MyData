using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BalloonSpawner : MonoBehaviour
{
    [SerializeField] private float itemInterval;
    [SerializeField] private float itemProbability;
    [SerializeField] private GameObject Balloon;
    private SoundManager _SoundManager;

    private float timer = 0f; // 時間を計測するタイマー



    // Start is called before the first frame update
    void Start()
    {
        _SoundManager = GetComponent<SoundManager>();
    }

    // Update is called once per frame
    void Update()
    {
        // タイマーを進める
        timer += Time.deltaTime;

        // タイマーがitemIntervalに達したらリセット
        if (timer >= itemInterval)
        {
            timer = 0f; // タイマーをリセット

            // itemProbabilityの確率でバルーンを生成
            if (Random.value <= itemProbability) 
            {
                GameObject player = GameObject.FindWithTag("Player");

                if (player != null)
                {
                    Vector3 playerPosition = player.transform.position;
                    // バルーンをワールド座標 (0, 0, 0) に生成

                    float xpos  = 7;
                    int randomInt = Random.Range(1, 4); // 0から3までのランダムな整数
                    int randomSign = Random.value < 0.5f ? -1 : 1;
                    xpos *= randomSign;
                    if (xpos > 0)
                    {
                        _SoundManager.PlayerSound(1);
                    }
                    else
                    {
                        _SoundManager.PlayerSound(0);
                    }
                    Instantiate(Balloon, new Vector3(xpos, playerPosition.y + randomInt, 0), Quaternion.identity);
                }



            }
        }
    }
}
