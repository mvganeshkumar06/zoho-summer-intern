#include <bits/stdc++.h>
#include "type.cpp"
#include "flight-ticket-booking.cpp"
using namespace std;

void printOptions()
{
    cout << "\nOptions\n";
    cout << "1 - List flights.\n";
    cout << "2 - Search flights based on location.\n";
    cout << "3 - Search flights based on business class.\n";
    cout << "4 - Print available seats in a flight.\n";
    cout << "5 - Book seats in a flight.\n";
    cout << "6 - Print seats with meal order.\n";
    cout << "7 - Print booking summary.\n";
    cout << "8 - Cancel seats in a flight.\n";
    cout << "9 - Exit.\n";
    cout << "\nChoose an option from above - ";
}

void split(string &line, char delimiter, vector<string> &tokens)
{
    stringstream ss(line);
    string token;
    while (getline(ss, token, delimiter))
    {
        tokens.push_back(token);
    }
}

bool getSeatNumbers(vector<pair<int, int>> &seatNumbers)
{
    vector<string> seatTokens, seatNumberTokens;
    string line;
    getline(cin >> ws, line);
    split(line, ' ', seatTokens);
    for (auto &seatToken : seatTokens)
    {
        size_t index = seatToken.find("_");
        if (index != string::npos)
        {
            int row = stoi(seatToken.substr(0, index)) - 1, column = tolower(*seatToken.substr(index + 1).c_str()) - 'a';
            seatNumbers.push_back({row, column});
            seatNumberTokens.clear();
        }
        else
        {
            cout << "\nInvalid seat number syntax\n";
            return false;
        }
    }
    return true;
}

pair<int, int> getFileContent(string &line, vector<int> &arrangement)
{
    vector<string> fileContentTokens;
    split(line, ' ', fileContentTokens);
    string type = fileContentTokens[0], arrangementContent = fileContentTokens[1];
    int row = stoi(fileContentTokens[2]);
    SeatType seatType;
    if (type == "Economy")
    {
        seatType = ECONOMY;
    }
    else
    {
        seatType = BUSINESS;
    }
    string arrangementConfig = arrangementContent.substr(1, arrangementContent.size() - 2);
    fileContentTokens.clear();
    split(arrangementConfig, ',', fileContentTokens);
    int column;
    for (const auto &content : fileContentTokens)
    {
        int num = stoi(content);
        arrangement.push_back(num);
        column += num;
    }
    return {row, column};
}

int main()
{
    FlightTicketBooking flightTicketBooking;
    // Traverse the files in the folder.
    string path = "./flight-details";
    for (const auto &file : filesystem::directory_iterator(path))
    {
        // Parse file name.
        string fileName = file.path().filename().string();
        int index = fileName.find(".txt");
        string rawFileName = fileName.substr(0, index);
        vector<string> fileNametokens;
        split(rawFileName, '-', fileNametokens);
        string id = fileNametokens[1], source = fileNametokens[2], destination = fileNametokens[3];

        // Read contents of file.
        ifstream fileDetails;
        fileDetails.open(path + "/" + fileName);
        string line;
        while (getline(fileDetails, line))
        {
            vector<int> economyArrangement, businessArrangement;
            pair<int, int> economyPair = getFileContent(line, economyArrangement);
            getline(fileDetails, line);
            pair<int, int> businessPair = getFileContent(line, businessArrangement);
            Flight flight(id, source, destination, 1000, economyPair.first, economyPair.second, economyArrangement, 2000, businessPair.first, businessPair.second, businessArrangement);
            flightTicketBooking.getFlights().push_back(flight);
        }
    }

    while (true)
    {
        printOptions();
        int choice;
        cin >> choice;
        switch (choice)
        {
        // List flights.
        case 1:
        {
            flightTicketBooking.listFlights();
            break;
        }
        // Search flights based on location.
        case 2:
        {
            cout << "\nEnter the source and destination - ";
            string source, destination;
            cin >> source >> destination;
            flightTicketBooking.search(source, destination);
            break;
        }
        // Search flights based on business class.
        case 3:
        {
            flightTicketBooking.search();
            break;
        }
        // Print available seats in a flight.
        case 4:
        {
            cout << "\nEnter flight Id - ";
            string id;
            cin >> id;
            flightTicketBooking.printAvailableSeats(id);
            break;
        }
        // Book seats in a flight.
        case 5:
        {
            cout << "\nEnter passenger name, flight Id, seat type (E for Economy and B for business) - ";
            string passengerName, flightId;
            char type;
            cin >> passengerName >> flightId >> type;
            SeatType seatType;
            if (type == 'E')
            {
                seatType = ECONOMY;
            }
            else if (type == 'B')
            {
                seatType = BUSINESS;
            }
            else
            {
                cout << "\nInvalid seat type\n";
                break;
            }
            cout << "\nEnter the seat numbers - ";
            vector<pair<int, int>> seatNumbers;
            if (getSeatNumbers(seatNumbers))
            {
                flightTicketBooking.bookSeat(passengerName, flightId, seatType, seatNumbers);
            }
            else
            {
                cout << "\nUnable to book seat\n";
            }
            break;
        }
        // Print seats with meal order.
        case 6:
        {
            cout << "\nEnter flight Id - ";
            string id;
            cin >> id;
            flightTicketBooking.printSeatsWithMeal(id);
            break;
        }
        // Print booking summary.
        case 7:
        {
            cout << "\nEnter booking Id - ";
            string bookingId;
            cin >> bookingId;
            flightTicketBooking.printBookingSummary(bookingId);
            break;
        }
        // Cancel seats in a flight.
        case 8:
        {
            cout << "\nEnter booking id - ";
            string bookingId;
            cin >> bookingId;
            cout << "\nEnter the seat numbers - ";
            vector<pair<int, int>> seatNumbers;
            getSeatNumbers(seatNumbers);
            flightTicketBooking.cancelSeat(bookingId, seatNumbers);
            break;
        }
        // Exit.
        case 9:
        {
            return 0;
            break;
        }
        default:
        {
            cout << "\nChoose a correct option\n";
            break;
        }
        }
    }
    return 0;
}