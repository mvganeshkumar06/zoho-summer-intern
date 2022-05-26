#include <bits/stdc++.h>
using namespace std;

class Seat
{
    SeatType seatType;
    int totalPrice;
    vector<vector<char>> seats;
    vector<vector<bool>> seatsFilled;
    vector<vector<bool>> seatsWithMeal;
    void updateAisleSet(vector<int> &arrangement, unordered_set<int> &aisleSet)
    {
        int sum = 0;
        for (int i = 0; i < arrangement.size() - 1; i++)
        {
            sum += arrangement[i];
            aisleSet.insert(sum);
            aisleSet.insert(sum - 1);
        }
    }
    void updateSeats(int row, int column, unordered_set<int> &aisleSet)
    {
        for (int i = 0; i < row; i++)
        {
            vector<char> seatRow;
            vector<bool> seatFillRow, seatWithMealRow;
            for (int j = 0; j < column; j++)
            {
                if (j == 0 || j == column - 1)
                {
                    seatRow.push_back('W');
                }
                else if (aisleSet.find(j) != aisleSet.end())
                {
                    seatRow.push_back('A');
                }
                else
                {
                    seatRow.push_back('M');
                }
                seatFillRow.push_back(false);
                seatWithMealRow.push_back(false);
            }
            seats.push_back(seatRow);
            seatsFilled.push_back(seatFillRow);
            seatsWithMeal.push_back(seatWithMealRow);
        }
    }
    string getSeatNumber(int row, int column)
    {
        return to_string(row + 1) + "_" + char('A' + column);
    }

public:
    Seat() {}
    Seat(SeatType seatType, int basePrice, int row, int column, vector<int> &arrangement)
    {
        this->seatType = seatType;
        this->totalPrice = basePrice;
        unordered_set<int> aisleSet;
        updateAisleSet(arrangement, aisleSet);
        updateSeats(row, column, aisleSet);
    }
    SeatType getSeatType()
    {
        return seatType;
    }
    void setSeats(vector<vector<char>> &seats)
    {
        this->seats = seats;
    }
    void setSeatsFilled(vector<vector<bool>> &seatsFilled)
    {
        this->seatsFilled = seatsFilled;
    }
    void setSeatsWithMeal(vector<vector<bool>> &seatsWithMeal)
    {
        this->seatsWithMeal = seatsWithMeal;
    }
    int getSize()
    {
        return seats.size();
    }
    bool isValidSeatParams(int row, int column)
    {
        return row >= 0 && row < seats.size() && column >= 0 && column < seats[row].size();
    }
    bool isSeatFilled(int row, int column)
    {
        return seatsFilled[row][column];
    }
    void fillSeat(int row, int column)
    {
        seatsFilled[row][column] = true;
    }
    void emptySeat(int row, int column)
    {
        seatsFilled[row][column] = false;
    }
    bool isSeatWithMeal(int row, int column)
    {
        return seatsWithMeal[row][column];
    }
    void fillMealForSeat(int row, int column)
    {
        seatsWithMeal[row][column] = true;
    }
    void emptyMealForSeat(int row, int column)
    {
        seatsWithMeal[row][column] = false;
    }
    ArrangementType getArrangementType(int row, int column)
    {
        char arrangement = seats[row][column];
        if (arrangement == 'W')
        {
            return WINDOW;
        }
        if (arrangement == 'M')
        {
            return MIDDLE;
        }
        return AISLE;
    }
    void printAvailableSeats()
    {
        for (int i = 0; i < seats.size(); i++)
        {
            for (int j = 0; j < seats[i].size(); j++)
            {
                if (!isSeatFilled(i, j))
                {
                    cout << getSeatNumber(i, j) << " ";
                }
                else
                {
                    cout << "-_- ";
                }
            }
            cout << "\n";
        }
    }
    void printSeatsWithMeal()
    {
        for (int i = 0; i < seats.size(); i++)
        {
            for (int j = 0; j < seats[i].size(); j++)
            {
                if (isSeatWithMeal(i, j))
                {
                    cout << getSeatNumber(i, j) << " ";
                }
                else
                {
                    cout << "-_- ";
                }
            }
            cout << "\n";
        }
    }
    int getTotalPrice()
    {
        return totalPrice;
    }
    void surgePrice(SeatType &seatType)
    {
        if (seatType == ECONOMY)
        {
            totalPrice += 100;
        }
        else
        {
            totalPrice += 200;
        }
    }
};