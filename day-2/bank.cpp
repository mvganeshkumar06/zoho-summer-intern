#include <bits/stdc++.h>
using namespace std;

enum BankType
{
    PRIVATE,
    PUBLIC
};

class Bank
{
protected:
    string name;
    string establishedDate;
    BankType bType;
    string branch;

public:
    Bank(string name, string establishedDate, BankType bType, string branch) : name(name), establishedDate(establishedDate), bType(bType), branch(branch) {}

    string getName()
    {
        return name;
    }
    string getEstablishedDate()
    {
        return establishedDate;
    }
    string getBankType()
    {
        if (bType == 0)
        {
            return "PRIVATE";
        }
        if (bType == 1)
        {
            return "PUBLIC";
        }
        return "Invalid Bank Type";
    }
    string getBranch()
    {
        return branch;
    }
    void printInfo()
    {
        cout << "\nBank Details\n";
        cout << "Name - " << name << "\n";
        cout << "Established Date - " << establishedDate << "\n";
        cout << "Type - " << getBankType() << "\n";
        cout << "Branch - " << branch << "\n\n";
    }
};