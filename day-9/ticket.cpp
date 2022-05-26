#include <bits/stdc++.h>
using namespace std;

class Ticket
{
    string id;
    string flightId;
    SeatType seatType;
    int row;
    int column;
    ArrangementType arrangementType;
    bool isMealPreferred;
    int price;
    string getSeatNumber(int row, int column)
    {
        return to_string(row + 1) + "_" + char('A' + column);
    }

public:
    Ticket(string id, string flightId, SeatType seatType, int row, int column, ArrangementType arrangementType, int price) : id(id), flightId(flightId), seatType(seatType), row(row), column(column), arrangementType(arrangementType), price(price), isMealPreferred(false) {}
    SeatType getSeatType()
    {
        return seatType;
    }
    int getRow()
    {
        return row;
    }
    int getColumn()
    {
        return column;
    }
    bool getIsMealPreferred()
    {
        return isMealPreferred;
    }
    void setIsMealPreferred(bool isMealPreferred)
    {
        this->isMealPreferred = isMealPreferred;
    }
    int getPrice()
    {
        return price;
    }
    void setPrice(int price)
    {
        this->price = price;
    }
    void printSummary()
    {
        cout << "Ticket Id - " << id << "\n";
        cout << "Seat number - " << getSeatNumber(row, column) << "\n";
        cout << "Arrangement type - ";
        if (arrangementType == WINDOW)
        {
            cout << "Window\n";
        }
        else if (arrangementType == MIDDLE)
        {
            cout << "Middle\n";
        }
        else
        {
            cout << "Aisle\n";
        }
        cout << "Price - " << price << "\n";
        cout << "Is meal preferred - " << (isMealPreferred == 1 ? "Yes" : "No") << "\n\n";
    }
};