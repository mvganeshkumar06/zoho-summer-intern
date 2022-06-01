#include <bits/stdc++.h>
using namespace std;

class Hdfc : public Bank, public Loan
{
    string tagline = "We Understand Your World";
    double multiplier = 1.2;

public:
    Hdfc(string establishedDate, BankType bType, string branch, LoanType lType, double interestRate) : Bank("HDFC", establishedDate, bType, branch), Loan("HDFC", lType, interestRate) {}

    string getName()
    {
        return name + " - " + tagline;
    }
    string getEstablishedDate()
    {
        return name + " Est on - " + establishedDate;
    }
    string getBranch()
    {
        return name + " Branch - " + branch;
    }
    string getLoanType()
    {
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
    double getIntrestRate()
    {
        return interestRate * multiplier;
    }
    void printDocumentsRequired()
    {
        if (lType == 1)
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
        cout << "\nBank Details\n";
        cout << "Name - " << getName() << "\n";
        cout << "Established Date - " << getEstablishedDate() << "\n";
        cout << "Type - " << getBankType() << "\n";
        cout << "Branch - " << getBranch() << "\n\n";

        cout << "\nLoan Details\n";
        cout << "Type - " << getLoanType() << "\n";
        cout << "Interest Rate - " << getInterestRate() << "\n";
        printDocumentsRequired();
        cout << "\n";
    }
};

class Sbi : public Bank, public Loan
{
    string tagline = "PURE BANKING, NOTHING ELSE";
    double multiplier = 1.5;

public:
    Sbi(string establishedDate, BankType bType, string branch, LoanType lType, double interestRate) : Bank("SBI", establishedDate, bType, branch), Loan("SBI", lType, interestRate) {}

    string getName()
    {
        return name + " - " + tagline;
    }
    string getEstablishedDate()
    {
        return name + " Est on - " + establishedDate;
    }
    string getBranch()
    {
        return name + " Branch - " + branch;
    }
    string getLoanType()
    {
        if (lType == 0)
        {
            return "GOLD";
        }
        if (lType == 2)
        {
            return "PERSONAL";
        }
        return "Invalid Loan Type";
    }
    double getIntrestRate()
    {
        return interestRate * multiplier;
    }
    void printDocumentsRequired()
    {
        if (lType == 0)
        {
            cout << "Document G1, Document G2, Document G3\n";
        }
        else if (lType == 2)
        {
            cout << "Document P1, Document P2, Document P3\n";
        }
    }
    void printInfo()
    {
        cout << "\nBank Details\n";
        cout << "Name - " << getName() << "\n";
        cout << "Established Date - " << getEstablishedDate() << "\n";
        cout << "Type - " << getBankType() << "\n";
        cout << "Branch - " << getBranch() << "\n\n";

        cout << "\nLoan Details\n";
        cout << "Type - " << getLoanType() << "\n";
        cout << "Interest Rate - " << getInterestRate() << "\n";
        printDocumentsRequired();
        cout << "\n";
    }
};

class Icici : public Bank, public Loan
{
    string tagline = "Hum Hai Na";
    double multiplier = 1.8;

public:
    Icici(string establishedDate, BankType bType, string branch, LoanType lType, double interestRate) : Bank("ICICI", establishedDate, bType, branch), Loan("ICICI", lType, interestRate) {}

    string getName()
    {
        return name + " - " + tagline;
    }
    string getEstablishedDate()
    {
        return name + " Est on - " + establishedDate;
    }
    string getBranch()
    {
        return name + " Branch - " + branch;
    }
    string getLoanType()
    {
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
    double getIntrestRate()
    {
        return interestRate * multiplier;
    }
    void printDocumentsRequired()
    {
        if (lType == 1)
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
        cout << "\nBank Details\n";
        cout << "Name - " << getName() << "\n";
        cout << "Established Date - " << getEstablishedDate() << "\n";
        cout << "Type - " << getBankType() << "\n";
        cout << "Branch - " << getBranch() << "\n\n";

        cout << "\nLoan Details\n";
        cout << "Type - " << getLoanType() << "\n";
        cout << "Interest Rate - " << getInterestRate() << "\n";
        printDocumentsRequired();
        cout << "\n";
    }
};

class IndianBank : public Bank, public Loan
{
    string tagline = "Your own bank";
    double multiplier = 2.2;

public:
    IndianBank(string establishedDate, BankType bType, string branch, LoanType lType, double interestRate) : Bank("Indian Bank", establishedDate, bType, branch), Loan("Indian Bank", lType, interestRate) {}

    string getName()
    {
        return name + " - " + tagline;
    }
    string getEstablishedDate()
    {
        return name + " Est on - " + establishedDate;
    }
    string getBranch()
    {
        return name + " Branch - " + branch;
    }
    string getLoanType()
    {
        if (lType == 0)
        {
            return "GOLD";
        }
        if (lType == 2)
        {
            return "PERSONAL";
        }
        return "Invalid Loan Type";
    }
    double getIntrestRate()
    {
        return interestRate * multiplier;
    }
    void printDocumentsRequired()
    {
        if (lType == 0)
        {
            cout << "Document G1, Document G2, Document G3\n";
        }
        else if (lType == 2)
        {
            cout << "Document P1, Document P2, Document P3\n";
        }
    }
    void printInfo()
    {
        cout << "\nBank Details\n";
        cout << "Name - " << getName() << "\n";
        cout << "Established Date - " << getEstablishedDate() << "\n";
        cout << "Type - " << getBankType() << "\n";
        cout << "Branch - " << getBranch() << "\n\n";

        cout << "\nLoan Details\n";
        cout << "Type - " << getLoanType() << "\n";
        cout << "Interest Rate - " << getInterestRate() << "\n";
        printDocumentsRequired();
        cout << "\n";
    }
};