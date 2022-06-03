#include <bits/stdc++.h>
#include "notepad.pb.h"
using namespace std;

class NotepadPortal
{
    string userName;
    vector<string> notepadNames;
    int versionChangesLimit = 5;
    vector<string> versionNames;
    void getExistingNotepadNames()
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
            cout << "\nUnable to serialize the notepad data\n";
            return false;
        }
        return true;
    }
    bool parseAndReadNotepad(string &name, notepad::Notepad &notepad)
    {
        // Parse notepad and read from the file
        ifstream iFileStream;
        iFileStream.open("./notepads/" + userName + "/" + name + ".txt", ios::in);
        if (!notepad.ParseFromIstream(&iFileStream))
        {
            cout << "\nUnable to parse the notepad data\n";
            return false;
        }
        return true;
    }
    void getExistingVersionNames()
    {
        // Check if folder exist
        string path = "./versions/" + userName;
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

            // Update version names
            versionNames.push_back(rawFileName);
        }
    }
    bool versionExist(string &name)
    {
        for (const auto &versionName : versionNames)
        {
            if (versionName == name)
            {
                return true;
            }
        }
        return false;
    }
    bool serializeAndStoreVersion(string &notepadName, notepad::Versions &versions)
    {
        // Serialize versions and store it in a file
        ofstream oFileStream;
        oFileStream.open("./versions/" + userName + "/" + notepadName + ".txt", ios::out);
        if (!versions.SerializeToOstream(&oFileStream))
        {
            cout << "\nUnable to serialize the versions\n";
            return false;
        }
        return true;
    }
    bool parseAndReadVersions(string &notepadName, notepad::Versions &versions)
    {
        // Parse versions and read from the file
        ifstream iFileStream;
        iFileStream.open("./versions/" + userName + "/" + notepadName + ".txt", ios::in);
        if (!versions.ParseFromIstream(&iFileStream))
        {
            cout << "\nUnable to parse the versions\n";
            return false;
        }
        return true;
    }
    void createVersion(int versionSize, string &notepadId, notepad::Version *version)
    {
        // Generate version id
        string id = "v" + to_string(versionSize + 1);

        // Generate version number (1 based indexing)
        int number = versionSize + 1;

        // Update version
        version->set_id(id);
        version->set_number(number);
        time_t currTime = time(NULL);
        string createdTime = string(ctime(&currTime));
        version->set_created_time(createdTime);
        version->set_notepad_id(notepadId);
    }
    bool addContentAndUpdateVersion(notepad::Notepad &notepad, notepad::Versions &versions, notepad::Version *version)
    {
        // Create change to add to version
        notepad::Change *change = version->add_changes();

        // Start line for the change (0 based indexing)
        int startLine = notepad.contents_size();

        // Get notepad content from user
        cout << "\nEnter the notepad contents\n";
        string line;
        while (true)
        {
            getline(cin >> ws, line);
            if (line == "$")
            {
                break;
            }
            // Create content
            notepad::Content *content = notepad.add_contents();
            content->set_line(line);

            // Update change contents
            notepad::Content *changeContent = change->add_contents();
            changeContent->set_line(line);
        }

        // End line for the change (0 based indexing)
        int endLine = startLine + change->contents_size() - 1;

        // Update change
        change->set_name(notepad::ChangeName::ADD);
        change->set_start_line(startLine);
        change->set_end_line(endLine);

        string notepadName = notepad.name();

        // Serialize versions and store it in a file
        if (!serializeAndStoreVersion(notepadName, versions))
        {
            return false;
        }

        return true;
    }
    bool addNotepadContentHelper(notepad::Notepad &notepad)
    {
        string notepadId = notepad.id(), notepadName = notepad.name();

        // Create versions
        notepad::Versions versions;

        // Parse versions and read from the file
        if (!parseAndReadVersions(notepadName, versions))
        {
            return false;
        }

        int versionSize = versions.versions_size();

        // If the latest version changes reached the limit
        if (versionSize == 0 || versions.versions(versionSize - 1).changes_size() == versionChangesLimit)
        {
            // Create the next version
            notepad::Version *nextVersion = versions.add_versions();
            createVersion(versionSize, notepadId, nextVersion);
            if (!addContentAndUpdateVersion(notepad, versions, nextVersion))
            {
                return false;
            }
        }
        else
        {
            notepad::Version *version = versions.mutable_versions(versions.versions_size() - 1);
            if (!addContentAndUpdateVersion(notepad, versions, version))
            {
                return false;
            }
        }

        return true;
    }
    bool removeContentAndUpdateVersion(notepad::Notepad &notepad, notepad::Versions &versions, notepad::Version *version, int startLine, int endLine)
    {
        // Create change to add to version
        notepad::Change *change = version->add_changes();

        // Copy the notepad content from start to end line before removing
        for (int i = startLine; i <= endLine; i++)
        {
            notepad::Content content = notepad.contents(i);
            notepad::Content *changeContent = change->add_contents();
            changeContent->set_line(content.line());
        }

        // Remove notepad content from start to end line
        google::protobuf::RepeatedPtrField<notepad::Content> *contentRpf = notepad.mutable_contents();
        if (startLine == endLine)
        {
            contentRpf->DeleteSubrange(startLine, 1);
        }
        else
        {
            contentRpf->DeleteSubrange(startLine, endLine - startLine + 1);
        }

        // Update change
        change->set_name(notepad::ChangeName::REMOVE);
        change->set_start_line(startLine);
        change->set_end_line(endLine);

        string notepadName = notepad.name();

        // Serialize versions and store it in a file
        if (!serializeAndStoreVersion(notepadName, versions))
        {
            return false;
        }

        return true;
    }
    bool removeNotepadContentHelper(notepad::Notepad &notepad, int startLine, int endLine)
    {
        string notepadId = notepad.id(), notepadName = notepad.name();

        // Create versions
        notepad::Versions versions;

        // Parse versions and read from the file
        if (!parseAndReadVersions(notepadName, versions))
        {
            return false;
        }

        int versionSize = versions.versions_size();

        // If the latest version changes reached the limit
        if (versionSize == 0 || versions.versions(versionSize - 1).changes_size() == versionChangesLimit)
        {
            // Create the next version
            notepad::Version *nextVersion = versions.add_versions();
            createVersion(versionSize, notepadId, nextVersion);
            if (!removeContentAndUpdateVersion(notepad, versions, nextVersion, startLine, endLine))
            {
                return false;
            }
        }
        else
        {
            notepad::Version *version = versions.mutable_versions(versions.versions_size() - 1);
            if (!removeContentAndUpdateVersion(notepad, versions, version, startLine, endLine))
            {
                return false;
            }
        }

        return true;
    }
    bool updateContentAndUpdateVersion(notepad::Notepad &notepad, notepad::Versions &versions, notepad::Version *version, int startLine, int endLine)
    {
        // Create change to add to version
        notepad::Change *change = version->add_changes();

        // Copy the notepad content from start to end line before updating
        for (int i = startLine; i <= endLine; i++)
        {
            notepad::Content content = notepad.contents(i);
            notepad::Content *changeContent = change->add_contents();
            changeContent->set_line(content.line());
        }

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

        // Update change
        change->set_name(notepad::ChangeName::UPDATE);
        change->set_start_line(startLine);
        change->set_end_line(endLine);

        string notepadName = notepad.name();

        // Serialize versions and store it in a file
        if (!serializeAndStoreVersion(notepadName, versions))
        {
            return false;
        }

        return true;
    }
    bool updateNotepadContentHelper(notepad::Notepad &notepad, int startLine, int endLine)
    {
        string notepadId = notepad.id(), notepadName = notepad.name();

        // Create versions
        notepad::Versions versions;

        // Parse versions and read from the file
        if (!parseAndReadVersions(notepadName, versions))
        {
            return false;
        }

        int versionSize = versions.versions_size();

        // If the latest version changes reached the limit
        if (versionSize == 0 || versions.versions(versionSize - 1).changes_size() == versionChangesLimit)
        {
            // Create the next version
            notepad::Version *nextVersion = versions.add_versions();
            createVersion(versionSize, notepadId, nextVersion);
            if (!updateContentAndUpdateVersion(notepad, versions, nextVersion, startLine, endLine))
            {
                return false;
            }
        }
        else
        {
            notepad::Version *version = versions.mutable_versions(versions.versions_size() - 1);
            if (!updateContentAndUpdateVersion(notepad, versions, version, startLine, endLine))
            {
                return false;
            }
        }

        return true;
    }
    string getChangeName(notepad::ChangeName changeName)
    {
        if (changeName == notepad::ChangeName::ADD)
        {
            return "ADD";
        }
        if (changeName == notepad::ChangeName::REMOVE)
        {
            return "REMOVE";
        }
        return "UPDATE";
    }
    void revertAdd(notepad::Notepad &notepad, int startLine, int endLine)
    {
        // Remove notepad content from start to end line
        google::protobuf::RepeatedPtrField<notepad::Content> *contentRpf = notepad.mutable_contents();
        if (startLine == endLine)
        {
            contentRpf->DeleteSubrange(startLine, 1);
        }
        else
        {
            contentRpf->DeleteSubrange(startLine, endLine - startLine + 1);
        }
    }
    void revertRemove(notepad::Notepad &notepad, notepad::Change &change)
    {
        int startLine = change.start_line();

        // Create dummy change to hold notepad contents from start line
        notepad::Change dummyChange;

        // Copy the notepad content from start line before reverting remove
        for (int i = startLine; i < notepad.contents_size(); i++)
        {
            notepad::Content content = notepad.contents(i);
            notepad::Content *dummyChangeContent = dummyChange.add_contents();
            dummyChangeContent->set_line(content.line());
        }

        int notepadEndLine = notepad.contents_size() - 1;

        // Remove notepad content from start line
        google::protobuf::RepeatedPtrField<notepad::Content> *contentRpf = notepad.mutable_contents();
        if (startLine == notepadEndLine)
        {
            contentRpf->DeleteSubrange(startLine, 1);
        }
        else
        {
            contentRpf->DeleteSubrange(startLine, notepadEndLine - startLine + 1);
        }

        // Add change contents to notepad
        for (int i = 0; i < change.contents_size(); i++)
        {
            notepad::Content changeContent = change.contents(i);
            notepad::Content *content = notepad.add_contents();
            content->set_line(changeContent.line());
        }

        // Add remaining notepad content
        for (int i = 0; i < dummyChange.contents_size(); i++)
        {
            notepad::Content dummyChangeContent = dummyChange.contents(i);
            notepad::Content *content = notepad.add_contents();
            content->set_line(dummyChangeContent.line());
        }
    }
    void revertUpdate(notepad::Notepad &notepad, notepad::Change &change)
    {
        int startLine = change.start_line(), endLine = change.end_line();

        // Update notepad content from start to end line
        int currLine = startLine;
        for (int i = 0; i < change.contents_size(); i++)
        {
            notepad::Content changeContent = change.contents(i);
            notepad::Content *content = notepad.mutable_contents(currLine);
            content->set_line(changeContent.line());
            currLine++;
        }
    }
    void revertChange(notepad::Notepad &notepad, notepad::Change &change)
    {
        // Revert add
        if (change.name() == notepad::ChangeName::ADD)
        {
            revertAdd(notepad, change.start_line(), change.end_line());
        }

        // Revert remove
        else if (change.name() == notepad::ChangeName::REMOVE)
        {
            revertRemove(notepad, change);
        }

        // Revert update
        else
        {
            revertUpdate(notepad, change);
        }
    }

public:
    NotepadPortal(string &name)
    {
        userName = name;
        getExistingNotepadNames();
        getExistingVersionNames();
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
        cout << "7 - Display versions\n";
        cout << "8 - Revert version\n";
        cout << "9 - Logout\n";
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
        string id = "n" + to_string(notepadNames.size() + 1);

        // Create notepad
        notepad::Notepad notepad;
        notepad.set_id(id);
        notepad.set_name(name);
        notepad.set_user_name(userName);

        // Create versions
        notepad::Versions versions;

        // Serialize version and store it in a file
        if (!serializeAndStoreVersion(name, versions))
        {
            return false;
        }

        // Add notepad content from user
        if (!addNotepadContentHelper(notepad))
        {
            cout << "\nUnable to add notepad content\n";
            return false;
        }

        // Serialize notepad and store it in a file
        if (!serializeAndStoreNotepad(name, notepad))
        {
            return false;
        }

        cout << "\nNotepad created successfully\n";

        // Update notepad names
        notepadNames.push_back(name);

        // Update version names
        versionNames.push_back(name);

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
        if (!addNotepadContentHelper(notepad))
        {
            cout << "\nUnable to add notepad content\n";
            return false;
        }

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

        // Remove content from start to end line
        if (!removeNotepadContentHelper(notepad, startLine, endLine))
        {
            cout << "\nUnable to remove notepad content\n";
            return false;
        }

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
        if (!updateNotepadContentHelper(notepad, startLine, endLine))
        {
            cout << "\nUnable to update notepad content\n";
            return false;
        }

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
    bool displayVersions(string &name)
    {
        // Check if version exist
        if (!versionExist(name))
        {
            cout << "\nVersion does not exist with the given name\n";
            return false;
        }

        // Create versions
        notepad::Versions versions;

        // Parse versions and read from the file
        if (!parseAndReadVersions(name, versions))
        {
            return false;
        }

        // Display the versions
        for (int i = 0; i < versions.versions_size(); i++)
        {
            notepad::Version version = versions.versions(i);
            cout << "\nVersion number - " << version.number() << "\n";
            cout << "\nCreated time - " << version.created_time() << "\n";
            cout << "Notepad id - " << version.notepad_id() << "\n";
            cout << "\nChanges\n";
            for (int j = 0; j < version.changes_size(); j++)
            {
                notepad::Change change = version.changes(j);
                cout << "\nName - " << getChangeName(change.name()) << "\n";
                int startLine = change.start_line(), endLine = change.end_line();
                cout << "From - " << (startLine + 1) << " to " << (endLine + 1) << "\n";
                for (int k = 0; k < change.contents_size(); k++)
                {
                    notepad::Content content = change.contents(k);
                    cout << content.line() << "\n";
                }
            }
        }
        return true;
    }
    bool revertVersion(string &name, int versionNumber)
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

        // Check if version exist
        if (!versionExist(name))
        {
            cout << "\nVersion does not exist with the given name\n";
            return false;
        }

        // Create versions
        notepad::Versions versions;

        // Parse versions and read from the file
        if (!parseAndReadVersions(name, versions))
        {
            return false;
        }

        // Check if valid version number (0 based indexing)
        int n = versions.versions_size();
        versionNumber -= 1;
        if (versionNumber < 0 || versionNumber >= n - 1)
        {
            cout << "\nInvalid version number\n";
            return false;
        }

        // Get version repeated ptr field
        google::protobuf::RepeatedPtrField<notepad::Version> *versionRpf = versions.mutable_versions();

        // Traverse the versions
        for (int i = n - 1; i > versionNumber; i--)
        {
            notepad::Version *version = versions.mutable_versions(i);

            // Revert each change in the version
            for (int j = version->changes_size() - 1; j >= 0; j--)
            {
                notepad::Change change = version->changes(j);
                revertChange(notepad, change);
            }

            // Remove the version
            versionRpf->DeleteSubrange(i, 1);
        }

        // Serialize notepad and store it in a file
        if (!serializeAndStoreNotepad(name, notepad))
        {
            return false;
        }

        // Serialize versions and store it in a file
        if (!serializeAndStoreVersion(name, versions))
        {
            return false;
        }

        cout << "\nReverted to version " << (versionNumber + 1) << " successfully\n";
        return true;
    }
};