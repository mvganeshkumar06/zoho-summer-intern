#include <bits/stdc++.h>
using namespace std;

class AgeNotWithinRangeException : public exception
{
    const char *what() const throw()
    {
        return "Age is not within the range";
    }
};

class NameNotValidException : public exception
{
    const char *what() const throw()
    {
        return "Name is not valid, it should not contain any special characters";
    }
};

class InvalidCouseException : public exception
{
    const char *what() const throw()
    {
        return "Course is not valid";
    }
};

class StudentLimitExceededException : public exception
{
    const char *what() const throw()
    {
        return "Can not create more than one student object";
    }
};

class Student
{
public:
    int rollNo, age;
    string name, course;
    static int studentCount;

    Student(int rollNo, string name, int age, string course)
    {
        try
        {
            if (studentCount >= 1)
            {
                throw StudentLimitExceededException();
            }

            this->rollNo = rollNo;

            for (const char &ch : name)
            {
                bool isAlphabet = (ch >= 97 && ch <= 122) || (ch >= 65 && ch <= 90);
                if (!isAlphabet)
                {
                    throw NameNotValidException();
                }
            }
            this->name = name;

            if (age < 15 or age > 21)
            {
                throw AgeNotWithinRangeException();
            }
            this->age = age;

            string courseList[] = {"abc", "def", "ghi"};
            bool isCourseFound = false;
            for (const string &currCourse : courseList)
            {
                if (course == currCourse)
                {
                    isCourseFound = true;
                    break;
                }
            }
            if (!isCourseFound)
            {
                throw InvalidCouseException();
            }

            studentCount += 1;
        }
        catch (const exception &e)
        {
            cout << "\n"
                 << e.what() << "\n";
        }
    }
};

int Student::studentCount = 0;

int main()
{
    Student s(1, "john", 20, "ghi");
    cout << "Student count - " << Student::studentCount << "\n";
    return 0;
}