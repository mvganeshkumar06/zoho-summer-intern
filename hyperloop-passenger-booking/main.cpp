#include <bits/stdc++.h>
#include "hyperloop-booking.cpp"
using namespace std;

void printOptions()
{
    cout << "\nOptions\n";
    cout << "1 - Init.\n";
    cout << "2 - Add passenger.\n";
    cout << "3 - Start pod.\n";
    cout << "4 - Print queue.\n";
    cout << "5 - Exit.\n";
    cout << "\nChoose an option from above - ";
}

int main()
{
    HyperLoopBooking hyperloopBooking;

    while (true)
    {
        printOptions();
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            hyperloopBooking.init();
            break;
        case 2:
            hyperloopBooking.addPassenger();
            break;
        case 3:
            hyperloopBooking.startPod();
            break;
        case 4:
            hyperloopBooking.printQueue();
            break;
        case 5:
            return 0;
            break;
        default:
            cout << "\nChoose a correct option\n";
            break;
        }
    }

    return 0;
}