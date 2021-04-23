#ifndef _QUE_H_
#define _QUE_H_
#include <cstdlib>

template <typename Item>    // шаблонный класс QueueTp
class QueueTp
{
private:
// Определения области действия класса
    struct Node { Item item; struct Node * next; }; // вложенная структура, локальная для данного класса
    enum {Q_SIZE = 10};
// Закрытые члены класса
    Node * front;                       // указатель на начало QueueTp
    Node * rear;                        // указатель на конец  QueueTp
    int items;                          // текущее количество элементов в QueueTp
    const int qsize;                    // максимальное количество элементов в QueueTp
/* Упреждающие объявления для предотвращения открытого копирования. Этот код переопределяет 
стандартные определения методов, которые в противном случае генерируются автоматически. 
Поскольку это закрытые методы, они не могут вызываться внешним кодом: */
    QueueTp(const QueueTp & q) : qsize(0)  {};
    QueueTp & operator=(const QueueTp & q) { return *this;}
public:
    explicit QueueTp(int qs = Q_SIZE);  // создание очереди с предельным размером qs
    ~QueueTp();
    bool isempty() const;               // проверка на пустоту
    bool isfull() const;                // проверка на заполнение
    int QueueTpcount() const;           // определения количества элементов
    bool enQueueTp(const Item & item);  // добавление элемента в конец
    bool deQueueTp(Item & item);        // удаление элемента из начала
};
// QueueTp methods
template <typename Item>
QueueTp<Item>::QueueTp(int qs) : qsize(qs) // инициализация qsize значением qs
{
    front = rear = NULL;         // or nullptr
    items = 0;
}
template <typename Item>
QueueTp<Item>::~QueueTp()					 // явный деструктор поочередно удаляет все узлы, начиная с начала списка
{
    Node * temp;
	while (front != NULL)	     // пока очередь не пуста
	{
		temp  = front;		     // сохранение адреса начального элемента
		front = front->next;     // переустановка указателя на следующий элемент
		delete temp;		     // удаление предыдущего начального элемента
    }
}
template <typename Item>
bool QueueTp<Item>::isempty() const      // проверка на пустоту
{
    return items == 0;
}
template <typename Item>
bool QueueTp<Item>::isfull() const       // проверка на заполнение
{
    return items == qsize;
}
template <typename Item>
int QueueTp<Item>::QueueTpcount() const    // определения количества элементов
{
    return items;
}
template <typename Item>
bool QueueTp<Item>::enQueueTp(const Item & item) // добавление элемента в конец очереди
{
	if (isfull())			     // если очередь уже полна
		return false;            // завершить программу
	Node * add = new Node;	     // создание узла; при неудачном выполнении операция new генерирует 
                                 // исключение std::bad_alloc.
	add->item = item;		     // занесение значения в часть данных узла
	add->next = NULL;		     // занесение в указатель на следующий узел NULL или nullptr
	items++;					 // увеличить счетчик элементов (items) на единицу
	if (front == NULL)		     // если очередь пуста,
		front = add;		     // элемент помещается в начало
	else						 // иначе он помещается в конец 
		rear->next = add;	     /* присоединить узел в конец очереди; этот процесс состоит из двух частей:
1. Созданный узел привязывается к другим узлам в списке. Для этого в указатель next предыдущего 
   конечного узла заносится ссылка на новый конечный узел.
2. В указатель-член rear объекта QueueTp заносится ссылка на новый узел, чтобы иметь доступ 
   непосредственно к последнему узлу. Если очередь пуста, то ссылку на новый узел необходимо 
   поместить и в указатель front. (Если в очереди всего один узел, то он является и начальным, и конечным.) */			
	rear = add;				     // указатель конца указывает на новый узел
	return true;
}
// Удаление элемента из начала очереди также выполняется за несколько шагов:
template <typename Item>
bool QueueTp<Item>::deQueueTp(Item & item)
{
	if (front == NULL)		     // если очередь уже пуста, завершить программу
		return false;
	item = front->item;			 /* часть данных узла front(первый элемент из очереди) заносится в item —
ссылочную переменную, переданную в метод. */
	items--;					 // уменьшить счетчик элементов (items) на единицу
	Node * temp = front;		 // сохранение местоположения первого элемента (адреса front) для последующего удаления
	front = front->next;		 /* Удалить узел из очереди: сдвиг указателя начала на следующий элемент. В 
указатель-член front объекта QueueTp заносится указатель на следующий узел, адрес которого находится в front->next. */
	delete temp;			     // удаление предыдущего первого элемента
	if (items == 0)			     // если список теперь пуст, то занести в rear значение NULL. (Начальный 
		rear = NULL;		     // указатель уже равен NULL после установки front->next ).
	return true;
}
#endif