#include <bits/stdc++.h>
#include "user-portal.cpp"
using namespace std;

void printOptions()
{
    cout << "\nOptions\n";
    cout << "1 - Sign up\n";
    cout << "2 - Login\n";
    cout << "3 - Exit\n";
    cout << "\nChoose an option from above - ";
}

int main()
{
    UserPortal userPortal;
    while (true)
    {
        printOptions();
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            string name, email, password, location;
            cout << "\nEnter the following details\n";
            cout << "Name - ";
            cin >> name;
            cout << "Email - ";
            cin >> email;
            cout << "Password - ";
            cin >> password;
            cout << "Location - ";
            cin >> location;
            if (userPortal.signUp(name, email, password, location))
            {
                cout << "\nSignup successful, you can now login using your credentials\n";
            }
            else
            {
                cout << "\nUnable to signup\n";
            }
            break;
        }
        case 2:
        {
            string name, password;
            cout << "\nEnter the following details\n";
            cout << "Name - ";
            cin >> name;
            cout << "Password - ";
            cin >> password;
            if (userPortal.login(name, password))
            {
                cout << "\nLogin successful\n";
            }
            else
            {
                cout << "\nUnable to login\n";
            }
            break;
        }
        case 3:
        {
            return 0;
        }
        default:
            cout << "\nChoose a correct option\n";
            break;
        }
    }
    return 0;
}