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
    bool isEconomyAvailable;
    bool isBusinessAvailable;

    Flight(string id, string source, string destination) : id(id), source(source), destination(destination), isEconomyAvailable(false), isBusinessAvailable(false) {}
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
    void setEconomy(int price, int row, int column, vector<int> &arrangement)
    {
        this->economy = Seat(ECONOMY, price, row, column, arrangement);
        isEconomyAvailable = true;
    }
    Seat &getBusiness()
    {
        return business;
    }
    void setBusiness(int price, int row, int column, vector<int> &arrangement)
    {
        this->business = Seat(BUSINESS, price, row, column, arrangement);
        isBusinessAvailable = true;
    }
    bool isAvailable(string &source, string &destination)
    {
        return (this->source == source) && (this->destination == destination);
    }
    bool isBusinessClassAloneAvailable()
    {
        return !isEconomyAvailable && isBusinessAvailable;
    }
    void printAvailableSeats()
    {
        if (isEconomyAvailable)
        {
            cout << "\nThe available economy seats are - \n";
            economy.printAvailableSeats();
        }
        if (isBusinessAvailable)
        {
            cout << "\nThe available business seats are - \n";
            business.printAvailableSeats();
        }
    }
    void printSeatsWithMeal()
    {
        if (isEconomyAvailable)
        {
            cout << "\nThe economy seats with meal booking are - \n";
            economy.printSeatsWithMeal();
        }
        if (isBusinessAvailable)
        {
            cout << "\nThe business seats with meal booking are - \n";
            business.printSeatsWithMeal();
        }
    }
    bool bookSeat(SeatType &seatType, int row, int column)
    {
        if (seatType == ECONOMY)
        {
            if (isEconomyAvailable)
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
            cout << "\nEconomy seats are not available\n";
            return false;
        }
        else if (seatType == BUSINESS)
        {
            if (isBusinessAvailable)
            {
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
            cout << "\nBusiness seats are not available\n";
            return false;
        }
        cout << "\nInvalid seat type\n";
        return false;
    }
    bool cancelSeat(SeatType &seatType, int row, int column)
    {
        if (seatType == ECONOMY)
        {
            if (isEconomyAvailable)
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
            cout << "\nEconomy seats are not available\n";
            return false;
        }
        else if (seatType == BUSINESS)
        {
            if (isBusinessAvailable)
            {
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
            cout << "\nBusiness seats are not available\n";
            return false;
        }
        cout << "\nInvalid seat type\n";
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
