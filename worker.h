// worker.h  -- классы сотрудников с множественным наследованием
#ifndef _WORKER_H_
#define _WORKER_H_
#include <string>

class Worker                                        // работник — абстрактный базовый класс
{
private:
    std::string fullname;
    long id;
protected:
/* Если сделать методы Data() закрытыми, то вызов Worker::Data() из кода Waiter будет невозможным.
Это как раз одна из ситуаций, где могут пригодиться защищенные классы. Если методы Data() являются 
защищенными, их можно использовать внутри всех классов иерархии, но извне они будут недоступны. */
    virtual void Data() const;
    virtual void Get();
public:
    Worker()                                             : fullname("no one"), id(0L) {}
    Worker(const std::string & s, long n)                : fullname(s),        id(n)  {}
    virtual ~Worker()  = 0;                         // чистый виртуальный деструктор
    virtual void Set() = 0;
    virtual void Show() const = 0;
};
class Waiter : virtual public Worker                // виртуальный базовый класс: официант
{
private:
    int panache;
protected:
    void Data() const;
    void Get();
public:
    Waiter()                                                                : Worker(),       panache(0)                {}
    Waiter(const std::string & s, long n, int p = 0)                        : Worker(s, n),   panache(p)                {}
    Waiter(const Worker & wk, int p = 0)                                    : Worker(wk),     panache(p)                {}
    void Set();
    void Show() const;
};
class Singer : virtual public Worker                // виртуальный базовый класс: певец
{
protected:  // ряд внутренних констант, представляющих виды голоса:
    enum {other, alto, contralto, soprano, bass, baritone, tenor};
    enum {Vtypes = 7};
    void Data() const;
    void Get();
private:
    static char * pv[Vtypes];                       // строковые эквиваленты видов голоса
    int voice;
public:
    Singer()                                                                : Worker(),     voice(other)                {}
    Singer(const std::string & s, long n, int v = other)                    : Worker(s, n), voice(v)                    {}
    Singer(const Worker & wk, int v = other)                                : Worker(wk),   voice(v)                    {}
    void Set();
    void Show() const;
};
class SingingWaiter : public Singer, public Waiter  // Множественное наследование
{
protected:
    void Data() const;
    void Get();
public:
    SingingWaiter()                                                                                                     {}
    SingingWaiter(const std::string & s, long n, int p = 0, int v = other)  : Worker(s,n), Waiter(s,n,p), Singer(s,n,v) {}
/* Если для создания виртуального базового класса нужен конструктор не по умолчанию, придется явно 
вызывать соответствующий базовый конструктор: */
    SingingWaiter(const Worker & wk, int p = 0, int v = Singer::other)      : Worker(wk),  Waiter(wk, p), Singer(wk, v) {}
/* Здесь явно вызывается конструктор Worker (const Worker & ). Такое использование допустимо, а зачастую 
и необходимо, для виртуальных базовых классов, но ошибочно для невиртуальных базовых классов. Если у 
класса есть непрямой виртуальный базовый класс, конструктор этого класса должен явно вызывать 
конструктор виртуального базового класса, за исключением случаев, когда достаточно конструктора 
по умолчанию виртуального базового класса. */
    SingingWaiter(const Waiter & wt, int v = other)                         : Worker(wt),  Waiter(wt),    Singer(wt,v)  {}
    SingingWaiter(const Singer & wt, int p = 0)                             : Worker(wt),  Waiter(wt,p),  Singer(wt)    {}
    void Set();
    void Show() const;
};
#endif