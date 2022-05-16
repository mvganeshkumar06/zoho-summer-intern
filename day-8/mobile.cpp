#include <bits/stdc++.h>
using namespace std;

class Mobile
{
public:
    string number;
    float amount;
    Mobile() : amount(0) {}
    void setAmount(float amount)
    {
        this->amount = amount;
    }
    bool isValid(string &number)
    {
        return this->number == number;
    }
};