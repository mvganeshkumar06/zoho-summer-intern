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
        T *connection = NULL;
        for (auto &e : connections)
        {
            if (e.number == number)
            {
                connection = &e;
                break;
            }
        }
        return connection;
    }
    void payBill(string &number)
    {
        T *connection = getConnection(number);
        if (connection != NULL)
        {
            cout << "\nBill payed $" << connection->amount << " for the number " << number << ".\n";
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
    bpl.updateBill(l.number, 100);
    bpl.payBill(l.number);

    return 0;
}