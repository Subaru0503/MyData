using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class TutorialManager : MonoBehaviour
{
    // Start is called before the first frame update
    [SerializeField] private GameObject[] _TutorialSprites;
    public int _currentPage;
    [SerializeField] private GameObject _NextButton;
    [SerializeField] private GameObject _BackButton;
    [SerializeField] private GameObject _EndButton;

    void Start()
    {
        _currentPage = 0;
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void NextPage()
    {
        if (_currentPage < _TutorialSprites.Length - 1)
        {
            if (_currentPage == 0)
            {
                _BackButton.SetActive(true);
            }
            _TutorialSprites[_currentPage].SetActive(false);
            _currentPage++;
            _TutorialSprites[_currentPage].SetActive(true);

            if(_currentPage == _TutorialSprites.Length -1)
            {
                _EndButton.GetComponent<Button>().Select();
                _NextButton.SetActive(false);
            }

        }
    }

    public void BackPage()
    {
        if ( 0 < _currentPage)
        {
            if (_currentPage == _TutorialSprites.Length - 1)
            {
                _NextButton.SetActive(true);
            }
            _TutorialSprites[_currentPage].SetActive(false);
            _currentPage--;
            _TutorialSprites[_currentPage].SetActive(true);

            if (_currentPage == 0)
            {
                _NextButton.GetComponent<Button>().Select();
                _BackButton.SetActive(false);
            }

        }
    }
}
