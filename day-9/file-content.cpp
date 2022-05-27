#include <bits/stdc++.h>
using namespace std;

class FileContent
{
    SeatType seatType;
    vector<int> arrangement;
    int row;
    int column;

public:
    FileContent() {}
    SeatType getSeatType()
    {
        return seatType;
    }
    void setSeatType(SeatType &seatType)
    {
        this->seatType = seatType;
    }
    vector<int> &getArrangement()
    {
        return arrangement;
    }
    void setArrangement(vector<int> &arrangement)
    {
        this->arrangement = arrangement;
    }
    int getRow()
    {
        return row;
    }
    void setRow(int row)
    {
        this->row = row;
    }
    int getColumn()
    {
        return column;
    }
    void setColumn(int column)
    {
        this->column = column;
    }
};