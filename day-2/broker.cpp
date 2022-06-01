#include <bits/stdc++.h>
using namespace std;

class Broker
{

public:
    void printComparisonResult(Loan &bank)
    {
        cout << bank.getBankName() << " has low interest rate compared to other banks\n\n";
    }

    Loan &compare(Loan &bank1, Loan &bank2)
    {
        if (bank1.getInterestRate() <= bank2.getInterestRate())
        {
            return bank1;
        }
        return bank2;
    }
    Loan &compare(Loan &bank1, Loan &bank2, Loan &bank3)
    {
        return compare(compare(bank1, bank2), bank3);
    }
    Loan &compare(vector<Loan> &v, Loan &resultBank)
    {
        for (int i = 1; i < v.size(); i++)
        {
            resultBank = compare(resultBank, v[i]);
        }
        return resultBank;
    }
};