#include <bits/stdc++.h>
using namespace std;

class Passenger
{
    string name;
    int age;
    char destination;

public:
    Passenger(string name, int age, char destination) : name(name), age(age), destination(destination) {}
    string getName()
    {
        return name;
    }
    int getAge()
    {
        return age;
    }
    char getDestination()
    {
        return destination;
    }
    void printDetails()
    {
        cout << "\nName - " << name << "\n";
        cout << "Age - " << age << "\n";
        cout << "Destination - " << destination << "\n";
    }
};