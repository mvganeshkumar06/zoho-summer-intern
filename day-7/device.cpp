#include <bits/stdc++.h>
using namespace std;

enum Status
{
    ONLINE,
    OFFLINE
};

class Device
{
public:
    string name;
    Status status;
    Device() {}
    Device(string &name) : name(name) {}
    void turnOn()
    {
        if (status == OFFLINE)
        {
            status = ONLINE;
            cout << "\n"
                 << name << " is turned ON.\n";
        }
    }
    void turnOff()
    {
        if (status == ONLINE)
        {
            status = OFFLINE;
            cout << "\n"
                 << name << " is turned OFF.\n";
        }
    }
};