#include <bits/stdc++.h>
#include "flight.cpp"
#include "booking.cpp"
using namespace std;

class FlightTicketBooking
{
    vector<Flight> flights;
    vector<Booking> bookings;
    Flight *getFlight(string flightId)
    {
        for (auto &flight : flights)
        {
            if (flight.getId() == flightId)
            {
                return &flight;
            }
        }
        return NULL;
    }
    void bookMeal(Flight *flight, Booking &booking)
    {
        for (auto &ticket : booking.getTickets())
        {
            if (ticket.getSeatType() == ECONOMY)
            {
                flight->getEconomy().fillMealForSeat(ticket.getRow(), ticket.getColumn());
            }
            else
            {
                flight->getBusiness().fillMealForSeat(ticket.getRow(), ticket.getColumn());
            }
            ticket.setIsMealPreferred(true);
            ticket.setPrice(ticket.getPrice() + 200);
        }
        int mealBookingPrice = 200 * booking.getTickets().size();
        booking.setTotalPrice(booking.getTotalPrice() + mealBookingPrice);
        cout << "\nMeal booking price " << mealBookingPrice << " is applied to the booking\n";
    }
    Booking *getBooking(string &id)
    {
        for (auto &booking : bookings)
        {
            if (booking.getId() == id)
            {
                return &booking;
            }
        }
        return NULL;
    }
    bool removeTickets(Flight *flight, SeatType seatType, vector<Ticket> &bookedTickets, vector<pair<int, int>> &seatNumbers)
    {
        for (const auto &seatNumber : seatNumbers)
        {
            int row = seatNumber.first, col = seatNumber.second;
            bool isSeatFound = false;
            vector<Ticket>::iterator ticketIterator;
            for (auto ticket = bookedTickets.begin(); ticket != bookedTickets.end(); ticket++)
            {
                if (row == ticket->getRow() && col == ticket->getColumn())
                {
                    isSeatFound = true;
                    ticketIterator = ticket;
                    break;
                }
            }
            if (isSeatFound)
            {
                if (seatType == ECONOMY)
                {
                    flight->getEconomy().emptySeat(row, col);
                    flight->getEconomy().emptyMealForSeat(row, col);
                }
                else
                {
                    flight->getBusiness().emptySeat(row, col);
                    flight->getBusiness().emptyMealForSeat(row, col);
                }
                bookedTickets.erase(ticketIterator);
            }
            else
            {
                return false;
            }
        }
        return true;
    }
    void removeBooking(string &id)
    {
        vector<Booking>::iterator bookingIterator;
        for (auto booking = bookings.begin(); booking != bookings.end(); booking++)
        {
            if (booking->getId() == id)
            {
                bookingIterator = booking;
            }
        }
        bookings.erase(bookingIterator);
    }

public:
    vector<Flight> &getFlights()
    {
        return flights;
    }
    // List the flights details.
    void listFlights()
    {
        cout << "\nNumber of flights available - " << flights.size() << "\n";
        for (auto &flight : flights)
        {
            cout << "Flight Id - " << flight.getId() << "\n";
            cout << "Flight Name - " << flight.getSource() << "-" << flight.getDestination() << "\n";
        }
    }
    // Print the details of all the flights from the given source and destination.
    void search(string &source, string &destination)
    {
        bool flightExist = false;
        for (auto &flight : flights)
        {
            if (flight.isAvailable(source, destination))
            {
                flightExist = true;
                flight.printDetails();
            }
        }
        if (!flightExist)
        {
            cout << "\nNo flights exist from the given source and destination\n";
        }
    }
    // Print the details of all the flights which has only business class alone.
    void search()
    {
        bool flightExist = false;
        for (auto &flight : flights)
        {
            if (flight.isBusinessClassAloneAvailable())
            {
                flightExist = true;
                flight.printDetails();
            }
        }
        if (!flightExist)
        {
            cout << "\nNo flights contain only business class alone\n";
        }
    }
    void printAvailableSeats(string flightId)
    {
        Flight *flight = getFlight(flightId);
        if (flight != NULL)
        {
            flight->printAvailableSeats();
        }
        else
        {
            cout << "\nInvalid flight Id\n";
        }
    }
    void printSeatsWithMeal(string &flightId)
    {
        Flight *flight = getFlight(flightId);
        if (flight != NULL)
        {
            flight->printSeatsWithMeal();
        }
        else
        {
            cout << "\nInvalid flight Id\n";
        }
    }
    void bookSeat(string &passengerName, string &flightId, SeatType &seatType, vector<pair<int, int>> &seatNumbers)
    {
        Flight *flight = getFlight(flightId);
        if (flight != NULL)
        {
            string bookingId = flight->getId() + "-B" + to_string(bookings.size() + 1);
            Booking booking(bookingId, passengerName, flightId, seatType);
            bool allTicketsBooked = true;
            int bookingPrice = 0;
            for (const auto &seatNumber : seatNumbers)
            {
                int row = seatNumber.first, col = seatNumber.second;
                if (flight->bookSeat(seatType, row, col))
                {
                    string id = bookingId + "-T" + to_string(booking.getTickets().size() + 1);
                    ArrangementType arrangementType;
                    int ticketPrice = 0;
                    if (seatType == ECONOMY)
                    {
                        arrangementType = flight->getEconomy().getArrangementType(row, col);
                        ticketPrice = flight->getEconomy().getTotalPrice();
                    }
                    else
                    {
                        arrangementType = flight->getBusiness().getArrangementType(row, col);
                        ticketPrice = flight->getBusiness().getTotalPrice();
                    }
                    if (arrangementType == AISLE || arrangementType == WINDOW)
                    {
                        ticketPrice += 100;
                    }
                    Ticket ticket(id, flightId, seatType, row, col, arrangementType, ticketPrice);
                    booking.getTickets().push_back(ticket);
                    bookingPrice += ticketPrice;
                }
                else
                {
                    allTicketsBooked = false;
                    break;
                }
            }
            booking.setTotalPrice(bookingPrice);
            // Update bookings only after all tickets are booked.
            if (allTicketsBooked)
            {
                cout << "\nBooking successfull, all tickets are booked\n";
                // Surge price after each successfull booking.
                if (seatType == ECONOMY)
                {
                    flight->getEconomy().surgePrice(seatType);
                }
                else
                {
                    flight->getBusiness().surgePrice(seatType);
                }
                // Option to book meal after booking tickets.
                cout << "\nDo you want to book meal along with the tickets [y/n] - ";
                char option;
                cin >> option;
                if (option == 'y')
                {
                    bookMeal(flight, booking);
                }
                bookings.push_back(booking);
                booking.printSummary();
            }
            // Cancel booked tickets as some tickets were not able to book
            else
            {
                bookings.push_back(booking);
                cancelSeat(bookingId, seatNumbers);
                cout << "\nBooking cancelled as some tickets were not able to book\n";
            }
        }
        else
        {
            cout << "\nInvalid flight Id\n";
        }
    }
    void cancelSeat(string &bookingId, vector<pair<int, int>> &seatNumbers)
    {
        Booking *booking = getBooking(bookingId);
        if (booking != NULL)
        {
            Flight *flight = getFlight(booking->getFlightId());
            int cancellationPrice = 200 * seatNumbers.size();
            if (removeTickets(flight, booking->getSeatType(), booking->getTickets(), seatNumbers))
            {
                cout << "\nCancellation successfull, all the given tickets are cancelled\n";
                if (booking->getTickets().size() == 0)
                {
                    cout << "\nPlease pay the cancellation price - " << cancellationPrice << "\n";
                    removeBooking(bookingId);
                }
                else
                {
                    int remainingTicketsPrice = 0;
                    for (auto &ticket : booking->getTickets())
                    {
                        remainingTicketsPrice += ticket.getPrice();
                    }
                    int removedTicketsPrice = booking->getTotalPrice() - remainingTicketsPrice;
                    booking->setTotalPrice((booking->getTotalPrice() - removedTicketsPrice) + cancellationPrice);
                    cout << "\nCancellation price " << cancellationPrice << " is applied to the booking\n";
                    booking->printSummary();
                }
            }
            else
            {
                cout << "\nInvalid seat numbers\n";
            }
        }
        else
        {
            cout << "\nInvalid booking Id\n";
        }
    }
    void printBookingSummary(string &bookingId)
    {
        Booking *booking = getBooking(bookingId);
        if (booking != NULL)
        {
            booking->printSummary();
        }
        else
        {
            cout << "\nInvalid booking Id\n";
        }
    }
};