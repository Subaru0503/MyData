using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class AllStageManager
{
    // Start is called before the first frame update
    [SerializeField] private const int stages = 3;
    [SerializeField] private const int achievements = 3;
    [SerializeField] static private bool[,] ClearFlag = new bool[stages, achievements];


    static void InitializeAchievements()
    {
        for (int i = 0; i < stages; i++)
        {
            for (int j = 0; j < achievements; j++)
            {
                ClearFlag[i, j] = false; // 全て未開放
            }
        }
    }

    // 実績の初期化（全て未開放）

   public static void UnlockAchievement(int stage, int achievementIndex)
    {
        if (stage >= 0 && stage < stages && achievementIndex >= 0 && achievementIndex < achievements)
        {
            ClearFlag[stage, achievementIndex] = true; // 実績を開放
        }
    }

    public static bool GetAchievement(int stage, int achievementIndex)
    {
        if (stage >= 0 && stage < stages && achievementIndex >= 0 && achievementIndex < achievements)
        {
           return ClearFlag[stage, achievementIndex]; // 実績を開放
        }
        return false;
    }

}
