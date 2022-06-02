#include <bits/stdc++.h>
#include "user-portal.cpp"
#include "notepad-portal.cpp"
using namespace std;

int main()
{
    UserPortal userPortal;
    while (true)
    {
        userPortal.printOptions();
        int choice;
        cin >> choice;
        switch (choice)
        {
        // Sign up
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
        // Login
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
                bool userLoggedIn = true;
                NotepadPortal notepadPortal(name);
                while (userLoggedIn)
                {
                    notepadPortal.printOptions();
                    int choice;
                    cin >> choice;
                    switch (choice)
                    {
                    // List notepads
                    case 1:
                    {
                        notepadPortal.listNotepads();
                        break;
                    }
                    // Create notepad
                    case 2:
                    {
                        cout << "\nEnter notepad name - ";
                        string notepadName;
                        getline(cin >> ws, notepadName);
                        if (!notepadPortal.createNotepad(notepadName))
                        {
                            cout << "\nUnable to create notepad\n";
                        }
                        break;
                    }
                    // Add notepad content
                    case 3:
                    {
                        cout << "\nEnter notepad name - ";
                        string notepadName;
                        getline(cin >> ws, notepadName);
                        if (!notepadPortal.addNotepadContent(notepadName))
                        {
                            cout << "\nUnable to add notepad content\n";
                        }
                        break;
                    }
                    // Remove notepad content
                    case 4:
                    {
                        cout << "\nEnter notepad name - ";
                        string notepadName;
                        getline(cin >> ws, notepadName);
                        cout << "\nEnter the start and end line number to remove - ";
                        int startLine, endLine;
                        cin >> startLine >> endLine;
                        if (!notepadPortal.removeNotepadContent(notepadName, startLine, endLine))
                        {
                            cout << "\nUnable to remove notepad content\n";
                        }
                        break;
                    }
                    // Update notepad content
                    case 5:
                    {
                        cout << "\nEnter notepad name - ";
                        string notepadName;
                        getline(cin >> ws, notepadName);
                        cout << "\nEnter the start and end line number to update - ";
                        int startLine, endLine;
                        cin >> startLine >> endLine;
                        if (!notepadPortal.updateNotepadContent(notepadName, startLine, endLine))
                        {
                            cout << "\nUnable to update notepad content\n";
                        }
                        break;
                    }
                    // Display notepad
                    case 6:
                    {
                        cout << "\nEnter notepad name - ";
                        string notepadName;
                        getline(cin >> ws, notepadName);
                        if (!notepadPortal.displayNotepad(notepadName))
                        {
                            cout << "\nUnable to display notepad\n";
                        }
                        break;
                    }
                    // Display version
                    case 7:
                    {
                        cout << "\nEnter notepad name - ";
                        string notepadName;
                        getline(cin >> ws, notepadName);
                        if (!notepadPortal.displayVersions(notepadName))
                        {
                            cout << "\nUnable to display versions\n";
                        }
                        break;
                    }
                    // Logout
                    case 8:
                    {
                        userLoggedIn = false;
                        break;
                    }
                    default:
                        cout << "\nChoose a correct option\n";
                        break;
                    }
                }
            }
            else
            {
                cout << "\nUnable to login\n";
            }
            break;
        }
        // Exit
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