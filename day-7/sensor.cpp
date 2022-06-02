#include <bits/stdc++.h>
#include "device.cpp"
using namespace std;

string devices[3] = {"fan", "light", "door"};
Device fan = Device(devices[0]), light = Device(devices[1]), door = Device(devices[2]);

class Sensor
{
public:
    string name;
    int batteryLevel;
    Status status;
    float value;
    string comparisonOperator;
    float limit;
    string deviceName;
    string functionName;
    Sensor() {}
    Sensor(string &name) : name(name), batteryLevel(5), status(OFFLINE), value(20.2f) {}
    void setStatus(Status status)
    {
        this->status = status;
        cout << "\n"
             << name << " Sensor is " << (status == 0 ? "ONLINE" : "OFFLINE") << "\n";
    }
    void setValue(float value)
    {
        if (status == ONLINE)
        {
            this->value = value;
        }
    }
    void setBatteryLevel(int batteryLevel)
    {
        if (status == ONLINE)
        {
            this->batteryLevel = batteryLevel;
        }
    }
    void setCondition(string &comparisonOperator, float limit)
    {
        if (status == ONLINE)
        {
            this->comparisonOperator = comparisonOperator;
            this->limit = limit;
        }
    }
    void setAction(string &deviceName, string &functionName)
    {
        if (status == ONLINE)
        {
            this->deviceName = deviceName;
            this->functionName = functionName;
        }
    }
    bool isConditionSatisfied()
    {
        if (comparisonOperator == "<")
        {
            return value < limit;
        }
        else if (comparisonOperator == "<=")
        {
            return value <= limit;
        }
        else if (comparisonOperator == ">")
        {
            return value > limit;
        }
        else if (comparisonOperator == ">=")
        {
            return value >= limit;
        }
        else if (comparisonOperator == "==")
        {
            return value == limit;
        }
        cout << "\nInvalid comparison operator\n";
        return false;
    }
    void onValueChange()
    {
        if (status == ONLINE)
        {
            if (isConditionSatisfied())
            {
                if (deviceName == "fan")
                {
                    if (functionName == "turnOn")
                    {
                        fan.turnOn();
                    }
                    else if (functionName == "turnOff")
                    {
                        fan.turnOff();
                    }
                    else
                    {
                        cout << "\nInvalid function name\n";
                    }
                }
                else if (deviceName == "light")
                {
                    if (functionName == "turnOn")
                    {
                        light.turnOn();
                    }
                    else if (functionName == "turnOff")
                    {
                        light.turnOff();
                    }
                    else
                    {
                        cout << "\nInvalid function name\n";
                    }
                }
                else if (deviceName == "door")
                {
                    if (functionName == "turnOn")
                    {
                        door.turnOn();
                    }
                    else if (functionName == "turnOff")
                    {
                        door.turnOff();
                    }
                    else
                    {
                        cout << "\nInvalid function name\n";
                    }
                }
            }
        }
    }
    void printInfo()
    {
        cout << "Sensor - " << name << "\n";
        cout << "Value - " << value << "\n";
        cout << "Battery level - " << batteryLevel << "\n\n";
    }
};