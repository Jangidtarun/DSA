#include <iostream>
using namespace std;

class sLLNODE
{
public:
    sLLNODE()
    {
        value = 0;
        next = 0;
    }

    sLLNODE(int val, sLLNODE *node = 0)
    {
        value = val;
        next = node;
    }

    int value;
    sLLNODE *next;
};

class sLL
{
public:
    sLL()
    {
        head = tail = NULL;
    }

    ~sLL()
    {
        for (sLLNODE *p; !isempty();)
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

    void addToHead(int el)
    {
        head = new sLLNODE(el, head);
        if (tail == 0)
        {
            tail = head;
        }
    }

    void addToTail(int el){
        tail->next = new sLLNODE(el);
    }

    int deleteFromHead()
    {
        if (isempty())
        {
            // throw invalid_argument("empty list\n");
            return -1;
        }

        int el = head->value;
        sLLNODE *tmp = head;
        if (head == tail)
        {
            head = tail = 0;
        }
        else
        {
            head = head->next;
        }
        delete tmp;
        return el;
    }

    

private:
    sLLNODE *head, *tail;
};

int main()
{
    sLL l1;
    l1.addToHead(1);
    l1.addToHead(1999);
    l1.addToTail(10);
    cout << l1.deleteFromHead() << endl;
    cout << l1.deleteFromHead() << endl;
    cout << l1.deleteFromHead() << endl;
    return EXIT_SUCCESS;
}