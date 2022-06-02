#include <bits/stdc++.h>
#include "sensor.cpp"
using namespace std;

class Client
{
public:
    string sensors[4] = {"temperature", "motion", "waterLevel", "gasLevel"};
    Sensor temperature, motion, waterLevel, gasLevel;
    Client()
    {
        this->temperature = Sensor(sensors[0]);
        this->motion = Sensor(sensors[1]);
        this->waterLevel = Sensor(sensors[2]);
        this->gasLevel = Sensor(sensors[3]);
    }
    void getTaskTokens(vector<string> &tokens)
    {
        string line;
        getline(cin >> ws, line);

        stringstream ss(line);
        string intermediate;
        while (getline(ss, intermediate, ' '))
        {
            tokens.push_back(intermediate);
        }
    }
    bool isTokensValid(vector<string> &tokens1, vector<string> &tokens2)
    {
        return tokens1.size() == 4 && tokens1[0] == "If:" && tokens2.size() == 3 && tokens2[0] == "Then:";
    }
    bool isSensorFound(string &sensorName)
    {
        for (const string &currName : sensors)
        {
            if (currName == sensorName)
            {
                return true;
            }
        }
        return false;
    }
    bool isDeviceFound(string &deviceName)
    {
        for (const string &currName : devices)
        {
            if (currName == deviceName)
            {
                return true;
            }
        }
        return false;
    }
    void setTasks()
    {
        while (true)
        {
            string option;
            cout << "\nEnter a task or exit [0/1] - ";
            cin >> option;
            if (option == "1")
            {
                break;
            }
            vector<string> tokens1, tokens2;
            getTaskTokens(tokens1);
            getTaskTokens(tokens2);
            if (!isTokensValid(tokens1, tokens2))
            {
                cout << "\nInvalid syntax for task.\n";
                continue;
            }
            string sensorName = tokens1[1], comparisonOperator = tokens1[2], value = tokens1[3], deviceName = tokens2[1], functionName = tokens2[2];
            if (isSensorFound(sensorName))
            {
                if (sensorName == "temperature")
                {
                    temperature.setCondition(comparisonOperator, stof(value));
                }
                else if (sensorName == "motion")
                {
                    motion.setCondition(comparisonOperator, stof(value));
                }
                else if (sensorName == "waterLevel")
                {
                    waterLevel.setCondition(comparisonOperator, stof(value));
                }
                else if (sensorName == "gasLevel")
                {
                    gasLevel.setCondition(comparisonOperator, stof(value));
                }
            }
            else
            {
                cout << "\nSensor not found.\n";
                continue;
            }
            if (isDeviceFound(deviceName))
            {
                if (sensorName == "temperature")
                {
                    temperature.setAction(deviceName, functionName);
                }
                else if (sensorName == "motion")
                {
                    motion.setAction(deviceName, functionName);
                }
                else if (sensorName == "waterLevel")
                {
                    waterLevel.setAction(deviceName, functionName);
                }
                else if (sensorName == "gasLevel")
                {
                    gasLevel.setAction(deviceName, functionName);
                }
            }
            else
            {
                cout << "\nDevice not found.\n";
            }
        }
    }
    void executeEvent(Sensor &sensor, char option)
    {
        if (option == 'i')
        {
            sensor.setValue(sensor.value + 1);
            sensor.onValueChange();
            sensor.setBatteryLevel(sensor.batteryLevel - 1);
            sensor.printInfo();
            fan.printInfo();
            light.printInfo();
            door.printInfo();
        }
        else if (option == 'd')
        {
            sensor.setValue(sensor.value - 1);
            sensor.onValueChange();
            sensor.setBatteryLevel(sensor.batteryLevel - 1);
            sensor.printInfo();
            fan.printInfo();
            light.printInfo();
            door.printInfo();
        }
        else
        {
            cout << "\nInvalid syntax for event.\n";
        }
        if (sensor.batteryLevel == 0)
        {
            cout << "\n"
                 << sensor.name << " Sensor battery too low.\n";
            sensor.setStatus(OFFLINE);
        }
    }
    void listenEvents()
    {
        while (true)
        {
            string option;
            cout << "\nEnter an event or exit [0/1] - ";
            cin >> option;
            if (option == "1")
            {
                break;
            }
            string event;
            cin >> event;
            if (event[0] == 't')
            {
                executeEvent(temperature, event[1]);
            }
            else if (event[0] == 'm')
            {
                executeEvent(motion, event[1]);
            }
            else if (event[0] == 'w')
            {
                executeEvent(waterLevel, event[1]);
            }
            else if (event[0] == 'g')
            {
                executeEvent(gasLevel, event[1]);
            }
            else
            {
                cout << "\nInvalid syntax for event.\n";
            }
        }
    }
    void onConnect()
    {
        temperature.setStatus(ONLINE);
        motion.setStatus(ONLINE);
        waterLevel.setStatus(ONLINE);
        gasLevel.setStatus(ONLINE);
    }
    void onDisconnect()
    {
        temperature.setStatus(OFFLINE);
        motion.setStatus(OFFLINE);
        waterLevel.setStatus(OFFLINE);
        gasLevel.setStatus(OFFLINE);
    }
};

int main()
{
    Client c;
    cout << "\nClient started running.\n";
    c.onConnect();
    cout << "\nSet the conditions to automate your tasks using the below syntax\n";
    cout << "\nIf: <sensor_name> <comparison> <sensor_value>\nThen : <device> <function>\n\n";
    c.setTasks();
    cout << "\nEnter events using the below syntax\n";
    cout << "\n<first_character_of_sensor_name_in_lower_case>[i/d]\n";
    cout << "\nExample - ti - increments the temperature\n";
    c.listenEvents();
    return 0;
}