#include <bits/stdc++.h>
using namespace std;

class Landline
{
public:
    string stdCode;
    string number;
    int amount;
    Landline() : amount(0) {}
    void setAmount(int amount)
    {
        this->amount = amount;
    }
};