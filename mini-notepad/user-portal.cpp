#include <bits/stdc++.h>
#include "notepad.pb.h"
using namespace std;

class UserPortal
{
    bool isAlphabet(char ch)
    {
        return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
    }
    bool isNumeric(char ch)
    {
        return (ch >= '0' && ch <= '9');
    }
    bool isSpecialChar(char ch)
    {
        return !isAlphabet(ch) && !isNumeric(ch) && ch != '.';
    }
    bool isValidEmail(string &email)
    {
        int n = email.size();
        auto atIndex = email.find("@");
        auto dotIndex = email.find(".");
        // Check if @ and . exist
        if (atIndex == string::npos || dotIndex == string::npos)
        {
            return false;
        }
        // Check if position of @ and . is valid
        if (atIndex == 0 || atIndex == n - 1 || dotIndex == 0 || dotIndex == n - 1 || dotIndex - atIndex == 1)
        {
            return false;
        }
        // Check if characters other than @ and . are valid
        for (int i = 0; i < atIndex; i++)
        {
            if (isSpecialChar(email[i]))
            {
                return false;
            }
        }
        for (int i = atIndex + 1; i < dotIndex; i++)
        {
            if (!isAlphabet(email[i]))
            {
                return false;
            }
        }
        for (int i = dotIndex + 1; i < n; i++)
        {
            if (!isAlphabet(email[i]))
            {
                return false;
            }
        }
        return true;
    }
    int getCharIndex(char ch)
    {
        return tolower(ch) - 'a';
    }
    void encryptPassword(string &password)
    {
        int k = 6, n = 26;
        for (char &ch : password)
        {
            ch = 'a' + ((getCharIndex(ch) + k) % n);
        }
    }
    bool isValidPassword(string &currPassword, string &savedPassword)
    {
        return currPassword == savedPassword;
    }
    bool getExistingUsers(notepad::Users &users)
    {
        ifstream iFileStream;
        iFileStream.open("users.txt", ios::in | ios::binary);
        if (!users.ParseFromIstream(&iFileStream))
        {
            cout << "\nUnable to parse the data\n";
            return false;
        }
        return true;
    }
    int getUserIndex(notepad::Users &users, string &name)
    {
        for (int i = 0; i < users.users_size(); i++)
        {
            const auto &user = users.users(i);
            if (user.name() == name)
            {
                return i;
            }
        }
        return -1;
    }

public:
    void printOptions()
    {
        cout << "\nOptions\n";
        cout << "1 - Sign up\n";
        cout << "2 - Login\n";
        cout << "3 - Exit\n";
        cout << "\nChoose an option from above - ";
    }
    bool signUp(string &name, string &email, string &password, string &location)
    {
        // Get the existing users
        notepad::Users users;
        if (!getExistingUsers(users))
        {
            cout << "\nUnable to get the existing users\n";
            return false;
        }

        // Check if user already exist
        int userIndex = getUserIndex(users, name);
        if (userIndex != -1)
        {
            cout << "\nUser already exist\n";
            return false;
        }

        // Check if valid email
        if (!isValidEmail(email))
        {
            cout << "\nInvalid email\n";
            return false;
        }

        // Encrypt the password
        encryptPassword(password);

        // Create user and add it to exising users
        notepad::User *user = users.add_users();
        user->set_name(name);
        user->set_email(email);
        user->set_password(password);
        user->set_location(location);

        // Serialize the users and store it in a file
        ofstream oFileStream;
        oFileStream.open("users.txt", ios::out | ios::binary);
        if (!users.SerializeToOstream(&oFileStream))
        {
            cout << "\nUnable to serialize the data\n";
            return false;
        }
        return true;
    }
    bool login(string &name, string &currPassword)
    {
        // Get the existing users
        notepad::Users users;
        if (!getExistingUsers(users))
        {
            cout << "\nUnable to get the existing users\n";
            return false;
        }

        // Check if user already exist
        int userIndex = getUserIndex(users, name);
        if (userIndex == -1)
        {
            cout << "\nUser does not exist\n";
            return false;
        }
        notepad::User user = users.users(userIndex);

        // Ecrypt the current password
        encryptPassword(currPassword);

        // Check the password of the user
        string savedPassword = user.password();
        if (!isValidPassword(currPassword, savedPassword))
        {
            cout << "\nInvalid password\n";
            return false;
        }
        return true;
    }
};