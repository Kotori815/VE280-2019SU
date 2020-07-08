#include <iostream>
#include "recursive.h"
#include "p2.h"

using namespace std;

bool is_even(int a){
    if (a % 2 == 0){return true;}
    else {return false;}
    
}

int main()
{
    int i;
    list_t listA, listA_answer;
    list_t listB, listB_answer;

    listA = list_make();
    listB = list_make();
    listA_answer = list_make();
    listB_answer = list_make();

    for(i = 5; i>0; i--)
    {
        listA = list_make(i, listA);
        listA_answer = list_make(6-i, listA_answer);
        listB = list_make(i+10, listB);
        listB_answer = list_make(i+10, listB_answer);
    }

    for(i = 5; i>0; i--)
    {
        listB_answer = list_make(i, listB_answer);
    }

    list_print(listA);
    cout << " size:" << size(listA) <<  endl;
    list_print(listB);
    cout << " size: " << size(listB) << endl;

    cout << "dot product:" << dot(listA, listB) << endl;

    listB = append(listA, listB);
    listA = reverse(listA);
    
    cout << "reversed A:" ;
    list_print(listA);
    cout << "\nArithSeq:" << isArithmeticSequence(listA) << " Incre" << isIncreasing(listA) << endl;
    
    cout << "append A, B:";
    list_print(listB);
    cout << "\nArithSeq:" << isArithmeticSequence(listB) << " Incre" << isIncreasing(listB) << endl;

    cout << "7 in B?" << memberOf(listB, 7) << endl;
    cout << "14 in B?" << memberOf(listB, 14) << endl;

    cout << "filter_odd: " << endl;
    list_print(filter_odd(listA));
    list_print(filter_odd(listB));
    cout << endl;

    cout << "filter with is_even()" << endl;
    list_print(filter(listA, is_even));
    list_print(filter(listB, is_even));
    cout << endl;

    cout << "dot product:" << dot(listA, listB) << endl;

    cout << "insert_list B to A at 3 dig:" << endl;
    list_print(insert_list(listA,listB,3)); 
    cout << endl;

    cout << "chop B by 4 and 6" << endl;
    list_print(chop(listB, 4));
    list_print(chop(listB, 6));
    cout << endl;

    list_t listC = list_make(2,list_make(3,list_make(7,list_make(3,list_make(9,list_make(2,list_make(1,list_make())))))));
    cout << "original listC:" << endl;
    list_print(listC);
    cout << "\n after uniq:" << endl;
    list_print(unique(listC));

}
