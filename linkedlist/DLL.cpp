#include<iostream>
using namespace std;

template <class T>
class dllNODE{
    public:
    dllNODE(){
        prev = next = 0;
    }
    dllNODE(T el, dllNODE *n = 0, dllNODE *p = 0){
        info = el;
        next = n;
        prev = p;
    }

    T info;
    dllNODE *prev;
    dllNODE *next;
};

int main(){
    dllNODE<string> *past = new dllNODE<string>("purva");
    dllNODE<string> *now = new dllNODE<string>("65");
    dllNODE<string> *node = new dllNODE<string>("hello",now,past);

    cout << node->prev->info << endl;
    cout << node->info << endl;
    cout << node->next->info << endl;
    return EXIT_SUCCESS;
}