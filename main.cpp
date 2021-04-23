#include "que.h"                          // компилировать с worker.cpp
#include "worker.h"
#include <iostream>
#include <cstring>
const int SIZE = 5;

int main(void)
{
    Worker * lolas[SIZE];
    QueueTp<Worker *> lol;
    int ct;
    for (ct = 0; ct < SIZE; ct++)
    {
        char choice;
        std::cout << "Enter the employee category:\n"    // ввод категории работника;
                  << "w: waiter  s: singer  "            // w - официант, s - певец,
                  << "t: singing waiter  q: quit\n";     // t - поющий официант, q - завершение
        std::cin  >> choice;
        while (std::strchr("wstq", choice) == NULL) // возвращает адрес первого вхождения символа choice в строку
        {   // "wstq" (если символ не найден, возвращается указатель NULL).
            std::cout << "Please enter a: w, s, t, or q: ";
            std::cin  >> choice;
        }
        if (choice == 'q')
            break;
        switch(choice)
        {
            case 'w':   lolas[ct] = new Waiter;
                        break;
            case 's':   lolas[ct] = new Singer;
                        break;
            case 't':   lolas[ct] = new SingingWaiter;
                        break;
        }
        while (std::cin.get() != '\n')
        continue;
        //cin.get();
        lolas[ct]->Set();
        if( !(lol.isfull()) ) // если очередь не переполнена и есть работники
            lol.enQueueTp(lolas[ct]);           // добавление новичка в очередь
    }
// вывод списка работников до очереди:
    std::cout << "\nHere is your workers before the Queue:\n";
    for (int i = 0; i < ct; i++)
    {
        std::cout << std::endl;
        lolas[i]->Show();
    }
/* если очередь не переполнена и есть работники:
    for(int i = 0; i < ct && !(lol.isfull()); i++)
    {
        lol.enQueueTp(lolas[i]);                // добавление новичка в очередь
    }*/
    int count = lol.QueueTpcount() - 1;             // определения количества элементов
// Выбрать из очереди первый объект, сдвиг работника начала на следующий элемент и удалить его:
    while( !lol.isempty() )              // пока не пустая очередь
        lol.deQueueTp(lolas[count--]);        // продвижение следующего клиента в начало
// вывод списка работников после очереди:
    std::cout << "\nHere is your workers after wandered trouth Queue:\n";
    for (int i = 0; i < ct; i++)
    {
        std::cout << std::endl;
        lolas[i]->Show();
        delete lolas[i];                        // вызов деструкторов
    }
    std::cout << "Bye.\n";
    // cin.get();
    return 0;
}