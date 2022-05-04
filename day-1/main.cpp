#include <iostream>
using namespace std;

enum vehicleType
{
    PETROL,
    DIESEL,
    EV
};

class Vehicle
{
public:
    vehicleType vType;
    string brand;
    string model;
    string color;
    double mileage;
    double price;
    int numOfWheels;
    Vehicle(vehicleType type, string brand, string model, string color, double mileage, double price)
    {
        this->vType = type;
        this->brand = brand;
        this->model = model;
        this->color = color;
        this->mileage = mileage;
        this->price = price;
    }
    virtual int getNumOfWheels() = 0;
    friend ostream &operator<<(ostream &outStream, const Vehicle &vehicle)
    {
        outStream << "Brand - " << vehicle.brand << "\n";
        outStream << "Model - " << vehicle.model << "\n";
        outStream << "Type - " << vehicle.vType << "\n";
        outStream << "Color - " << vehicle.color << "\n";
        outStream << "Price - " << vehicle.price << "\n";
        return outStream;
    }
    bool operator<(const Vehicle &vehicle)
    {
        return price < vehicle.price;
    }
    bool operator>(const Vehicle &vehicle)
    {
        return price > vehicle.price;
    }
};

enum carType
{
    SUV,
    SEDAN
};

class Car : public Vehicle
{
public:
    carType cType;
    int numOfPersons;
    Car(vehicleType vType, string brand, string model, string color, double mileage, double price, int numOfPersons, carType cType, int numOfWheels) : Vehicle(vType, brand, model, color, mileage, price)
    {
        this->numOfPersons = numOfPersons;
        this->cType = cType;
        this->numOfWheels = numOfWheels;
    }
    int getNumOfWheels()
    {
        return numOfWheels;
    }
};

enum bikeType
{
    SCOOTER,
    MOTORBIKE,
};

class Bike : public Vehicle
{
public:
    bikeType bType;
    double weight;
    Bike(vehicleType vType, string brand, string model, string color, double mileage, double price, double weight, bikeType bType, int numOfWheels) : Vehicle(vType, brand, model, color, mileage, price)
    {
        this->weight = weight;
        this->bType = bType;
        this->numOfWheels = numOfWheels;
    }
    int getNumOfWheels()
    {
        return numOfWheels;
    }
};

int main()
{
    Car c1(PETROL, "Maruthi", "M123", "Black", 40, 980000, 2, SUV, 4);
    Bike b1(EV, "Honda", "H123", "Blue", 50, 80000, 65, MOTORBIKE, 2);
    cout << "Number of wheels for car - " << c1.getNumOfWheels() << "\n";
    cout << "Number of wheels for bike - " << b1.getNumOfWheels() << "\n";
    cout << "Car price is less - " << (c1 < b1) << "\n";
    cout << "Car price is more - " << (c1 > b1) << "\n";
    cout << "Car information \n"
         << c1;
    cout << "Bike information \n"
         << b1;
    return 0;
}