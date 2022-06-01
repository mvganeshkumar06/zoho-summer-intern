#include <bits/stdc++.h>
using namespace std;

enum LoanType
{
    GOLD,
    LAND,
    PERSONAL
};

class Loan
{
protected:
    string bankName;
    LoanType lType;
    double interestRate;

public:
    Loan(string bankName, LoanType lType, double interestRate) : bankName(bankName), lType(lType), interestRate(interestRate) {}

    string getBankName()
    {
        return bankName;
    }
    string getLoanType()
    {
        if (lType == 0)
        {
            return "GOLD";
        }
        if (lType == 1)
        {
            return "LAND";
        }
        if (lType == 2)
        {
            return "PERSONAL";
        }
        return "Invalid Loan Type";
    }
    double getInterestRate()
    {
        return interestRate;
    }
    void printDocumentsRequired()
    {
        if (lType == 0)
        {
            cout << "Document G1, Document G2, Document G3\n";
        }
        else if (lType == 1)
        {
            cout << "Document L1, Document L2, Document L3\n";
        }
        else if (lType == 2)
        {
            cout << "Document P1, Document P2, Document P3\n";
        }
    }
    void printInfo()
    {
        cout << "\nLoan Details\n";
        cout << "Type - " << lType << "\n";
        cout << "Interest Rate - " << interestRate << "\n";
        printDocumentsRequired();
        cout << "\n";
    }
};