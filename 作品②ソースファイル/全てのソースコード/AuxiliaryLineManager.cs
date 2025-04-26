using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AuxiliaryLine : MonoBehaviour
{
    private float lenght = 0.0f;
    private LineRenderer lineRenderer;
    private Transform parentTransform;

    public LayerMask blockLayer;

    // Start is called before the first frame update
    void Start()
    {
        parentTransform = transform.parent;
        lineRenderer = GetComponent<LineRenderer>();
    }

    // Update is called once per frame
    void Update()
    {
        var hit = Physics2D.Raycast(parentTransform.position + new Vector3(0.0f, parentTransform.localScale.y, 0.0f), Vector2.down, 1000.0f, blockLayer);
        if (hit)
        {
            print(hit.distance);
            lineRenderer.SetPosition(0, parentTransform.position + new Vector3(0.0f, parentTransform.localScale.y, 0.0f));
            lineRenderer.SetPosition(1, hit.point);

            transform.localScale = new Vector2(hit.distance * 10,transform.localScale.y);
        }
    }

    void SetLength(float l)
    {
        lenght = l;
    }
}
