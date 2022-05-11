#include <bits/stdc++.h>
#include <exception>
using namespace std;

class MyException : public exception
{
    const char *message;
    string param;

public:
    MyException(const char *message, string param) : message(message), param(param) {}

    const char *what() const throw()
    {
        cout << "\nMyException [ " << param << " ]\n";
        return message;
    }
};

int main()
{
    try
    {

        int a, b;
        cout << "Enter two elements - ";
        cin >> a >> b;
        double res;
        if (b == 0)
        {
            throw MyException("\nInvalid division", "Division by zero");
        }
        res = a / b;
        cout << "\nDivision result - " << res << "\n\n";

        long size = 0x8fffffff;
        char *ptr = new char[size];

        string str;
        cout << "Enter a number - ";
        cin >> str;
        int num = stoi(str);
        cout << "Number - " << num << "\n";

        string s2;
        cout << "Enter a string - ";
        cin >> s2;
        int sLen = s2.length(), sIndex;
        cout << "Enter an index to access the string - ";
        cin >> sIndex;
        if (sIndex < 0 or sIndex >= sLen)
        {
            throw MyException("\nString index is invalid", "Index out of range");
        }
        cout << "String value - " << s2[sIndex] << "\n";

        int arrLen;
        cout << "Enter the size for array - ";
        cin >> arrLen;
        int arr[arrLen];
        cout << "Enter an array of integers - ";
        for (int i = 0; i < arrLen; i++)
        {
            cin >> arr[i];
        }
        int arrIndex;
        cout << "Enter an index to access the array - ";
        cin >> arrIndex;
        if (arrIndex < 0 or arrIndex >= arrLen)
        {
            throw MyException("\nArray index is invalid", "Index out of range");
        }
        cout << "Array value - " << arr[arrIndex] << "\n";

        int n;
        cout << "Enter an integer to compute sum of first n natural numbers - ";
        cin >> n;
        if (n < 0)
        {
            throw "Natural number can not negative";
        }
        int sum = 0;
        for (int i = 1; i <= n; i++)
        {
            sum += i;
        }
        cout << "Sum - " << sum << "\n";
    }
    catch (const exception &e)
    {
        cout << "\n"
             << e.what() << "\n";
    }
    catch (...)
    {
        cout << "\nException occurred\n";
    }
    cout << "\nException Handling Accomplished\n\n";
    return 0;
}