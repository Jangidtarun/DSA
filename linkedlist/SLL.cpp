#include <iostream>
#include <bits/stdc++.h>
using namespace std;

template <class T>
class sLLNODE
{
public:
    sLLNODE()
    {
        info = 0;
        next = 0;
    }

    sLLNODE(T val, sLLNODE *node = 0)
    {
        info = val;
        next = node;
    }

    T info;
    sLLNODE *next;
};

template <class T>
class sLL
{
public:
    sLL()
    {
        head = tail = NULL;
    }

    ~sLL()
    {
        for (sLLNODE<T> *p; !isempty();)
        {
            p = head->next;
            delete head;
            head = p;
        }
    }

    bool isempty()
    {
        return head == NULL;
    }

    void addToHead(T el)
    {
        head = new sLLNODE<T>(el, head);
        if (tail == 0)
        {
            tail = head;
        }
    }

    void addToTail(T el)
    {
        if (tail != 0)
        {
            tail->next = new sLLNODE<T>(el);
            tail = tail->next;
        }
        else
            head = tail = new sLLNODE<T>(el);
    }

    T deleteFromHead()
    {
        T el = head->info;
        if (head == tail)
        {
            head = tail = 0;
        }
        else
        {
            head = head->next;
        }
        return el;
    }

    T deleteFromTail()
    {
        T el = tail->info;
        if (head == tail)
        {
            delete head;
            head = tail = 0;
        }
        else
        {
            sLLNODE<T> *tmp;
            for (tmp = head; tmp->next != tail; tmp = tmp->next)
                ;
            delete tail;
            tail = tmp;
            tail->next = 0;
        }
        return el;
    }

    bool isInList(int el)
    {
        for (sLLNODE<T> *tmp = head; tmp != tail; tmp = tmp->next)
        {
            if (tmp->info == el)
            {
                return true;
            }
        }
        return false;
    }

    void deleteNode(T el)
    {
        if (head != 0)
        {
            if (head == tail && el == head->info)
            {
                delete head;
                head = tail = 0;
            }
            else if (el == head->info)
            {
                // sLLNODE *tmp = head;
                delete head;
                head = head->next;
                // delete tmp;
            }
            else
            {
                sLLNODE<T> *pred, *tmp;
                for (pred = head, tmp = head->next; tmp != 0 && !(tmp->info == el); pred = pred->next, tmp = tmp->next)
                {
                }
                if (tmp != 0)
                {
                    pred->next = tmp->next;
                    if (tmp == tail)
                    {
                        tail = pred;
                    }
                    delete tmp;
                }
            }
        }
    }

    void printList()
    {
        if (isempty())
        {
            return;
        }
        for (sLLNODE<T> *tmp = head; tmp != tail->next; tmp = tmp->next)
        {
            cout << tmp->info << " ";
        }
        cout << endl;
    }

private:
    sLLNODE<T> *head, *tail;
};

int main()
{
    sLL<string> l1;
    l1.addToHead("1");
    l1.addToHead("1999");
    l1.addToTail("10");
    l1.addToTail("23");
    l1.printList();

    return EXIT_SUCCESS;
}