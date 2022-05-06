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
public:
    LoanType lType;
    double interestRate;

    Loan(LoanType lType, double interestRate) : lType(lType), interestRate(interestRate) {}

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

enum BankType
{
    PRIVATE,
    PUBLIC
};

class Bank
{
public:
    string name;
    string establishedDate;
    BankType bType;
    string branch;

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

class Solution : public Bank, public Loan
{
public:
    Solution(string name, string establishedDate, BankType bType, string branch, LoanType lType, double interestRate) : Bank(name, establishedDate, bType, branch), Loan(lType, interestRate) {}

    void printInfo()
    {
        Bank::printInfo();
        Loan::printInfo();
    }
};

class Broker
{

public:
    void printComparisonResult(Solution &bank)
    {
        cout << bank.getName() << " has low interest rate compared to other banks\n\n";
    }

    Solution &compare(Solution &bank1, Solution &bank2)
    {
        if (bank1.getInterestRate() <= bank2.getInterestRate())
        {
            return bank1;
        }
        return bank2;
    }
    Solution &compare(Solution &bank1, Solution &bank2, Solution &bank3)
    {
        return compare(compare(bank1, bank2), bank3);
    }
    Solution &compare(vector<Solution> &v, Solution &resultBank)
    {
        for (int i = 1; i < v.size(); i++)
        {
            resultBank = compare(resultBank, v[i]);
        }
        return resultBank;
    }
};

int main()
{
    Solution hdfc("HDFC", "123", PRIVATE, "ABC", GOLD, 8.5), sbi("SBI", "234", PUBLIC, "DEF", GOLD, 5.6), icici("ICICI", "345", PUBLIC, "GHI", LAND, 5.8), indianBank("INDIAN BANK", "456", PRIVATE, "JKL", PERSONAL, 6.7);

    vector<Solution> v = {hdfc, sbi, icici, indianBank};

    for (auto it : v)
    {
        it.printInfo();
    }

    Broker b;
    Solution resultBank = b.compare(hdfc, indianBank);
    b.printComparisonResult(resultBank);

    Solution resultBank2 = b.compare(hdfc, icici, indianBank);
    b.printComparisonResult(resultBank2);

    Solution resultBank3 = v[0];
    b.compare(v, resultBank3);
    b.printComparisonResult(resultBank3);

    return 0;
}
