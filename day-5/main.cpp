#include <bits/stdc++.h>
using namespace std;

namespace point
{
    class Point
    {
    public:
        int x, y;
        Point(int x, int y) : x(x), y(y) {}
        void print()
        {
            cout << "\nPoint\n";
            cout << "x - " << x << "\n";
            cout << "y - " << y << "\n\n";
        }
    };
}

namespace shape
{
    namespace rectangle
    {
        double width, height;
        void setParams(double width, double height)
        {
            rectangle::width = width;
            rectangle::height = height;
        }
        void printArea()
        {
            cout << "Area of rectangle - " << width * height << "\n\n";
        }
    }
    inline namespace info
    {
        string name;
        void setName(string name)
        {
            info::name = name;
        }
        void printName()
        {
            cout << "Shape name - " << name << "\n\n";
        }
    }
}

int main()
{

    point::Point p(10, 15);
    p.print();

    namespace rectangle = shape::rectangle;

    rectangle::setParams(15, 20);
    rectangle::printArea();

    shape::setName("Shape 1");
    shape::printName();

    return 0;
}