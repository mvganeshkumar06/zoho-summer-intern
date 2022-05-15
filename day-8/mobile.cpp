#include <bits/stdc++.h>
using namespace std;

class Mobile
{
public:
    string number;
    int amount;
    Mobile() : amount(0) {}
    void setAmount(int amount)
    {
        this->amount = amount;
    }
};