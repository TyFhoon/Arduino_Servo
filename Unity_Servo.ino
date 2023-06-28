using System.Collections;
using UnityEngine;
using System;
using System.IO;
using System.IO.Ports;
using TMPro;

public class Ard_Script : MonoBehaviour
{
    //Connects the Serial port of the arduino to unity
    public SerialPort serial = new SerialPort("COM3", 9600);
    public TMP_Text Temp_Output;
    public TMP_Text Servo_Output;

    //gets the temperature from the arduino
    private string getLine;
    //After getting the value from Arduino, 2 values are outputted, the sensor and its reading
    private string OutputSensor;
    private string OutputValue;

    void Start()
    {
        serial.Open();
    }

    void OpenSerial()
    {
        if (serial.IsOpen == false)
        {
            serial.Open();
        }
    }

    //Checks if this get line is for the right sensor (Temp or servo)
    void CheckSensor()
    {
        getLine = serial.ReadLine();
        Debug.Log(getLine);
        string[] splitGetLine = getLine.Split(',');
        OutputSensor = splitGetLine[0];
        OutputValue = splitGetLine[1];
    }

    void Update()
    {
        //Outputs the temperature
        CheckSensor();
        if (OutputSensor == "Temp")
        {
            Temp_Output.text = OutputValue;
        }
        else if (OutputSensor == "Servo")
        {
            Servo_Output.text = OutputValue;
        }
    }
    //ON BUTTON
    public void OnFunc()
    {
        OpenSerial();
        //Sends "A" to arduino to turn ON
        serial.Write("T");
        Debug.Log("On");
    }
    //OFF BUTTON
    public void OffFunc()
    {
        OpenSerial();
        //Sends "a" to arduino to turn OFF
        serial.Write("t");
        Debug.Log("Off");
    }
    //RIGHT BUTTON
    public void RightFunc()
    {
        if (serial.IsOpen == false)
        {
            serial.Open();
        }
        //Sends "S" to arduino to make the servo go Right
        serial.Write("S");
        Debug.Log("Right");
    }
    //LEFT BUTTON
    public void LeftFunc()
    {
        if (serial.IsOpen == false)
        {
            serial.Open();
        }
        //Sends "s" to arduino to make the servo go left
        serial.Write("s");
        Debug.Log("Left");
    }
}
