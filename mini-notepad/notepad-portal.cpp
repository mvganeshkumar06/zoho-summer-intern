#include <bits/stdc++.h>
#include "notepad.pb.h"
#include "version-portal.cpp"
using namespace std;

class NotepadPortal
{
    string userName;
    vector<string> notepadNames;
    VersionPortal versionPortal;
    void getExistingNotepadNames(string &userName)
    {
        // Check if folder exist
        string path = "./notepads/" + userName;
        if (!filesystem::exists(path))
        {
            filesystem::create_directory(path);
        }

        // Traverse the files in the folder
        for (const auto &file : filesystem::directory_iterator(path))
        {
            // Parse file name
            string fileName = file.path().filename().string();
            int index = fileName.find(".txt");
            string rawFileName = fileName.substr(0, index);

            // Update notepad names
            notepadNames.push_back(rawFileName);
        }
    }
    bool notepadExist(string &name)
    {
        for (const auto &notepadName : notepadNames)
        {
            if (notepadName == name)
            {
                return true;
            }
        }
        return false;
    }
    bool serializeAndStoreNotepad(string &name, notepad::Notepad &notepad)
    {
        // Serialize notepad and store it in a file
        ofstream oFileStream;
        oFileStream.open("./notepads/" + userName + "/" + name + ".txt", ios::out);
        if (!notepad.SerializeToOstream(&oFileStream))
        {
            cout << "\nUnable to serialize the data\n";
            return false;
        }
        return true;
    }
    bool parseAndReadNotepad(string &name, notepad::Notepad &notepad)
    {
        ifstream iFileStream;
        iFileStream.open("./notepads/" + userName + "/" + name + ".txt", ios::in);
        if (!notepad.ParseFromIstream(&iFileStream))
        {
            cout << "\nUnable to parse the data\n";
            return false;
        }
        return true;
    }
    void addContent(notepad::Notepad &notepad)
    {
        // Get notepad content from user
        cout << "\nEnter the notepad contents\n";
        string line;
        getline(cin >> ws, line);
        while (line != "$")
        {
            // Create content
            notepad::Content *content = notepad.add_contents();
            content->set_line(line);
            getline(cin >> ws, line);
        }
    }
    void removeContent(notepad::Notepad &notepad, int startLine, int endLine)
    {
        // Remove notepad content from start to end line
        google::protobuf::RepeatedPtrField<notepad::Content> *rpf = notepad.mutable_contents();
        if (startLine == endLine)
        {
            rpf->DeleteSubrange(startLine, 1);
        }
        else
        {
            rpf->DeleteSubrange(startLine, endLine - startLine + 1);
        }
    }
    void updateContent(notepad::Notepad &notepad, int startLine, int endLine)
    {
        // Update notepad content from start to end line
        cout << "\nEnter the notepad contents\n";
        string line;
        for (int i = startLine; i <= endLine; i++)
        {
            // Update content
            getline(cin >> ws, line);
            notepad::Content *content = notepad.mutable_contents(i);
            content->set_line(line);
        }
    }

public:
    NotepadPortal(string &name)
    {
        userName = name;
        getExistingNotepadNames(name);
        versionPortal = VersionPortal(5);
    }
    void printOptions()
    {
        cout << "\nOptions\n";
        cout << "1 - List notepads\n";
        cout << "2 - Create notepad\n";
        cout << "3 - Add notepad content\n";
        cout << "4 - Remove notepad content\n";
        cout << "5 - Update notepad content\n";
        cout << "6 - Display notepad\n";
        cout << "7 - Logout\n";
        cout << "\nChoose an option from above - ";
    }
    void listNotepads()
    {
        // Check if notepad exists
        if (notepadNames.size() == 0)
        {
            cout << "\nNo notepad exist\n";
            return;
        }

        // Print notepad names
        cout << "\nThe existing notepads are\n";
        for (int i = 0; i < notepadNames.size(); i++)
        {
            cout << (i + 1) << ". " << notepadNames[i] << "\n";
        }
    }
    bool createNotepad(string &name)
    {
        // Check if notepad exist
        if (notepadExist(name))
        {
            cout << "\nNotepad already exist with the given name\n";
            return false;
        }

        // Generate notepad id
        string id = "n" + to_string(notepadNames.size());

        // Create notepad
        notepad::Notepad notepad;
        notepad.set_id(id);
        notepad.set_name(name);
        notepad.set_user_name(userName);

        // Add notepad content from user
        addContent(notepad);

        // Serialize notepad and store it in a file
        if (!serializeAndStoreNotepad(name, notepad))
        {
            return false;
        }

        cout << "\nNotepad created successfully\n";

        // Update notepad names
        notepadNames.push_back(name);

        return true;
    }
    bool addNotepadContent(string &name)
    {
        // Check if notepad exist
        if (!notepadExist(name))
        {
            cout << "\nNotepad does not exist with the given name\n";
            return false;
        }

        // Parse the notepad from the file
        notepad::Notepad notepad;
        if (!parseAndReadNotepad(name, notepad))
        {
            return false;
        }

        // Add notepad content from user
        addContent(notepad);

        // Serialize notepad and store it in a file
        if (!serializeAndStoreNotepad(name, notepad))
        {
            return false;
        }

        cout << "\nNotepad content added successfully\n";
        return true;
    }
    bool removeNotepadContent(string &name, int startLine, int endLine)
    {
        // Check if notepad exist
        if (!notepadExist(name))
        {
            cout << "\nNotepad does not exist with the given name\n";
            return false;
        }

        // Parse the notepad from the file
        notepad::Notepad notepad;
        if (!parseAndReadNotepad(name, notepad))
        {
            return false;
        }

        // Check if line numbers are valid (using 0 based indexing)
        int n = notepad.contents_size();
        startLine -= 1;
        endLine -= 1;

        if (startLine < 0 || startLine >= n || endLine < 0 || endLine >= n)
        {
            cout << "\nInvalid line numbers\n";
            return false;
        }

        cout << "valid line nums - " << startLine << " " << endLine << "\n";

        // Remove content from start to end line
        removeContent(notepad, startLine, endLine);

        // Serialize notepad and store it in a file
        if (!serializeAndStoreNotepad(name, notepad))
        {
            return false;
        }

        cout << "\nNotepad content removed successfully\n";
        return true;
    }
    bool updateNotepadContent(string &name, int startLine, int endLine)
    {
        // Check if notepad exist
        if (!notepadExist(name))
        {
            cout << "\nNotepad does not exist with the given name\n";
            return false;
        }

        // Parse the notepad from the file
        notepad::Notepad notepad;
        if (!parseAndReadNotepad(name, notepad))
        {
            return false;
        }

        // Check if line numbers are valid (using 0 based indexing)
        int n = notepad.contents_size();
        startLine -= 1;
        endLine -= 1;

        if (startLine < 0 || startLine >= n || endLine < 0 || endLine >= n)
        {
            cout << "\nInvalid line numbers\n";
            return false;
        }

        // Update content from start to end line
        updateContent(notepad, startLine, endLine);

        // Serialize notepad and store it in a file
        if (!serializeAndStoreNotepad(name, notepad))
        {
            return false;
        }

        cout << "\nNotepad content updated successfully\n";
        return true;
    }
    bool displayNotepad(string &name)
    {
        // Check if notepad exist
        if (!notepadExist(name))
        {
            cout << "\nNotepad does not exist with the given name\n";
            return false;
        }

        // Parse the notepad from the file
        notepad::Notepad notepad;
        if (!parseAndReadNotepad(name, notepad))
        {
            return false;
        }

        // Display the notepad content
        cout << "\n"
             << notepad.name() << "\n\n";
        for (int i = 0; i < notepad.contents_size(); i++)
        {
            cout << (i + 1) << ". " << notepad.contents(i).line() << "\n";
        }
        return true;
    }
};