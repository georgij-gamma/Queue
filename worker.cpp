// worker0.cpp -- методы классов работников с множественным наследованием
#include "worker.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

// Методы Worker:
Worker::~Worker() {} // Виртуальный деструктор должен быть реализован, даже если он является чистым

void Worker::Get()
{
    //cout << "Enter worker's name: ";                  
    getline(cin, fullname);
    cout << "Enter worker's ID: ";                      // ввод идентификатора работника
    cin >> id;
    while (cin.get() != '\n')
        continue;
}
void Worker::Data() const
{
    cout << "Name: "  << fullname << "\n";              // имя и фамилия
    cout << "Employee ID: " << id << "\n";              // идентификатор
}

// Методы Waiter:                                       // официант
void Waiter::Set()
{
    cout << "Enter waiter's name: ";                    // ввод имени и фамилии работчика
    Worker::Get();
    Get();
}
void Waiter::Get()
{
    cout << "Enter waiter's panache rating: ";          // Ввод индекса элегантности официанта
    cin >> panache;
    while (cin.get() != '\n')
        continue;
}
void Waiter::Show() const
{
    cout << "Category: waiter\n";                       // категория: официант
    Worker::Data();
    Data();
// protected methods
}
void Waiter::Data() const
{
    cout << "Panache rating: " << panache << "\n";      // индекс элегантности
}
// Методы Singer:
char * Singer::pv[Singer::Vtypes] = {"other", "alto", "contralto", // указатели на строковые эквиваленты в стиле С
                            "soprano", "bass", "baritone", "tenor"};
void Singer::Set()
{
    cout << "Enter singer's name: ";                    // Ввод имени и фамилии певца
    Worker::Get();
    Get();
}
void Singer::Get()
{
    cout << "Enter number for singer's vocal range:\n"; // Ввод номера вокального диапазона певца
    int i;
    for (i = 0; i < Vtypes; i++)
    {
        cout << i << ": " << pv[i] << "   ";
        if ( i % 4 == 3)
            cout << endl;
    }
    if (i % 4 != 0)
        cout   << endl;
    while (cin >>  voice && (voice < 0 || voice >= Vtypes))
        cout   << "Please enter a value >= 0 and < " << Vtypes << endl;
    while (cin.get() != '\n')
        continue;
}
void Singer::Show() const
{
    cout << "Category: singer\n";                       // категория: певец
    Worker::Data();
    Data();
}
void Singer::Data() const
{
	cout << "Vocal range: " << pv[voice] << "\n";       // вокальный диапазон
}
// SingingWaiter methods
void SingingWaiter::Data() const
{
	Singer::Data();
	Waiter::Data();
}
void SingingWaiter::Get()
{
    Waiter::Get();
    Singer::Get();
}
void SingingWaiter::Set()
{
    cout << "Enter singing waiter's name: ";            // Ввод имени и фамилии поющего официанта
    Worker::Get();
    Get();
}
void SingingWaiter::Show() const
{
	cout << "Category: singing waiter\n";               // категория: поющий официант
	Worker::Data();
	Data();
}