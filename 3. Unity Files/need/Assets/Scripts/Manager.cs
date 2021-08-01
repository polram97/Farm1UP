using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Manager : MonoBehaviour
{
    bool Planted = false;
    public SpriteRenderer plant;
    public Sprite[] Stages;
    int pstage = 0;
    float timebtwstg = 2f;
    float timer;
    public Text mytext;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if (Planted)
        {
            timer -= Time.deltaTime;
            if (timer < 0 && pstage < Stages.Length-1)
            {
                timer = timebtwstg;
                pstage++;
                ActPlant();
            }
            if (pstage < Stages.Length-1)
            {
                mytext.text = "The plant is growing";
            }
            else
            {
                mytext.text = "The plant is fully growed.";
            }
        }
    }
    private void OnMouseDown()
    {
        if (Planted)
        {
            if (pstage == 3)
            {
                Harvest();
            }
        }
        else
        {
            Planting();
        }
    }
    
    void Harvest()
    {
        Planted = false;
        plant.gameObject.SetActive(false);
        mytext.text = "There is no plant.";
    }
    void Planting()
    {
        Planted = true;
        pstage = 0;
        timer = timebtwstg;
        ActPlant();
        plant.gameObject.SetActive(true);
    }
    void ActPlant()
    {
        plant.sprite = Stages[pstage];
        
    }
}
