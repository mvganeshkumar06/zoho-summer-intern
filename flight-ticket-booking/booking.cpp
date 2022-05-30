#include <bits/stdc++.h>
#include "ticket.cpp"
using namespace std;

class Booking
{
    string id;
    string passengerName;
    string flightId;
    SeatType seatType;
    vector<Ticket> tickets;
    int totalPrice;

public:
    Booking(string id, string passengerName, string flightId, SeatType seatType) : id(id), passengerName(passengerName), flightId(flightId), seatType(seatType) {}
    string getId()
    {
        return id;
    }
    string getFlightId()
    {
        return flightId;
    }
    SeatType getSeatType()
    {
        return seatType;
    }
    vector<Ticket> &getTickets()
    {
        return tickets;
    }
    int getTotalPrice()
    {
        return totalPrice;
    }
    void setTotalPrice(int totalPrice)
    {
        this->totalPrice = totalPrice;
    }
    void printSummary()
    {
        cout << "\nBooking summary\n\n";
        cout << "Booking Id - " << id << "\n";
        cout << "Passenger name - " << passengerName << "\n";
        cout << "Flight Id - " << flightId << "\n";
        cout << "Seat type - " << (seatType == ECONOMY ? "Economy" : "Business") << "\n";
        cout << "Total price - " << totalPrice << "\n";
        cout << "\nTicket summary\n\n";
        for (auto &ticket : tickets)
        {
            ticket.printSummary();
        }
    }
};