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
    vector<bool (*)(float, float)> funPtrs = {
        [](float value, float limit)
        { return value < limit; },
        [](float value, float limit)
        { return value <= limit; },
        [](float value, float limit)
        { return value > limit; },
        [](float value, float limit)
        { return value >= limit; },
        [](float value, float limit)
        { return value == limit; },
    };
    bool (*funPtr)(float, float);
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
            if (comparisonOperator != "<" && comparisonOperator != "<=" && comparisonOperator != ">" && comparisonOperator != ">=" && comparisonOperator != "==")
            {
                cout << "\nInvalid comparison operator\n";
                return;
            }
            this->comparisonOperator = comparisonOperator;
            this->limit = limit;
            setFunPtr();
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
    void setFunPtr()
    {
        if (comparisonOperator == "<")
        {
            funPtr = funPtrs[0];
        }
        else if (comparisonOperator == "<=")
        {
            funPtr = funPtrs[1];
        }
        else if (comparisonOperator == ">")
        {
            funPtr = funPtrs[2];
        }
        else if (comparisonOperator == ">=")
        {
            funPtr = funPtrs[3];
        }
        else
        {
            funPtr = funPtrs[4];
        }
    }
    bool isConditionSatisfied()
    {
        return funPtr(value, limit);
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
        cout << "\nSensor - " << name << "\n";
        cout << "Value - " << value << "\n";
        cout << "Battery level - " << batteryLevel << "\n\n";
    }
};