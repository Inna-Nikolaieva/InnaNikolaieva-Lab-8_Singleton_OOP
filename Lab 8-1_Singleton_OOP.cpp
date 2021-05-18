/* Патерн «Одинак»
Перевантажити операції >= (порівняння дат за абсолютним значенням різниці у днях від поточної дати), 
-- (зменшення на 1 день), відсортувати масив екземплярів класу дат за спаданням абсолютного значення 
різниці від поточної дати з використанням алгоритму сортування вставками, зменшити кожну дату в масиві
на задану кількість днів, перевірити, чи дати у масиві далі будуть впорядковані.*/

#include <iostream>

using namespace std;

class Date {           
private:
    static Date* singleObject;  
    int day;
    int month;
    int year;
protected:
    Date(int d, int m, int y) { day = d; month = m; year = y; }       
public:         

    static Date* Instance(int d, int m, int y)
    {
        if (singleObject == nullptr) 
        {
            singleObject = new Date(d,m,y);
        }
        return singleObject;
    }
    
    int SetDate(int d, int m, int y)        
    {
        if ((d < 1 || d > 31) || (m < 1 || m > 12))
        {
            cout << "Incorrectly entered date!!!" << endl;
            system("pause");
            return 0;
        }
        else
            day = d; month = m; year = y;
    }

    int Bissextile(int y)                   
    {
        return ((y % 100 != 0) && (y % 4 == 0)) || (y % 400 == 0);
    }
    int DaysInMonth(int m, int y)         
    {
        int arr[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
        if (Bissextile(y))
            arr[1] = 29;
        return arr[m - 1];
    }

    Date operator--(int)
    {
        if (day-- < 1)
        {
            day = DaysInMonth(month - 1, year);
            if (month - 1 == 0)
                day = DaysInMonth(12, year);
            month--;
        }
        if (month < 1)
        {
            month = 12;
            year--;
        }
        return *this;
    }

    friend ostream& operator<< (ostream& out, const Date& date);
};

ostream& operator<< (ostream& out, const Date& d)
{
    out << "Date in format d/m/y: " << d.day << "/" << d.month << "/" << d.year << " р." << endl;
    out << "Date in format y-m-d: " << d.year << "-" << d.month << "-" << d.day << endl;
    return out;
}

void print(Date* d, int k);

Date* Date::singleObject = nullptr;

int main()
{
    setlocale(LC_ALL, "Ukrainian");
    Date* obj = Date::Instance(30, 5, 2021);
    obj->SetDate(30, 5, 2021);
    print(obj, 1);
    int days = 0;
    cout << endl << "Number of days to reduce each date: ";
    cin >> days;
    for (int j = 0; j < days; ++j)
        (*obj)--;
    print(obj, 1);
    system("pause");
    return 0;
}

void print(Date* d, int k)
{
    for (int i = 0; i < k; i++)
        cout << i + 1 << ". " << d[i];
}