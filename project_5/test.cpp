#include <iostream>
#include "dlist.h"
using namespace std;

int main(int argc, char *argv[])
{
    int result = 0;

    Dlist<int> ilist;

    //cout << ilist.isEmpty() << endl;

    int *ip = new int(1);
    ilist.insertFront(ip);
    ip = new int(1);
    ilist.insertBack(ip);
    ip = new int(3);
    ilist.insertBack(ip);

    Dlist<int> jlist = Dlist<int>(ilist);

    ip = ilist.removeFront();
    cout << *ip << endl;
    if(*ip != 1) result = -1;
    delete ip;

    ip = ilist.removeBack();
    cout << *ip << endl;
    if(*ip != 3) result = -1;
    delete ip;

    ip = ilist.removeBack();
    cout << *ip << endl;
    if(*ip != 1) result = -1;
    delete ip;

    cout << endl;

    //ilist.~Dlist();
    if(!ilist.isEmpty()) result = -1;


    ip = jlist.removeFront();
    cout << *ip << endl;
    if(*ip != 1) result = -1;
    delete ip;

    ip = jlist.removeBack();
    cout << *ip << endl;
    if(*ip != 3) result = -1;
    delete ip;

    if(jlist.isEmpty()) result = -1;

    cout << endl;

    ip = new int(3);
    jlist.insertBack(ip);
    ip = new int(5);
    jlist.insertBack(ip);

    ilist = jlist;

    ip = ilist.removeFront();
    cout << *ip << endl;
    if(*ip != 1) result = -1;
    delete ip;

    ip = ilist.removeBack();
    cout << *ip << endl;
    if(*ip != 3) result = -1;
    delete ip;

    ip = ilist.removeBack();
    cout << *ip << endl;
    if(*ip != 5) result = -1;
    delete ip;

    //ilist.~Dlist();
    if(!ilist.isEmpty()) result = -1;

    cout << endl;

    cout << result << endl;
    return result;
}
