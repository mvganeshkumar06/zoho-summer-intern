#include <bits/stdc++.h>
#include "seat.cpp"
using namespace std;

class Flight
{
    string id;
    string source;
    string destination;
    Seat economy;
    Seat business;

public:
    Flight(string id, string source, string destination, int economyBasePrice, int economyRow, int economyColumn, vector<int> &economyArrangement, int businessBasePrice, int businessRow, int businessColumn, vector<int> &businessArrangement)
    {
        this->id = id;
        this->source = source;
        this->destination = destination;
        this->economy = Seat(ECONOMY, economyBasePrice, economyRow, economyColumn, economyArrangement);
        this->business = Seat(BUSINESS, businessBasePrice, businessRow, businessColumn, businessArrangement);
    }
    string getId()
    {
        return id;
    }
    string getSource()
    {
        return source;
    }
    string getDestination()
    {
        return destination;
    }
    Seat &getEconomy()
    {
        return economy;
    }
    Seat &getBusiness()
    {
        return business;
    }
    bool isAvailable(string &source, string &destination)
    {
        return (this->source == source) && (this->destination == destination);
    }
    bool isBusinessClassAloneAvailable()
    {
        return (economy.getSize() == 0) && (business.getSize() > 0);
    }
    void printAvailableSeats()
    {
        cout << "\nThe available economy seats are - \n";
        economy.printAvailableSeats();
        cout << "\nThe available business seats are - \n";
        business.printAvailableSeats();
    }
    void printSeatsWithMeal()
    {
        cout << "\nThe economy seats with meal booking are - \n";
        economy.printSeatsWithMeal();
        cout << "\nThe business seats with meal booking are - \n";
        business.printSeatsWithMeal();
    }
    bool bookSeat(SeatType &seatType, int row, int column)
    {
        if (seatType == ECONOMY)
        {
            if (economy.isValidSeatParams(row, column))
            {
                if (!economy.isSeatFilled(row, column))
                {
                    economy.fillSeat(row, column);
                    return true;
                }
                cout << "\nSeat already booked\n";
                return false;
            }
            cout << "\nInvalid seat number\n";
            return false;
        }
        if (business.isValidSeatParams(row, column))
        {
            if (!business.isSeatFilled(row, column))
            {
                business.fillSeat(row, column);
                return true;
            }
            cout << "\nSeat already booked\n";
            return false;
        }
        cout << "\nInvalid seat number\n";
        return false;
    }
    bool cancelSeat(SeatType &seatType, int row, int column)
    {
        if (seatType == ECONOMY)
        {
            if (economy.isValidSeatParams(row, column))
            {
                if (economy.isSeatFilled(row, column))
                {
                    economy.emptySeat(row, column);
                    return true;
                }
                cout << "\nSeat not yet booked\n";
                return false;
            }
            cout << "\nInvalid seat number\n";
            return false;
        }
        if (business.isValidSeatParams(row, column))
        {
            if (business.isSeatFilled(row, column))
            {
                business.emptySeat(row, column);
                return true;
            }
            cout << "\nSeat not yet booked\n";
            return false;
        }
        cout << "\nInvalid seat number\n";
        return false;
    }
    void printDetails()
    {
        cout << "\nFlight\n";
        cout << "ID - " << id << "\n";
        cout << "Source - " << source << "\n";
        cout << "Destination - " << destination << "\n\n";
    }
};
