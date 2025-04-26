using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
public class StersDrower : MonoBehaviour
{
    [SerializeField] private int _stage;
    [SerializeField] private GameObject[] _Sters;
    [SerializeField] private Image[] _Texts;
   public bool[] bools = new bool[3];

    // Start is called before the first frame update
    void Start()
    {
        for (int i = 0; i < 3; i++)
        {
            CheckAchievement(i);
        }
    }
    public void DrawSters()
    {
        for (int i = 0; i < 3; i++)
        {
            CheckAchievement(i);
        }
    }

    void CheckAchievement(int index)
    {
        bool check = AllStageManager.GetAchievement(_stage, index);
        _Sters[index].SetActive(check);
        if (check)
        {
            _Texts[index].color = new Vector4(255, 255, 255, 255);
        }
        else 
        {
            _Texts[index].color = new Vector4(255,255,255,125);
        }
        bools[index] = check;
    }

}
