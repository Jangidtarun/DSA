#include <iostream>
using namespace std;

template <class T>
class dllNODE
{
public:
    dllNODE()
    {
        prev = next = 0;
    }
    dllNODE(T el, dllNODE *n = 0, dllNODE *p = 0)
    {
        info = el;
        next = n;
        prev = p;
    }

    T info;
    dllNODE *prev;
    dllNODE *next;
};

template <class T>
class DLL
{
public:
    DLL()
    {
        head = tail = 0;
    }

    ~DLL()
    {
        for (dllNODE<T> *tmp; !isempty();)
        {
            tmp = head->next;
            delete head;
            head = tmp;
        }
    }

    bool isempty()
    {
        return head == 0;
    }

    int size()
    {
        int ans = 0;

        if (isempty())
        {
            return ans;
        }

        for (dllNODE<T> *tmp = head; tmp != tail->next; tmp = tmp->next)
        {
            ans++;
        }
        return ans;
    }

    void push_front(const T el)
    {
        if (head != 0)
        {
            head = new dllNODE<T>(el, head);
            head->next->prev = head;
        }
        else
        {
            head = tail = new dllNODE<T>(el);
        }
        if (tail == 0)
        {
            tail = head;
        }
    }

    void push_back(const T el)
    {
        if (tail != 0)
        {
            tail = new dllNODE<T>(el, 0, tail);
            tail->prev->next = tail;
        }
        else
        {
            head = tail = new dllNODE<T>(el);
        }
    }

    T pop_front()
    {
        T el = head->info;
        if (head == tail)
        {
            delete head;
            head = tail = 0;
        }

        else
        {
            head = head->next;
            delete head->prev;
            head->prev = 0;
        }
        return el;
    }

    T pop_back()
    {
        T el = tail->info;
        if (head == tail)
        {
            delete head;
            head = tail = 0;
        }
        else
        {
            tail = tail->prev;
            delete tail->next;
            tail->next = 0;
        }
        return el;
    }

    void printList()
    {
        if (isempty())
        {
            return;
        }

        for (dllNODE<T> *tmp = head; tmp != tail->next; tmp = tmp->next)
        {
            cout << tmp->info << ' ';
        }
        cout << '\n';
    }

    void deleteNode(const T &el)
    {
        if (head != 0)
        {
            if (head == tail && el == head->info)
            {
                delete head;
                head = tail = 0;
            }
            else if (head->info == el)
            {
                head = head->next;
                delete head->prev;
                head->prev = 0;
            }
            else
            {
                dllNODE<T> *tmp;
                for (tmp = head; tmp != tail->next && tmp->info != el; tmp = tmp->next)
                {
                }
                if (tmp != 0)
                {
                    tmp->next->prev = tmp->prev;
                    tmp->prev->next = tmp->next;
                    delete tmp;
                }
            }
        }
    }

    bool isInList(const T &el)
    {
        for (dllNODE<T> *tmp = head; tmp != tail; tmp = tmp->next)
        {
            if (tmp->info == el)
            {
                return true;
            }
        }
        return false;
    }

protected:
    T info;
    dllNODE<T> *head, *tail;
};

int main()
{
    DLL<int> list;

    list.push_front(502);
    list.push_back(10);
    list.push_front(1);
    list.push_back(633);

    return EXIT_SUCCESS;
}