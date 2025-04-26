using System.Collections;
using System.Collections.Generic;
//using UnityEditor.SceneManagement;
using UnityEngine;
using UnityEngine.UI;

public class ClearManager : MonoBehaviour
{
    private int _stage;
    [SerializeField] private GameManager _gameManager;
    [SerializeField] private CountTimer _countTimer;
    [SerializeField] private StersDrower _sdrer;
    // Start is called before the first frame update
    void Start()
    {
        _stage = _gameManager.StageNum;
        switch(_stage)
        {
            case 0:
                Stage0Clear();
                break;
            case 1:
                Stage1Clear();
                break;
            case 2:
                Stage2Clear();
                break;
            default:
                break;
        }

    }

   void Stage0Clear()
    {
        
        AllStageManager.UnlockAchievement(_stage, 0);


        if (_countTimer.GetTimer() <= 180)
        {
            AllStageManager.UnlockAchievement(_stage, 1);
        }

        if (_gameManager.GetDropBlocks() <= 5)
        {
            AllStageManager.UnlockAchievement(_stage, 2);
        }
        _sdrer.DrawSters();
    }

    void Stage1Clear()
    {

        AllStageManager.UnlockAchievement(_stage, 0);


        if (_countTimer.GetTimer() <= 480)
        {
            AllStageManager.UnlockAchievement(_stage, 1);
        }

        if (_gameManager.GetDropBlocks() <= 15)
        {
            AllStageManager.UnlockAchievement(_stage, 2);
        }
        _sdrer.DrawSters();
    }

    void Stage2Clear()
    {

        AllStageManager.UnlockAchievement(_stage, 0);


        if (_countTimer.GetTimer() <= 600)
        {
            AllStageManager.UnlockAchievement(_stage, 1);
        }

        if (_gameManager.GetDropBlocks() <= 20)
        {
            AllStageManager.UnlockAchievement(_stage, 2);
        }
        _sdrer.DrawSters();
    }

}
