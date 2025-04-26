using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class SceneChange : MonoBehaviour
{
    private string _sceneName;
    // Start is called before the first frame update

    private void Awake()
    {
        Application.targetFrameRate = 60; // èâä˙èÛë‘ÇÕ-1Ç…Ç»Ç¡ÇƒÇ¢ÇÈ
    }

    void Start()
    {
    }

    // Update is called once per frame
    void Update()
    {
        
    }
    public void CangeScene(string sceneName)
    {
        _sceneName = sceneName;
        StartCoroutine(ExecuteSceneChangeWithDelay());
    }
    private IEnumerator ExecuteSceneChangeWithDelay()
    {
        yield return new WaitForSecondsRealtime(1.2f);
        if (AudioManager.Instance)
            AudioManager.Instance.StopAudio();
        SceneManager.LoadScene(_sceneName);
    }
    public void AudioContinueCS(string sceneName)
    {
        _sceneName = sceneName;
        StartCoroutine(ExecuteAudioContinueWithDelay());
    }
    private IEnumerator ExecuteAudioContinueWithDelay()
    {
        yield return new WaitForSecondsRealtime(1.2f);
        if (AudioManager.Instance)
            AudioManager.Instance.PlayAudio();
        SceneManager.LoadScene(_sceneName);
    }
}
