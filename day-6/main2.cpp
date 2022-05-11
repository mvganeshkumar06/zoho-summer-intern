#include <bits/stdc++.h>
using namespace std;

int main()
{
    bool outerTryError = false, innerTryError = false;
    try
    {
        int a, b;
        cout << "Enter two elements - ";
        cin >> a >> b;
        double res;
        if (b == 0)
        {
            throw "\nInvalid division";
        }
        res = a / b;
        cout << "\nDivision result - " << res << "\n\n";
        try
        {

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
                throw "\nIndex out of range";
            }
            cout << "Array value - " << arr[arrIndex] << "\n";
        }
        catch (const char *e)
        {
            innerTryError = true;
            cout << e << "\n";
            throw; // rethrowing the exception
        }
        if (!innerTryError)
        {
            cout << "\nNo exception occurred in inner try block\n";
        }
    }
    catch (const char *e)
    {
        outerTryError = true;
        cout << e << "\n";
    }
    if (!outerTryError)
    {
        cout << "\nNo exception occurred in outer try block\n";
    }
    return 0;
}