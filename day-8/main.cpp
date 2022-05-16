#include <bits/stdc++.h>
#include "mobile.cpp"
#include "landline.cpp"
using namespace std;

template <typename T>
class BillPayment
{
public:
    vector<T> connections;
    BillPayment() {}
    void addConnection(T &connection)
    {
        connections.push_back(connection);
    }
    T *getConnection(string &number)
    {
        for (auto &e : connections)
        {
            if (e.isValid(number))
            {
                return &e;
            }
        }
        return NULL;
    }
    void payBill(string &number)
    {
        T *connection = getConnection(number);
        if (connection != NULL)
        {
            cout << "\nBill payed $" << connection->amount << " for the number " << connection->number << ".\n";
            connection->amount = 0;
        }
        else
        {
            cout << "\nInvalid connection number.\n";
        }
    }
    void updateBill(string &number, int amount)
    {
        T *connection = getConnection(number);
        if (connection != NULL)
        {
            int updatedAmount = connection->amount + amount;
            cout << "\nBill amount updated from " << connection->amount << " to " << updatedAmount << ".\n";
            connection->setAmount(updatedAmount);
        }
        else
        {
            cout << "\nInvalid connection number.\n";
        }
    }
};

int main()
{
    BillPayment<Mobile> bpm;
    Mobile m;
    cout << "\nEnter mobile number - ";
    cin >> m.number;
    bpm.addConnection(m);
    bpm.updateBill(m.number, 200);
    bpm.payBill(m.number);

    BillPayment<Landline> bpl;
    Landline l;
    cout << "\nEnter STD code and landline number - ";
    cin >> l.stdCode >> l.number;
    bpl.addConnection(l);
    string landlineNumber = l.stdCode + l.number;
    bpl.updateBill(landlineNumber, 100);
    bpl.payBill(landlineNumber);

    return 0;
}