#include <bits/stdc++.h>
using namespace std;

class Landline
{
public:
    string stdCode;
    string number;
    float amount;
    Landline() : amount(0) {}
    void setAmount(float amount)
    {
        this->amount = amount;
    }
    bool isValid(string &number)
    {
        return this->stdCode + this->number == number;
    }
};