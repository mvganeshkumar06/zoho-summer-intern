#include <bits/stdc++.h>
using namespace std;

class Rectangle
{
public:
    int *left, *top, *width, *height, *area;
    Rectangle() : left(new int(0)), top(new int(0)), width(new int(0)), height(new int(0)) {}
    Rectangle(int width, int height) : left(new int(0)), top(new int(0)), width(new int(width)), height(new int(height)) {}
    Rectangle(int left, int top, int width, int height) : left(new int(left)), top(new int(top)), width(new int(width)), height(new int(height)) {}
    Rectangle(float left, float top, float width, float height) : left(new int(round(left))), top(new int(round(top))), width(new int(round(width))), height(new int(round(height))) {}
    Rectangle(Rectangle &rectangle)
    {
        left = rectangle.left;
        top = rectangle.top;
        width = rectangle.width;
        height = rectangle.height;
        rectangle.area = new int((*width) * (*height));
        area = rectangle.area;
    }
    ~Rectangle()
    {
        delete left, top, width, height, area;
    }
    void print()
    {
        cout << "\nRectangle Values\n";
        cout << "Left - " << *left << "\n";
        cout << "Top - " << *top << "\n";
        cout << "Width - " << *width << "\n";
        cout << "Height - " << *height << "\n";
        cout << "Area - " << *area << "\n\n";
    }
};

int main()
{
    Rectangle r1, r2(50, 25), r3(r2), r4(10, 20, 30, 40), r5(r4), r6(float(5.2), float(5.7), float(20.23), float(25.67)), r7(r6);
    r1.print();
    r2.print();
    r3.print();
    r4.print();
    r5.print();
    r6.print();
    r7.print();
    return 0;
}