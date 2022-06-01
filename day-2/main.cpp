#include <bits/stdc++.h>
#include "bank.cpp"
#include "loan.cpp"
#include "banks.cpp"
#include "broker.cpp"
using namespace std;

int main()
{
    Hdfc hdfc("123", PRIVATE, "ABC", PERSONAL, 8.5);
    Sbi sbi("234", PUBLIC, "DEF", GOLD, 5.6);
    Icici icici("345", PUBLIC, "GHI", LAND, 5.8);
    IndianBank indianBank("456", PRIVATE, "JKL", PERSONAL, 6.7);

    vector<Bank> banks = {hdfc, sbi, icici, indianBank};
    for (auto it : banks)
    {
        it.printInfo();
    }

    cout << "\nPrinting bank info using overridden methods\n";
    hdfc.printInfo();
    sbi.printInfo();
    icici.printInfo();
    indianBank.printInfo();

    Broker b;
    Loan resultBank = b.compare(hdfc, indianBank);
    b.printComparisonResult(resultBank);

    Loan resultBank2 = b.compare(hdfc, icici, indianBank);
    b.printComparisonResult(resultBank2);

    vector<Loan> loans = {hdfc, sbi, icici, indianBank};

    Loan resultBank3 = loans[0];
    b.compare(loans, resultBank3);
    b.printComparisonResult(resultBank3);

    return 0;
}
